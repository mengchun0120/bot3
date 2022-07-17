#include <ctime>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_ai_robot.h>
#include <botlib_player.h>
#include <botlib_game_map.h>
#include <botlib_chase_shoot_ai_param.h>
#include <botlib_chase_shoot_ai.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ChaseShootAI::ChaseShootAI()
    : distribution_(0.0f, 1.0f)
    , directions_{{1.0f, 0.0f}, {0.0f, 1.0f}, {-1.0f, 0.0f}, {0.0f, -1.0f}}
{
}

void ChaseShootAI::init(const ChaseShootAIParam* params)
{
    params_ = params;
    generator_.seed(time(nullptr));
    action_ = RobotAction::NONE;
    timeSinceLastDirectionChange_ = 0.0f;
}

void ChaseShootAI::apply(AIRobot& robot,
                         GameMap& map,
                         float timeDelta)
{
    timeSinceLastActionChange_ += timeDelta;
    timeSinceLastDirectionChange_ += timeDelta;

    if (!map.canSee(&robot))
    {
        resetAction(robot, RobotAction::NONE);
        return;
    }

    tryChangeAction(robot, map.player());
    applyAction(robot, map, timeDelta);
}

void ChaseShootAI::tryChangeAction(AIRobot& robot,
                                   const Player* player)
{
    bool rollDice = false;
    float d = dist(robot.pos(), player->pos());

    switch (action_)
    {
        case RobotAction::NONE:
        {
            if (d <= params_->stopChaseDist())
            {
                resetAction(robot, RobotAction::SHOOT);
                return;
            }

            rollDice = true;

            break;
        }
        case RobotAction::CHASE:
        {
            if (d <= params_->stopChaseDist())
            {
                resetAction(robot, RobotAction::SHOOT);
                return;
            }

            if (timeSinceLastActionChange_ >= params_->chaseDuration())
            {
                rollDice = true;
            }

            break;
        }
        case RobotAction::SHOOT:
        {
            rollDice = d > params_->stopChaseDist() ||
                       timeSinceLastActionChange_ >= params_->shootDuration();
            break;
        }
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid action");
            break;
    }

    if (!rollDice)
    {
        return;
    }

    RobotAction newAction = distribution_(generator_) <= params_->chaseProb() ?
                                    RobotAction::CHASE : RobotAction::SHOOT;
    resetAction(robot, newAction);
}

void ChaseShootAI::resetAction(AIRobot& robot,
                               RobotAction action)
{
    if (action_ == action)
    {
        return;
    }

    action_ = action;
    timeSinceLastActionChange_ = 0.0f;

    switch(action_)
    {
        case RobotAction::NONE:
        {
            robot.setShootingEnabled(false);
            robot.setMovingEnabled(false);
            break;
        }
        case RobotAction::CHASE:
        {
            robot.setShootingEnabled(false);
            robot.setMovingEnabled(true);
            break;
        }
        case RobotAction::SHOOT:
        {
            robot.setMovingEnabled(false);
            robot.setShootingEnabled(true);
            break;
        }
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid action");
    }
}

void ChaseShootAI::resetDirection(AIRobot& robot,
                                  const commonlib::Vector2& direction)
{
    robot.setDirection(direction);
    timeSinceLastDirectionChange_ = 0.0f;
}

void ChaseShootAI::applyAction(AIRobot& robot,
                               GameMap& map,
                               float timeDelta)
{
    switch(action_)
    {
        case RobotAction::CHASE:
        {
            applyChaseAction(robot, map, timeDelta);
            break;
        }
        case RobotAction::SHOOT:
        {
            applyShootAction(robot, map, timeDelta);
            break;
        }
        default:
            break;
    }
}

void ChaseShootAI::applyChaseAction(AIRobot& robot,
                                    GameMap& map,
                                    float timeDelta)
{
    Vector2 delta = timeDelta * robot.speed();
    bool collide = map.checkCollision(delta, &robot);
    bool changeDirection =
                collide ||
                timeSinceLastDirectionChange_ > params_->directionChangeInterval();

    if (!changeDirection)
    {
        return;
    }

    if (!findChaseDirection(robot, map, timeDelta))
    {
        resetAction(robot, RobotAction::SHOOT);
    }
}

void ChaseShootAI::applyShootAction(AIRobot& robot,
                                    GameMap& map,
                                    float timeDelta)
{
    Vector2 direction = normalize(map.player()->pos() - robot.pos());
    resetDirection(robot, direction);
}

bool ChaseShootAI::findChaseDirection(AIRobot& robot,
                                      GameMap& map,
                                      float timeDelta)
{
    Vector2 refDirection;

    if (tryFirstDirection(refDirection, robot, map, timeDelta))
    {
        return true;
    }

    int index = findNewDirection(robot, map, timeDelta, refDirection);
    if (index < 0)
    {
        return false;
    }

    resetDirection(robot, directions_[index]);
    return true;
}

bool ChaseShootAI::tryFirstDirection(Vector2& direction,
                                     AIRobot& robot,
                                     GameMap& map,
                                     float timeDelta)
{
    direction = normalize(map.player()->pos() - robot.pos());

    Vector2 delta = direction * (robot.speedNorm() * timeDelta);

    if (map.checkCollision(delta, &robot))
    {
        return false;
    }

    resetDirection(robot, direction);
    return true;
}

int ChaseShootAI::findNewDirection(AIRobot& robot,
                                   GameMap& map,
                                   float timeDelta,
                                   const Vector2& refDirection)
{
    int tryDirections[NUM_DIRECTIONS];
    float distDelta = robot.speedNorm() * timeDelta;

    sortDirections(tryDirections, refDirection);
    for (int i = 0; i < NUM_DIRECTIONS; ++i)
    {
        Vector2 delta = distDelta * directions_[tryDirections[i]];
        if (!map.checkCollision(delta, &robot))
        {
            return tryDirections[i];
        }
    }

    return -1;
}

void ChaseShootAI::sortDirections(int* result,
                                 const Vector2& refDirection)
{
    int i, j;

    for (i = 0; i < NUM_DIRECTIONS; ++i)
    {
        j = (i + 1) % NUM_DIRECTIONS;

        auto& d2 = directions_[j];
        auto& d1 = directions_[i];
        bool isBetween =
            between(refDirection[0], d1[0], d2[0]) &&
            between(refDirection[1], d1[1], d2[1]);

        if (isBetween)
        {
            break;
        }
    }

    randomChoose(result, i, j);
    i = (i - 1) % NUM_DIRECTIONS;
    j = (j + 1) % NUM_DIRECTIONS;
    randomChoose(result + 2, i, j);
}

void ChaseShootAI::randomChoose(int* result,
                                int i1,
                                int i2)
{
    float dice = distribution_(generator_);

    if (dice < 0.5f)
    {
        *result = i1;
        *(result + 1) = i2;
    }
    else
    {
        *result = i2;
        *(result + 1) = i1;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

