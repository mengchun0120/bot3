#include <botlib_game_object.h>
#include <botlib_game_object_updater.h>

namespace mcdane {
namespace botlib {

void GameObjectUpdater::init(GameObjectDumper* dumper)
{
    dumper_ = dumper;
}

void GameObjectUpdater::reset(float timeDelta)
{
    timeDelta_ = timeDelta;
}

bool GameObjectUpdater::run(GameMap& map,
                            GameObject* obj)
{
    if (obj->updated())
    {
        return true;
    }

    obj->update(map, *dumper_, timeDelta_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

