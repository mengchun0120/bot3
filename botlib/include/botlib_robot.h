#ifndef INCLUDED_BOTLIB_ROBOT_H
#define INCLUDED_BOTLIB_ROBOT_H

#include <botlib_robot_template.h>
#include <botlib_composite_object.h>

namespace mcdane {
namespace botlib {

class Robot: public CompositeObject {
public:
    Robot();

    ~Robot() override = default;

    void init(const RobotTemplate* t,
              float x,
              float y,
              float directionX,
              float directionY);

    void init(const RobotTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const RobotTemplate* getTemplate() const;

    inline float hp() const;

    inline float armor() const;

    inline float speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline bool movingEnabled() const;

    void update(GameMap& map,
                float timeDelta) override;

    void shiftPos(float deltaX,
                  float deltaY) override;

    void setDirection(float directionX,
                      float directionY) override;

    void setMovingEnabled(bool b);

protected:
    void initFirePointsAndDirections();

    void shiftFirePoints(float deltaX,
                         float deltaY);

    void resetFirePointsAndDirections();

    void resetSpeed();

    void updatePos(GameMap& map,
                   float timeDelta);

    bool checkNonpassthroughCollide(float& adjustedDeltaX,
                                    float& adjustedDeltaY,
                                    GameMap& map,
                                    float deltaX,
                                    float deltaY);

protected:
    float hp_;
    float energy_;
    std::vector<commonlib::Vector2> firePoints_;
    std::vector<commonlib::Vector2> fireDirections_;
    bool movingEnabled_;
    float speedX_;
    float speedY_;
};

const RobotTemplate* Robot::getTemplate() const
{
    return static_cast<const RobotTemplate*>(t_);
}

float Robot::hp() const
{
    return hp_;
}

float Robot::armor() const
{
    return getTemplate()->armor();
}

float Robot::speed() const
{
    return getTemplate()->speed();
}

float Robot::energy() const
{
    return energy_;
}

float Robot::rechargeRate() const
{
    return getTemplate()->rechargeRate();
}

bool Robot::movingEnabled() const
{
    return movingEnabled_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

