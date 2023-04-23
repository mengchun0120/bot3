#include <commonlib_log.h>
#include <botlib_game_object.h>
#include <botlib_game_obj_updater.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameObjUpdater::init(UpdateContext *cxt)
{
    cxt_ = cxt;
}

bool GameObjUpdater::operator()(GameObject *obj)
{
    if (obj->updated() && obj->state() == GameObjectState::DEAD)
    {
        return true;
    }

    obj->update(*cxt_);

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
