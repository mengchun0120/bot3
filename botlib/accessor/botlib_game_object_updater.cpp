#include <botlib_game_object.h>
#include <botlib_game_object_updater.h>

namespace mcdane {
namespace botlib {

GameObjectUpdater::GameObjectUpdater(UpdateContext& cxt)
    : cxt_(cxt)
{
}

bool GameObjectUpdater::run(GameObject* obj)
{
    if (obj->updated() && obj->state() == GameObjectState::DEAD)
    {
        return true;
    }

    obj->update(cxt_);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

