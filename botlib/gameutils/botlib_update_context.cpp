#include <commonlib_linked_item.h>
#include <commonlib_object_pool.h>
#include <botlib_update_context.h>

namespace mcdane {
namespace botlib {

void UpdateContext::init(GameMap* map1, int itemPoolSize)
{
    map_ = map1;
    itemPool_.init(itemPoolSize);

    itemDeleter_ = [&](GameObjectItem* item)
    {
        itemPool_.free(item);
    };

    dumper_.init(&itemPool_, itemDeleter_);
}

void UpdateContext::setTimeDelta(float timeDelta1)
{
    timeDelta_ = timeDelta1;
}

} // end of namespace botlib
} // end of namespace mcdane

