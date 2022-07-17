#ifndef INCLUDED_BOTLIB_CHASE_SHOOT_AI_H
#define INCLUDED_BOTLIB_CHASE_SHOOT_AI_H

#include <random>
#include <botlib_robot_action.h>
#include <botlib_ai.h>

namespace mcdane {
namespace botlib {

class ChaseShootAIParam;
class Player;

class ChaseShootAI: public AI {
public:
    ChaseShootAI();

    void init(const ChaseShootAIParam* params);

    void apply(AIRobot& robot,
               GameMap& map,
               float timeDelta) override;

private:
    void tryChangeAction(AIRobot& robot,
                         const Player* player);

    void resetAction(AIRobot& robot,
                     RobotAction action);

    void resetDirection(AIRobot& robot,
                        const commonlib::Vector2& direction);

    void applyAction(AIRobot& robot,
                     GameMap& map,
                     float timeDelta);

    void applyChaseAction(AIRobot& robot,
                          GameMap& map,
                          float timeDelta);

    void applyShootAction(AIRobot& robot,
                          GameMap& map,
                          float timeDelta);

    bool findChaseDirection(AIRobot& robot,
                            GameMap& map,
                            float timeDelta);

    bool tryFirstDirection(commonlib::Vector2& direction,
                           AIRobot& robot,
                           GameMap& map,
                           float timeDelta);

    int findNewDirection(AIRobot& robot,
                         GameMap& map,
                         float timeDelta,
                         const commonlib::Vector2& refDirection);

    void sortDirections(int* result,
                       const commonlib::Vector2& refDirection);

    void randomChoose(int* result,
                      int i1,
                      int i2);

private:
    static constexpr int NUM_DIRECTIONS = 4;
    const ChaseShootAIParam* params_;
    std::mt19937 generator_;
    std::uniform_real_distribution<float> distribution_;
    RobotAction action_;
    float timeSinceLastActionChange_;
    float timeSinceLastDirectionChange_;
    std::vector<commonlib::Vector2> directions_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

