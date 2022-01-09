#include <botlib_game_object_updater.h>

namespace mcdane {
namespace botlib {

void GameObjectUpdater::setMap(GameMap* map)
{
    map_ = map;
}

void GameObjectUpdater::setDelta(float delta)
{
    delta_ = delta;
}

bool GameObjectUpdater::run(GameObjectList& objList,
                            GameObject* obj)
{
    if (!check(obj))
    {
        return true;
    }

    obj->update(*map_, delta_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

