#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_math_utils.h>
#include <commonlib_collide.h>
#include <botlib_graphics.h>
#include <botlib_game_object_presenter.h>
#include <botlib_game_map.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameMap::init(unsigned int poolSize,
                   unsigned int rows,
                   unsigned int cols,
                   float viewportWidth,
                   float viewportHeight,
                   float maxObjSpan,
                   float maxCollideBreath)
{
    initItemDeleter();
    initPool(poolSize);
    initMap(rows, cols, viewportWidth, viewportHeight,
            maxObjSpan, maxCollideBreath);
}

void GameMap::present()
{
    using namespace std::placeholders;

    static GameObjectType presentOrder[] = {
        GameObjectType::TILE,
        GameObjectType::ROBOT,
        GameObjectType::MISSILE,
        GameObjectType::EFFECT
    };
    static GameObjectPresenter presenter;
    static Accessor accessor = std::bind(&GameObjectPresenter::present,
                                         &presenter, _1);

    SimpleShaderProgram& program = Graphics::simpleShader();
    program.use();
    program.setViewportOrigin(viewportOrigin_);

    int startRow, endRow, startCol, endCol;

    getPresentArea(startRow, endRow, startCol, endCol);
    for (unsigned int i = 0; i < k_gameObjTypeCount; ++i)
    {
        presenter.reset(presentOrder[i]);
        accessRegion(startRow, endRow, startCol, endCol, accessor);
    }
}

void GameMap::addObj(GameObject* o,
                     GameObject::Deleter* deleter)
{
    if (!o)
    {
        THROW_EXCEPT(InvalidArgumentException, "o is null");
    }

    int rowIdx = getCellIdx(o->y());
    int colIdx = getCellIdx(o->x());
    o->setMapPos(rowIdx, colIdx);

    GameMapItem* item = itemPool_.alloc();
    item->init(o, deleter);
    map_[rowIdx][colIdx].pushFront(item);

    LOG_DEBUG << "addObj " << o->type() << " row=" << rowIdx
             << " col=" << colIdx << LOG_END;
}

void GameMap::repositionObj(GameObject* o)
{
    if (!o)
    {
        THROW_EXCEPT(InvalidArgumentException, "o is null");
    }

    unsigned int rowIdx = getCellIdx(o->y());
    unsigned int colIdx = getCellIdx(o->x());

    if (rowIdx == o->row() && colIdx == o->col())
    {
        return;
    }

    GameMapItem* item = unlinkObj(o);
    map_[rowIdx][colIdx].pushFront(item);
    o->setMapPos(rowIdx, colIdx);
}

void GameMap::setViewportOrigin(float x,
                                float y)
{
    viewportOrigin_[0] = clamp(x, minViewportOrigin_[0], maxViewportOrigin_[0]);
    viewportOrigin_[1] = clamp(y, minViewportOrigin_[1], maxViewportOrigin_[1]);
    viewportAnchor_ = viewportOrigin_ - viewportHalfSize_;
}

GameMapItem* GameMap::searchObj(GameObject* o)
{
    ItemList& cell = map_[o->row()][o->col()];
    for (GameMapItem* i = cell.first(); i; i = i->next())
    {
        if (i->obj() == o)
        {
            return i;
        }
    }

    return nullptr;
}

GameMapItem* GameMap::unlinkObj(GameObject* o)
{
    GameMapItem* item = searchObj(o);
    map_[o->row()][o->col()].unlink(item);
    return item;
}

void GameMap::getCollideArea(int& startRow,
                             int& endRow,
                             int& startCol,
                             int& endCol,
                             float left,
                             float right,
                             float bottom,
                             float top,
                             float deltaX,
                             float deltaY) const
{
    float startX, endX, startY, endY;

    if (std::signbit(deltaX))
    {
        startX = left + deltaX - maxCollideBreath_;
        endX = right + maxCollideBreath_;
    }
    else
    {
        startX = left - maxCollideBreath_;
        endX = right + deltaX + maxCollideBreath_;
    }

    if (std::signbit(deltaY))
    {
        startY = bottom + deltaY - maxCollideBreath_;
        endY = top + maxCollideBreath_;
    }
    else
    {
        startY = bottom - maxCollideBreath_;
        endY = top + deltaY + maxCollideBreath_;
    }

    startRow = clamp(getCellIdx(startY), 0, rowCount()-1);
    endRow = clamp(getCellIdx(endY), 0, rowCount()-1);
    startCol = clamp(getCellIdx(startX), 0, colCount()-1);
    endCol = clamp(getCellIdx(endX), 0, colCount()-1);
}

Region<int> GameMap::getCollideArea(const Region<float>& r,
                                    float deltaX,
                                    float deltaY) const
{
    float startX, endX, startY, endY;

    if (std::signbit(deltaX))
    {
        startX = r.left() + deltaX - maxCollideBreath_;
        endX = r.right() + maxCollideBreath_;
    }
    else
    {
        startX = r.left() - maxCollideBreath_;
        endX = r.right() + deltaX + maxCollideBreath_;
    }

    if (std::signbit(deltaY))
    {
        startY = r.bottom() + deltaY - maxCollideBreath_;
        endY = r.top() + maxCollideBreath_;
    }
    else
    {
        startY = r.bottom() - maxCollideBreath_;
        endY = r.top() + deltaY + maxCollideBreath_;
    }

    int bottom = clamp(getCellIdx(startY), 0, rowCount()-1);
    int top = clamp(getCellIdx(endY), 0, rowCount()-1);
    int left = clamp(getCellIdx(startX), 0, colCount()-1);
    int right = clamp(getCellIdx(endX), 0, colCount()-1);

    return Region<int>(left, right, bottom, top);
}

void GameMap::getCollideArea(int& startRow,
                             int& endRow,
                             int& startCol,
                             int& endCol,
                             float left,
                             float right,
                             float bottom,
                             float top) const
{
    float startX = left - maxCollideBreath_;
    float endX = right + maxCollideBreath_;
    float startY = bottom - maxCollideBreath_;
    float endY = top + maxCollideBreath_;

    startRow = clamp(getCellIdx(startY), 0, rowCount()-1);
    endRow = clamp(getCellIdx(endY), 0, rowCount()-1);
    startCol = clamp(getCellIdx(startX), 0, colCount()-1);
    endCol = clamp(getCellIdx(endX), 0, colCount()-1);
}

Region<int> GameMap::getCollideArea(const Region<float>& r) const
{
    float startX = r.left() - maxCollideBreath_;
    float endX = r.right() + maxCollideBreath_;
    float startY = r.bottom() - maxCollideBreath_;
    float endY = r.top() + maxCollideBreath_;

    int bottom = clamp(getCellIdx(startY), 0, rowCount()-1);
    int top = clamp(getCellIdx(endY), 0, rowCount()-1);
    int left = clamp(getCellIdx(startX), 0, colCount()-1);
    int right = clamp(getCellIdx(endX), 0, colCount()-1);

    return Region<int>(left, right, bottom, top);
}

void GameMap::accessRegion(int startRow,
                           int endRow,
                           int startCol,
                           int endCol,
                           Accessor& accessor)
{
    for (int r = startRow; r <= endRow; ++r)
    {
        auto& row = map_[r];
        for (int c = startCol; c <= endCol; ++c)
        {
            for (GameMapItem* i = row[c].first(); i; i = i->next())
            {
                if (!accessor(i->obj()))
                {
                    return;
                }
            }
        }
    }
}

void GameMap::accessRegion(const Region<int>& r,
                           Accessor& accessor)
{
    for (int rowIdx = r.bottom(); rowIdx <= r.top(); ++rowIdx)
    {
        auto& row = map_[rowIdx];
        for (int colIdx = r.left(); colIdx <= r.right(); ++colIdx)
        {
            for (GameMapItem* i = row[colIdx].first(); i; i = i->next())
            {
                if (!accessor(i->obj()))
                {
                    return;
                }
            }
        }
    }
}

bool GameMap::checkRectCollide(float left,
                               float right,
                               float bottom,
                               float top) const
{
    bool collideBoundary = checkRectCollideBoundary(left, right, bottom, top,
                                                    0.0, width(), 0.0, height());

    if (collideBoundary)
    {
        return true;
    }

    int startRow, endRow, startCol, endCol;

    getCollideArea(startRow, endRow, startCol, endCol, left, right, bottom, top);
    for (int r = startRow; r <= endRow; ++r)
    {
        auto& row = map_[r];
        for (int c = startCol; c <= endCol; ++c)
        {
            for (const GameMapItem* i = row[c].first(); i; i = i->next())
            {
                const GameObject* o = i->obj();
                if (!o->alive() || !isNonPassthroughObjType(o->type()))
                {
                    continue;
                }

                bool collideObj = checkRectCollideRect(
                                        left, right, bottom, top,
                                        o->x() - o->collideBreath(),
                                        o->x() + o->collideBreath(),
                                        o->y() - o->collideBreath(),
                                        o->y() + o->collideBreath());
                if (collideObj)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void GameMap::initItemDeleter()
{
    itemDeleter_ = [this](GameMapItem* item)->void
    {
        item->deleteObj();
        itemPool_.free(item);
    };
}

void GameMap::initPool(unsigned int poolSize)
{
    if (poolSize == 0)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid poolSize" + toString(poolSize));
    }

    itemPool_.init(poolSize);
}

void GameMap::initMap(unsigned int rows,
                      unsigned int cols,
                      float viewportWidth,
                      float viewportHeight,
                      float maxObjSpan,
                      float maxCollideBreath)
{
    setBoundary(rows, cols);
    setViewportSize(viewportWidth, viewportHeight);
    setViewportOrigin(minViewportOrigin_[0], minViewportOrigin_[1]);

    map_.resize(rows);
    for (auto it = map_.begin(); it != map_.end(); ++it)
    {
        it->resize(cols);
        for (auto itemIt = it->begin(); itemIt != it->end(); ++itemIt)
        {
            itemIt->setDeleter(&itemDeleter_);
        }
    }

    maxObjSpan_ = maxObjSpan;
    maxCollideBreath_ = maxCollideBreath;
}

void GameMap::setBoundary(unsigned int rows,
                          unsigned int cols)
{
    if (rows < k_minRows)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid rows " + toString(rows));
    }

    if (cols < k_minCols)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid cols " + toString(cols));
    }

    boundary_.init(0.0f, rows * k_cellBreath, 0.0f, cols * k_cellBreath);
}

void GameMap::setViewportSize(float viewportWidth,
                              float viewportHeight)
{
    if (viewportWidth <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportWidth " + toString(viewportWidth));
    }

    if (viewportHeight <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportHeight " + toString(viewportHeight));
    }

    viewportSize_.init({viewportWidth, viewportHeight});
    viewportHalfSize_ = viewportSize_ / 2.0f;
    minViewportOrigin_ = viewportHalfSize_;
    maxViewportOrigin_.init({width() - viewportHalfSize_[0],
                             height() - viewportHalfSize_[1]});

}

void GameMap::getPresentArea(int& startRow,
                             int& endRow,
                             int& startCol,
                             int& endCol) const
{
    startRow = getCellIdx(viewportAnchor_[1] - maxObjSpan_);
    if (startRow < 0)
    {
        startRow = 0;
    }

    endRow = getCellIdx(viewportAnchor_[1] + viewportSize_[1] + maxObjSpan_);
    if (endRow >= rowCount())
    {
        endRow = rowCount() - 1;
    }

    startCol = getCellIdx(viewportAnchor_[0] - maxObjSpan_);
    if (startCol < 0)
    {
        startCol = 0;
    }

    endCol = getCellIdx(viewportAnchor_[0] + viewportSize_[0] + maxObjSpan_);
    if (endCol >= colCount())
    {
        endCol = colCount() - 1;
    }
}

void GameMap::presentCell(const ItemList& cell,
                          GameObjectType type) const
{
    for (const GameMapItem* t = cell.first(); t; t = t->next())
    {
        const GameObject* o = t->obj();
        if (o->type() == type)
        {
            o->present();
        }
    }
}

} // end of namespace botlib
} // end of namespace mcdane

