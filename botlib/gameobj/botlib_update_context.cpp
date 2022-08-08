#include <botlib_update_context.h>

namespace mcdane {
namespace botlib {

void UpdateContext::init(GameMap* map1,
                         GameObjectDumper* dumper1,
                         AIRobotDeathListener listener)
{
    map_ = map1;
    dumper_ = dumper1;
    aiRobotDeathListener_ = listener;
}

void UpdateContext::setTimeDelta(float timeDelta1)
{
    timeDelta_ = timeDelta1;
}

void UpdateContext::onAIRobotDeath()
{
    if (aiRobotDeathListener_)
    {
        aiRobotDeathListener_();
    }
}

} // end of namespace botlib
} // end of namespace mcdane

