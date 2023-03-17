#ifndef INCLUDED_BOTLIB_ROBOT_H
#define INCLUDED_BOTLIB_ROBOT_H

#include <vector>
#include <commonlib_time_utils.h>
#include <commonlib_linked_item.h>
#include <commonlib_linked_list.h>
#include <botlib_side.h>
#include <botlib_hp_indicator.h>
#include <botlib_robot_template.h>
#include <botlib_skill.h>
#include <botlib_composite_object.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class Robot: public CompositeObject {
public:
    using SkillList = std::vector<Skill*>;

public:
    Robot();

    ~Robot() override;

    void init(const RobotTemplate *t,
              Side side,
              const commonlib::Vector2 &pos1,
              const commonlib::Vector2 &direction1);

    inline const RobotTemplate *getTemplate() const;

    inline Side side() const;

    inline float hp() const;

    inline float armor() const;

    inline float speedNorm() const;

    inline float damageFactor() const;

    inline const commonlib::Vector2 &speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline float hpRatio() const;

    inline float armorRatio() const;

    inline float energyRatio() const;

    inline float fireIntervalMS() const;

    void present() const override;

    void update(UpdateContext &cxt) override;

    void shiftPos(const commonlib::Vector2 &delta) override;

    void setDirection(const commonlib::Vector2 &direction1) override;

    void addHP(float delta);

    void addEnergy(float delta);

    void doDamage(float damage, UpdateContext &cxt);

    bool canBeDumped(GameMap &map) const override;

    void setSpeedNorm(float speedNorm1);

    void setArmor(float armor1);

    void setDamageFactor(float factor);

    void resetSpeed();

    void removeMonitor(GameObject *obj);

    Skill *searchSkill(SkillType skillType);

    bool isSkillEnabled(SkillType skillType);

    bool setSkillEnabled(SkillType skillType, bool enabled);

    void shoot(UpdateContext &cxt);

    inline int skillCount() const;

    inline Skill *skill(int i);

protected:
    void initSkills();

    void updateAlive(UpdateContext &cxt);

    void updateDying(UpdateContext &cxt);

    void updateSkills(UpdateContext &cxt);

    void resetArmorReduceRatio();

    void updateEnergy(float timeDelta);

protected:
    Side side_;
    float hp_;
    float energy_;
    commonlib::Vector2 speed_;
    HPIndicator hpIndicator_;
    float timeSinceLastShoot_;
    float dyingTime_;
    float speedNorm_;
    float armor_;
    float damageFactor_;
    float armorReduceRatio_;
    SkillList skills_;
};

const RobotTemplate *Robot::getTemplate() const
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

const commonlib::Vector2 &Robot::speed() const
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

int Robot::skillCount() const
{
    return static_cast<int>(skills_.size());
}

Skill *Robot::skill(int i)
{
    return skills_[i];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

