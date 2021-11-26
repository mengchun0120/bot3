#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
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
                   float maxObjSpan)
{
    initItemDeleter();
    initBoundaryCells(maxObjSpan);
    initPool(poolSize);
    initMap(rows, cols, viewportWidth, viewportHeight);
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

    int rowIdx = getCellIdx(o->y());
    if (rowIdx < 0 || rowIdx >= rowCount())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "o->x is out of range: " + toString(o->x()));
    }

    int colIdx = getCellIdx(o->x());
    if (colIdx < 0 || colIdx >= colCount())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "o->y is out of range: " + toString(o->y()));
    }

    o->setMapPos(rowIdx, colIdx);

    GameMapItem* item = itemPool_.alloc();
    item->init(o, deleter);
    map_[rowIdx][colIdx].pushFront(item);

    LOG_INFO << "addObj " << o->type() << " row=" << rowIdx
             << " col=" << colIdx << LOG_END;
}

void GameMap::setViewportOrigin(float x,
                                float y)
{
    viewportOrigin_[0] = clamp(x, minViewportOrigin_[0], maxViewportOrigin_[0]);
    viewportOrigin_[1] = clamp(y, minViewportOrigin_[1], maxViewportOrigin_[1]);
    viewportAnchor_ = viewportOrigin_ - viewportHalfSize_;
}

bool GameMap::withinBoundary(float x,
                             float y)
{
    return x > boundaryLeft_ &&
           x < boundaryRight_ &&
           y > boundaryBottom_ &&
           y < boundaryTop_;
}

void GameMap::initItemDeleter()
{
    itemDeleter_ = [this](GameMapItem* item)->void
    {
        item->deleteObj();
        itemPool_.free(item);
    };
}

void GameMap::initBoundaryCells(float maxObjSpan)
{
    if (maxObjSpan <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid maxObjSpan " + toString(maxObjSpan));
    }

    maxObjSpan_ = maxObjSpan;
    boundaryCells_ = static_cast<int>(floor(maxObjSpan_ / k_cellBreath));
    if (boundaryCells_ <= 0)
    {
        boundaryCells_ = 1;
    }
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
                      float viewportHeight)
{
    unsigned int rowCount = rows + 2*boundaryCells_;
    unsigned int colCount = cols + 2*boundaryCells_;

    setMapSize(rowCount, colCount);
    setViewportSize(viewportWidth, viewportHeight);
    setViewportOrigin(minViewportOrigin_[0], minViewportOrigin_[1]);

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
    boundaryLeft_ = -maxObjSpan_;
    boundaryRight_ = width_ + maxObjSpan_;
    boundaryBottom_ = -maxObjSpan_;
    boundaryTop_ = height_ + maxObjSpan_;
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

} // end of namespace botlib
} // end of namespace mcdane

