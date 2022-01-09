#include <commonlib_log.h>
#include <commonlib_linked_list.h>
#include <botlib_game_object.h>
#include <botlib_dead_object_remover.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

bool DeadObjectRemover::run(GameObjectList& objList,
                            GameObject* obj)
{
    if (obj->alive())
    {
        return true;
    }

    LOG_DEBUG << "Deleted " << obj->type() << " " << obj << LOG_END;

    objList.remove(obj);

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

