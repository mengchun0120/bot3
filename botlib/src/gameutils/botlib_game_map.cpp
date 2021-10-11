#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMap::GameMap()
    : itemDeleter_(itemPool_)
{
}

GameMap::GameMap(unsigned int rows,
                 unsigned int cols,
                 unsigned int poolSize)
    : itemDeleter_(itemPool_)
{
    init(rows, cols, poolSize);
}

GameMap::~GameMap()
{
}

void GameMap::init(unsigned int rows,
                   unsigned int cols,
                   unsigned int poolSize)
{
    if (rows == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid rows " + toString(rows));
    }

    if (cols == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid cols " + toString(cols));
    }

    itemPool_.init(poolSize);
    map_.resize(rows);
    for (auto it = map_.begin(); it != map_.end(); ++it)
    {
        it->resize(cols);
    }
}

void GameMap::present() const
{
}

void GameMap::addObj(GameObject* o)
{
}

} // end of namespace botlib
} // end of namespace mcdane

