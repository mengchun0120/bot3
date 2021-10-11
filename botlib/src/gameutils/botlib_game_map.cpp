#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMap::GameMap()
{
    initItemDeleter();
}

GameMap::GameMap(unsigned int rows,
                 unsigned int cols,
                 unsigned int poolSize)
{
    initItemDeleter();
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
        for (auto itemIt = it->begin(); itemIt != it->end(); ++itemIt)
        {
            itemIt->setDeleter(&itemDeleter);
        }
    }
}

void GameMap::present() const
{
}

void GameMap::addObj(GameObject* o,
                     GameObject::Deleter* deleter)
{
}

void GameMap::initItemDeleter()
{
    itemDeleter_ = [this](GameMapItem* item)->void
    {
        item->deleteObj();
        itemPool_.free(item);
    };
}

} // end of namespace botlib
} // end of namespace mcdane

