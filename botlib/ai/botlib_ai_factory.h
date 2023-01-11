#ifndef INCLUDED_BOTLIB_AI_FACTORY_H
#define INCLUDED_BOTLIB_AI_FACTORY_H

#include <string>

namespace mcdane {
namespace botlib {

class AI;
class AIRobot;

class AIFactory {
public:
    static AI* create(AIRobot* robot,
                      const std::string& algorithm,
                      const std::string& name);

private:
    static AI* createChaseShootAI(AIRobot* robot,
                                  const std::string& name);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
