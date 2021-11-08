#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_graphics.h>
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
                 float viewportHeight)
{
    initItemDeleter();
    init(rows, cols, poolSize, viewportWidth, viewportHeight);
}

GameMap::~GameMap()
{
}

void GameMap::init(unsigned int poolSize,
                   unsigned int rows,
                   unsigned int cols,
                   float viewportWidth,
                   float viewportHeight)
{
    maxObjWidth_ = 0.0f;
    maxObjHeight_ = 0.0f;
    initPool(poolSize);
    initMap(rows, cols, viewportWidth, viewportHeight);
}

void GameMap::present() const
{
    Graphics& g = Graphics::getInstance();
    SimpleShaderProgram& program = g.simpleShader();
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

void GameMap::setViewportOrigin(float x,
                                float y)
{
    viewportOrigin_[0] = clamp(x, minViewportOrigin_[0], maxViewportOrigin_[0]);
    viewportOrigin_[1] = clamp(y, minViewportOrigin_[1], maxViewportOrigin_[1]);
    viewportAnchor_ = viewportOrigin_ - viewportHalfSize_;
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
                      float viewportHeight)
{
    setMapSize(rows, cols);
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
    startRow = getCellIdx(viewportAnchor_[1] - maxObjHeight_);
    if (startRow < 0)
    {
        startRow = 0;
    }

    endRow = getCellIdx(viewportAnchor_[1] + viewportSize_[1]);
    if (endRow >= rowCount())
    {
        endRow = rowCount() - 1;
    }

    startCol = getCellIdx(viewportAnchor_[0] - maxObjWidth_);
    if (startCol < 0)
    {
        startCol = 0;
    }

    endCol = getCellIdx(viewportAnchor_[0] + viewportSize_[0]);
    if (endCol >= colCount())
    {
        endCol = colCount() - 1;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

