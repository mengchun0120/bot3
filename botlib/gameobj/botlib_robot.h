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

    inline const commonlib::Vector2& speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline bool movingEnabled() const;

    inline float hpRatio() const;

    inline float fireIntervalMS() const;

    inline bool shootingEnabled() const;

    void present() const override;

    void update(GameMap& map,
                float timeDelta) override;

    void shiftPos(const commonlib::Vector2& delta) override;

    void setDirection(const commonlib::Vector2& direction1) override;

    void setMovingEnabled(bool b);

    void addHP(float delta);

    void setShootingEnabled(bool b);

    std::string toString() const override;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

protected:
    void initFirePointsAndDirections();

    void shiftFirePoints(const commonlib::Vector2& delta);

    void resetFirePointsAndDirections();

    void resetSpeed();

    void updatePos(GameMap& map,
                   float timeDelta);

    bool checkNonpassthroughCollide(commonlib::Vector2& delta,
                                    GameMap& map);

    void checkCollideMissile(GameMap& map);

    void updateShooting(GameMap& map);

    bool canShoot(const commonlib::TimePoint& t);

    void shoot(GameMap& map,
               const commonlib::TimePoint& t);

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
    commonlib::TimePoint lastShootTime_;
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
    return getTemplate()->armor();
}

float Robot::speedNorm() const
{
    return getTemplate()->speed();
}

const commonlib::Vector2& Robot::speed() const
{
    return speed_;
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

float Robot::hpRatio() const
{
    return hp_ / getTemplate()->hp();
}

float Robot::fireIntervalMS() const
{
    return getTemplate()->fireIntervalMS();
}

bool Robot::shootingEnabled() const
{
    return shootingEnabled_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

