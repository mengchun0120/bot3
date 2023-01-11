#include <commonlib_exception.h>
#include <botlib_context.h>
#include <botlib_chase_shoot_ai.h>
#include <botlib_ai_factory.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AI* AIFactory::create(AIRobot* robot,
                      const std::string& algorithm,
                      const std::string& name)
{
    AI* ai = nullptr;

    if (algorithm == "chase_shoot")
    {
        ai = createChaseShootAI(robot, name);
    }
    else
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Unsupported AI algorithm " + algorithm);
    }

    return ai;
}

AI* AIFactory::createChaseShootAI(AIRobot* robot,
                                  const std::string& name)
{
    const AILib& lib = Context::gameLib().aiLib();
    const ChaseShootAIParam* param = lib.findChaseShootAIParam(name);
    if (!param)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find ChaseShootAIParam " + name);
    }

    ChaseShootAI* ai = new ChaseShootAI();
    ai->init(robot, param);
    return ai;
}

} // end of namespace botlib
} // end of namespace mcdane
