#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_collide.h>
#include <botlib_graphics.h>
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

void GameMap::present() const
{
    SimpleShaderProgram& program = Graphics::simpleShader();
    program.use();
    program.setViewportOrigin(viewportOrigin_);

    int startRow, endRow, startCol, endCol;

    getPresentArea(startRow, endRow, startCol, endCol);
    for (int row = startRow; row <= endRow; ++row)
    {
        auto& r = map_[row];

        for (int col = startCol; col <= endCol; ++col)
        {
            presentCell(r[col]);
        }
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

    LOG_INFO << "addObj " << o->type() << " row=" << rowIdx
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
    setMapSize(rows, cols);
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

void GameMap::setMapSize(unsigned int rows,
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

    width_ = rows * k_cellBreath;
    height_ = cols * k_cellBreath;
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
    maxViewportOrigin_.init({width_ - viewportHalfSize_[0],
                             height_ - viewportHalfSize_[1]});

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

void GameMap::presentCell(const ItemList& cell) const
{
    static GameObjectType presentOrder[] = {
        GameObjectType::TILE,
        GameObjectType::MISSILE,
        GameObjectType::ROBOT,
        GameObjectType::EFFECT
    };

    for (unsigned int i = 0; i < k_gameObjTypeCount; ++i)
    {
        for (const GameMapItem* t = cell.first(); t; t = t->next())
        {
            const GameObject* o = t->obj();
            if (o->type() == presentOrder[i])
            {
                o->present();
            }
        }
    }
}

} // end of namespace botlib
} // end of namespace mcdane

