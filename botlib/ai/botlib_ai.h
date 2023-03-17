#ifndef INCLUDED_BOTLIB_AI_H
#define INCLUDED_BOTLIB_AI_H

namespace mcdane {
namespace botlib {

class AIRobot;
class GameMap;

class AI {
public:
    AI() = default;

    virtual ~AI() = default;

    void init(AIRobot *robot);

    virtual void apply(GameMap &map,
                       float timeDelta) = 0;

protected:
    AIRobot *robot_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

