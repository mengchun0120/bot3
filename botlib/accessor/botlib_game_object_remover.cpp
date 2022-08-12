#include <commonlib_log.h>
#include <botlib_game_object.h>
#include <botlib_game_object_dumper.h>
#include <botlib_game_object_remover.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectRemover::GameObjectRemover(GameObjectDumper& dumper,
                                     GameMap& map)
    : dumper_(dumper)
    , map_(map)
{
}

bool GameObjectRemover::run(GameObject* obj)
{
    if (obj->state() != GameObjectState::DEAD && obj->canBeDumped(map_))
    {
        dumper_.add(obj);
    }

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
