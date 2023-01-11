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

void ChaseShootAI::init(AIRobot* robot,
                        const ChaseShootAIParam* params)
{
    AI::init(robot);
    checkSkill();
    params_ = params;
    generator_.seed(time(nullptr));
    action_ = RobotAction::NONE;
    timeSinceLastDirectionChange_ = 0.0f;
}

void ChaseShootAI::apply(GameMap& map,
                         float timeDelta)
{
    timeSinceLastActionChange_ += timeDelta;
    timeSinceLastDirectionChange_ += timeDelta;

    if (!map.canSee(robot_))
    {
        resetAction(RobotAction::NONE);
        return;
    }

    tryChangeAction(map.player());
    applyAction(map, timeDelta);
}

void ChaseShootAI::checkSkill()
{
    if (robot_->searchSkill(SkillType::SHOOT_MISSILE) == nullptr)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Robot doesn't have SHOOT_MISSILE skill");
    }
}

void ChaseShootAI::tryChangeAction(const Player* player)
{
    bool rollDice = false;
    float d = dist(robot_->pos(), player->pos());

    switch (action_)
    {
        case RobotAction::NONE:
        {
            if (d <= params_->stopChaseDist())
            {
                resetAction(RobotAction::SHOOT);
                return;
            }

            rollDice = true;

            break;
        }
        case RobotAction::CHASE:
        {
            if (d <= params_->stopChaseDist())
            {
                resetAction(RobotAction::SHOOT);
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
    resetAction(newAction);
}

void ChaseShootAI::resetAction(RobotAction action)
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
            robot_->setShootingEnabled(false);
            robot_->setMovingEnabled(false);
            break;
        }
        case RobotAction::CHASE:
        {
            robot_->setShootingEnabled(false);
            robot_->setMovingEnabled(true);
            break;
        }
        case RobotAction::SHOOT:
        {
            robot_->setMovingEnabled(false);
            robot_->setShootingEnabled(true);
            break;
        }
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid action");
    }
}

void ChaseShootAI::resetDirection(const commonlib::Vector2& direction)
{
    robot_->setDirection(direction);
    timeSinceLastDirectionChange_ = 0.0f;
}

void ChaseShootAI::applyAction(GameMap& map,
                               float timeDelta)
{
    switch(action_)
    {
        case RobotAction::CHASE:
        {
            applyChaseAction(map, timeDelta);
            break;
        }
        case RobotAction::SHOOT:
        {
            applyShootAction(map, timeDelta);
            break;
        }
        default:
            break;
    }
}

void ChaseShootAI::applyChaseAction(GameMap& map,
                                    float timeDelta)
{
    Vector2 delta = timeDelta * robot_->speed();
    bool collide = map.checkCollision(delta, robot_);
    bool changeDirection =
                collide ||
                timeSinceLastDirectionChange_ > params_->directionChangeInterval();

    if (!changeDirection)
    {
        return;
    }

    if (!findChaseDirection(map, timeDelta))
    {
        resetAction(RobotAction::SHOOT);
    }
}

void ChaseShootAI::applyShootAction(GameMap& map,
                                    float timeDelta)
{
    Vector2 direction = normalize(map.player()->pos() - robot_->pos());
    resetDirection(direction);
}

bool ChaseShootAI::findChaseDirection(GameMap& map,
                                      float timeDelta)
{
    Vector2 refDirection;

    if (tryFirstDirection(refDirection, map, timeDelta))
    {
        return true;
    }

    int index = findNewDirection(map, timeDelta, refDirection);
    if (index < 0)
    {
        return false;
    }

    resetDirection(directions_[index]);
    return true;
}

bool ChaseShootAI::tryFirstDirection(Vector2& direction,
                                     GameMap& map,
                                     float timeDelta)
{
    direction = normalize(map.player()->pos() - robot_->pos());

    Vector2 delta = direction * (robot_->speedNorm() * timeDelta);

    if (map.checkCollision(delta, robot_))
    {
        return false;
    }

    resetDirection(direction);
    return true;
}

int ChaseShootAI::findNewDirection(GameMap& map,
                                   float timeDelta,
                                   const Vector2& refDirection)
{
    int tryDirections[NUM_DIRECTIONS];
    float distDelta = robot_->speedNorm() * timeDelta;

    sortDirections(tryDirections, refDirection);
    for (int i = 0; i < NUM_DIRECTIONS; ++i)
    {
        Vector2 delta = distDelta * directions_[tryDirections[i]];
        if (!map.checkCollision(delta, robot_))
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

