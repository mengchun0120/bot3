#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMap::GameMap()
    : maxObjWidth_(0.0f)
    , maxObjHeight_(0.0f)
{
    initItemDeleter();
}

GameMap::GameMap(unsigned int poolSize,
                 unsigned int rows,
                 unsigned int cols,
                 float viewportWidth,
                 float viewportHeight,
                 float originX,
                 float originY)
{
    initItemDeleter();
    init(rows, cols, poolSize, viewportWidth, viewportHeight, originX, originY);
}

GameMap::~GameMap()
{
}

void GameMap::init(unsigned int poolSize,
                   unsigned int rows,
                   unsigned int cols,
                   float viewportWidth,
                   float viewportHeight,
                   float originX,
                   float originY)
{
    maxObjWidth_ = 0.0f;
    maxObjHeight_ = 0.0f;
    initPool(poolSize);
    initMap(rows, cols, viewportWidth, viewportHeight, originX, originY);
}

void GameMap::present() const
{
    int startRow, endRow, startCol, endCol;

    getPresentArea(startRow, endRow, startCol, endCol);
    for (int row = startRow; row <= endRow; ++row)
    {
        auto& r = map_[row];

        for (int col = startCol; col <= endCol; ++col)
        {
            const GameMapItem* item;
            for (item = r[col].first(); item; item = item->next())
            {
                item->obj()->present();
            }
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

    int rowIdx = getCellIdx(o->x());
    if (rowIdx < 0 || rowIdx >= rowCount())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "o->x is out of range: " + toString(o->x()));
    }

    int colIdx = getCellIdx(o->y());
    if (colIdx < 0 || colIdx >= colCount())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "o->y is out of range: " + toString(o->y()));
    }

    GameMapItem* item = itemPool_.alloc();
    item->init(o, deleter);
    map_[rowIdx][colIdx].pushFront(item);

    if (o->width() > maxObjWidth_)
    {
        maxObjWidth_ = o->width();
    }

    if (o->height() > maxObjHeight_)
    {
        maxObjHeight_ = o->height();
    }
}

void GameMap::setOrigin(float originX,
                        float originY)
{
    originX_ = clamp(originX, 0.0f, maxOriginX_);
    originY_ = clamp(originY, 0.0f, maxOriginY_);
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
                      float originX,
                      float originY)
{
    if (rows == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid rows " + toString(rows));
    }

    if (cols == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid cols " + toString(cols));
    }

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

    width_ = rows * k_cellBreath;
    height_ = cols * k_cellBreath;
    viewportWidth_ = viewportWidth;
    viewportHeight_ = viewportHeight;
    maxOriginX_ = width_ - viewportWidth_;
    maxOriginY_ = height_ - viewportHeight_;

    setOrigin(originX, originY);

    map_.resize(rows);
    for (auto it = map_.begin(); it != map_.end(); ++it)
    {
        it->resize(cols);
        for (auto itemIt = it->begin(); itemIt != it->end(); ++itemIt)
        {
            itemIt->setDeleter(&itemDeleter_);
        }
    }

}

void GameMap::getPresentArea(int& startRow,
                             int& endRow,
                             int& startCol,
                             int& endCol) const
{
    startRow = getCellIdx(originY_ - maxObjHeight_);
    if (startRow < 0)
    {
        startRow = 0;
    }

    endRow = getCellIdx(originY_ + viewportHeight_);
    if (endRow >= rowCount())
    {
        endRow = rowCount() - 1;
    }

    startCol = getCellIdx(originX_ - maxObjWidth_);
    if (startCol < 0)
    {
        startCol = 0;
    }

    endCol = getCellIdx(originX_ + viewportWidth_);
    if (endCol >= colCount())
    {
        endCol = colCount() - 1;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

