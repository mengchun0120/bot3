#ifndef INCLUDED_BOTLIB_AI_H
#define INCLUDED_BOTLIB_AI_H

namespace mcdane {
namespace botlib {

class AIRobot;
class GameMap;

class AI {
public:
    static AI* create(const std::string& algorithm,
                      const std::string& name);

    AI() = default;

    virtual ~AI() = default;

    virtual void apply(AIRobot& robot,
                       GameMap& map,
                       float timeDelta) = 0;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

