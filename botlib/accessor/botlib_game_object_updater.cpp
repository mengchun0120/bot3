#include <botlib_game_object.h>
#include <botlib_game_object_updater.h>

namespace mcdane {
namespace botlib {

GameObjectUpdater::GameObjectUpdater(float delta)
    : delta_(delta)
{
}

void GameObjectUpdater::reset(float delta)
{
    delta_ = delta;
}

bool GameObjectUpdater::run(GameMap& map,
                            GameObject* obj)
{
    if (obj->state() != GameObjectState::ALIVE || obj->updated())
    {
        return true;
    }

    obj->update(map, delta_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

