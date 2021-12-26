#include <cmath>
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
    constexpr int presentTypeCount = 4;
    static GameObjectPresenter presenter;
    static Accessor accessor = std::bind(&GameObjectPresenter::present,
                                         &presenter, _1);

    SimpleShaderProgram& program = Graphics::simpleShader();
    program.setViewportOrigin(viewportOrigin_);

    for (unsigned int i = 0; i < presentTypeCount; ++i)
    {
        presenter.reset(presentOrder[i]);
        accessRegion(presentArea_, accessor);
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
    resetViewableRegion();
    resetPresentArea();
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

void GameMap::accessRegion(const Region<int>& r,
                           Accessor& accessor)
{
    GameMapItem* item, * next;

    for (int rowIdx = r.bottom(); rowIdx <= r.top(); ++rowIdx)
    {
        auto& row = map_[rowIdx];
        for (int colIdx = r.left(); colIdx <= r.right(); ++colIdx)
        {
            for (item = row[colIdx].first(); item; item = next)
            {
                next = item->next();

                if (!accessor(item->obj()))
                {
                    return;
                }
            }
        }
    }
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
    maxObjSpan_ = maxObjSpan;
    maxCollideBreath_ = maxCollideBreath;
    extraCell_ = static_cast<int>(ceil(maxObjSpan_ / k_cellBreath));
    initMapCells(rows, cols);
    setBoundary(rows, cols);
    setViewportSize(viewportWidth, viewportHeight);
    setViewportOrigin(minViewportOrigin_[0], minViewportOrigin_[1]);
}

void GameMap::initMapCells(unsigned int rows,
                           unsigned int cols)
{
    unsigned int rowCount = rows + extraCell_*2;
    unsigned int colCount = cols + extraCell_*2;

    map_.resize(rowCount);
    for (auto it = map_.begin(); it != map_.end(); ++it)
    {
        it->resize(colCount);
        for (auto itemIt = it->begin(); itemIt != it->end(); ++itemIt)
        {
            itemIt->setDeleter(&itemDeleter_);
        }
    }
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

void GameMap::resetViewableRegion()
{
    viewableRegion_.init(viewportAnchor_[0] - maxObjSpan_,
                         viewportAnchor_[0] + viewportSize_[0] + maxObjSpan_,
                         viewportAnchor_[1] - maxObjSpan_,
                         viewportAnchor_[1] + viewportSize_[1] + maxObjSpan_);
}

void GameMap::resetPresentArea()
{
    int startRow = clamp(getCellIdx(viewableRegion_.bottom()), 0, rowCount()-1);
    int endRow = clamp(getCellIdx(viewableRegion_.top()), 0, rowCount()-1);
    int startCol = clamp(getCellIdx(viewableRegion_.left()), 0, colCount()-1);
    int endCol = clamp(getCellIdx(viewableRegion_.right()), 0, colCount()-1);

    presentArea_.init(startCol, endCol, startRow, endRow);
}

} // end of namespace botlib
} // end of namespace mcdane

