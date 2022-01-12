#include <botlib_game_object.h>
#include <botlib_game_object_updater.h>

namespace mcdane {
namespace botlib {

GameObjectUpdater::GameObjectUpdater(GameMap* map,
                                     float delta)
    : map_(map)
    , delta_(delta)
{
}

void GameObjectUpdater::reset(GameMap* map,
                              float delta)
{
    map_ = map;
    delta_ = delta;
}

bool GameObjectUpdater::run(GameObjectList& objList,
                            GameObject* obj)
{
    if (!obj->alive() || obj->updated())
    {
        return true;
    }

    obj->update(*map_, delta_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

