#include <commonlib_log.h>
#include <botlib_dead_object_remover.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

bool DeadObjectRemover::run(ItemList& itemList,
                            GameMapItem* item)
{
    GameObject* o = item->obj();

    if (o->alive())
    {
        return true;
    }

    LOG_DEBUG << "Deleted " << o->type() << " " << o << LOG_END;

    itemList.remove(item);

    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

