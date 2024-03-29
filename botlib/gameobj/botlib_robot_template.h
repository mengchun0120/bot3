#ifndef INCLUDED_BOTLIB_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_ROBOT_TEMPLATE_H

#include <botlib_skill_template.h>
#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class MissileTemplate;

class RobotTemplate: public CompositeObjectTemplate {
public:
    RobotTemplate();

    ~RobotTemplate() override = default;

    void init(const std::string &name,
              const rapidjson::Value &v,
              const MissileTemplateLib &missileTemplateLib,
              const ComponentTemplateLib &componentTemplateLib,
              const SkillTemplateLib &skillTemplateLib);

    inline float hp() const;

    inline float armor() const;

    inline float speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline const MissileTemplate *missileTemplate() const;

    inline float dyingDuration() const;

    inline const std::vector<const SkillTemplate*> skills() const;

    inline const SkillTemplate *defaultSkill() const;

    inline float touchRadius() const;

    inline float touchRadiusSquare() const;

private:
    void initSkills(const std::vector<std::string> &skillNames,
                    const std::string &defaultSkillName,
                    const SkillTemplateLib &skillTemplateLib);

protected:
    float hp_;
    float armor_;
    float speed_;
    float energy_;
    float rechargeRate_;
    const MissileTemplate *missileTemplate_;
    float dyingDuration_;
    std::vector<const SkillTemplate*> skills_;
    const SkillTemplate *defaultSkill_;
    float touchRadius_;
    float touchRadiusSquare_;
};

float RobotTemplate::hp() const
{
    return hp_;
}

float RobotTemplate::armor() const
{
    return armor_;
}

float RobotTemplate::speed() const
{
    return speed_;
}

float RobotTemplate::energy() const
{
    return energy_;
}

float RobotTemplate::rechargeRate() const
{
    return rechargeRate_;
}

const MissileTemplate *RobotTemplate::missileTemplate() const
{
    return missileTemplate_;
}

float RobotTemplate::dyingDuration() const
{
    return dyingDuration_;
}

const std::vector<const SkillTemplate*> RobotTemplate::skills() const
{
    return skills_;
}

const SkillTemplate *RobotTemplate::defaultSkill() const
{
    return defaultSkill_;
}

float RobotTemplate::touchRadius() const
{
    return touchRadius_;
}

float RobotTemplate::touchRadiusSquare() const
{
    return touchRadiusSquare_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

