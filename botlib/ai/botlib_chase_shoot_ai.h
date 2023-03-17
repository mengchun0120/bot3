#ifndef INCLUDED_BOTLIB_CHASE_SHOOT_AI_H
#define INCLUDED_BOTLIB_CHASE_SHOOT_AI_H

#include <random>
#include <botlib_robot_action.h>
#include <botlib_ai.h>

namespace mcdane {
namespace botlib {

class ChaseShootAIParam;
class MoveSkill;
class ShootMissileSkill;
class Player;

class ChaseShootAI: public AI {
public:
    ChaseShootAI();

    void init(AIRobot *robot,
              const ChaseShootAIParam *params);

    void apply(GameMap &map,
               float timeDelta) override;

private:
    void initSkills();

    void tryChangeAction(const Player *player);

    void resetAction(RobotAction action);

    void resetDirection(const commonlib::Vector2 &direction);

    void applyAction(GameMap &map,
                     float timeDelta);

    void applyChaseAction(GameMap &map,
                          float timeDelta);

    void applyShootAction(GameMap &map,
                          float timeDelta);

    bool findChaseDirection(GameMap &map,
                            float timeDelta);

    bool tryFirstDirection(commonlib::Vector2 &direction,
                           GameMap &map,
                           float timeDelta);

    int findNewDirection(GameMap &map,
                         float timeDelta,
                         const commonlib::Vector2 &refDirection);

    void sortDirections(int *result,
                       const commonlib::Vector2 &refDirection);

    void randomChoose(int *result,
                      int i1,
                      int i2);

private:
    static constexpr int NUM_DIRECTIONS = 4;
    const ChaseShootAIParam *params_;
    std::mt19937 generator_;
    std::uniform_real_distribution<float> distribution_;
    float timeSinceLastActionChange_;
    float timeSinceLastDirectionChange_;
    std::vector<commonlib::Vector2> directions_;
    MoveSkill *moveSkill_;
    ShootMissileSkill *shootSkill_;
    RobotAction action_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

