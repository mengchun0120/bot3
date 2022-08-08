#ifndef INCLUDED_BOTLIB_ROBOT_H
#define INCLUDED_BOTLIB_ROBOT_H

#include <commonlib_time_utils.h>
#include <botlib_side.h>
#include <botlib_hp_indicator.h>
#include <botlib_robot_template.h>
#include <botlib_composite_object.h>

namespace mcdane {
namespace botlib {

class Robot: public CompositeObject {
public:
    Robot();

    ~Robot() override = default;

    void init(const RobotTemplate* t,
              Side side,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline const RobotTemplate* getTemplate() const;

    inline Side side() const;

    inline float hp() const;

    inline float armor() const;

    inline float speedNorm() const;

    inline float damageFactor() const;

    inline const commonlib::Vector2& speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline bool movingEnabled() const;

    inline float hpRatio() const;

    inline float armorRatio() const;

    inline float energyRatio() const;

    inline float fireIntervalMS() const;

    inline bool shootingEnabled() const;

    void present() const override;

    void update(UpdateContext& cxt) override;

    void shiftPos(const commonlib::Vector2& delta) override;

    void setDirection(const commonlib::Vector2& direction1) override;

    void setMovingEnabled(bool b);

    void addHP(float delta);

    void doDamage(float damage, UpdateContext& cxt);

    void setShootingEnabled(bool b);

    bool canBeDumped(GameMap& map) const override;

    void setSpeedNorm(float speedNorm1);

    void setFireIntervalMS(float fireIntervalMS1);

    void setArmor(float armor1);

    void setDamageFactor(float factor);

    void resetSpeed();

protected:
    void initFirePointsAndDirections();

    void shiftFirePoints(const commonlib::Vector2& delta);

    void resetFirePointsAndDirections();

    void updatePos(UpdateContext& cxt);

    void updateShooting(UpdateContext& cxt);

    void checkPassthroughCollide(UpdateContext& cxt);

    void shoot(UpdateContext& cxt);

    void resetArmorReduceRatio();

    void updateEnergy(float timeDelta);

protected:
    Side side_;
    float hp_;
    float energy_;
    std::vector<commonlib::Vector2> firePoints_;
    std::vector<commonlib::Vector2> fireDirections_;
    bool movingEnabled_;
    commonlib::Vector2 speed_;
    HPIndicator hpIndicator_;
    bool shootingEnabled_;
    float timeSinceLastShoot_;
    float dyingTime_;
    float fireIntervalMS_;
    float speedNorm_;
    float armor_;
    float damageFactor_;
    float armorReduceRatio_;
};

const RobotTemplate* Robot::getTemplate() const
{
    return static_cast<const RobotTemplate*>(t_);
}

Side Robot::side() const
{
    return side_;
}

float Robot::hp() const
{
    return hp_;
}

float Robot::armor() const
{
    return armor_;
}

float Robot::speedNorm() const
{
    return speedNorm_;
}

const commonlib::Vector2& Robot::speed() const
{
    return speed_;
}

float Robot::energy() const
{
    return energy_;
}

float Robot::damageFactor() const
{
    return damageFactor_;
}

float Robot::rechargeRate() const
{
    return getTemplate()->rechargeRate();
}

bool Robot::movingEnabled() const
{
    return movingEnabled_;
}

float Robot::hpRatio() const
{
    return hp_ / getTemplate()->hp();
}

float Robot::armorRatio() const
{
    return armor_ / getTemplate()->armor();
}

float Robot::energyRatio() const
{
    return energy_ / getTemplate()->energy();
}


float Robot::fireIntervalMS() const
{
    return fireIntervalMS_;
}

bool Robot::shootingEnabled() const
{
    return shootingEnabled_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

