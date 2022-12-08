#include <botlib_update_context.h>

namespace mcdane {
namespace botlib {

void UpdateContext::init(GameMap* map1,
                         GameObjectDumper* dumper1)
{
    map_ = map1;
    dumper_ = dumper1;
}

void UpdateContext::setTimeDelta(float timeDelta1)
{
    timeDelta_ = timeDelta1;
}

} // end of namespace botlib
} // end of namespace mcdane

