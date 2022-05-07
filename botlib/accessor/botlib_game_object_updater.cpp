#include <botlib_game_object.h>
#include <botlib_game_object_updater.h>

namespace mcdane {
namespace botlib {

GameObjectUpdater::GameObjectUpdater(GameMap& map,
                                     GameObjectDumper& dumper,
                                     float timeDelta)
    : map_(map)
    , dumper_(dumper)
    , timeDelta_(timeDelta)
{
}

bool GameObjectUpdater::run(GameObject* obj)
{
    if (obj->updated())
    {
        return true;
    }

    obj->update(map_, dumper_, timeDelta_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

