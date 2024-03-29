#include <utility>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RobotTemplate::RobotTemplate()
    : hp_(0.0f)
    , armor_(0.0f)
    , speed_(0.0f)
    , energy_(0.0f)
    , rechargeRate_(0.0f)
    , missileTemplate_(nullptr)
    , dyingDuration_(0.0f)
    , defaultSkill_(nullptr)
    , touchRadius_(0.0f)
    , touchRadiusSquare_(0.0f)
{
}

void RobotTemplate::init(const std::string &name,
                         const rapidjson::Value &v,
                         const MissileTemplateLib &missileTemplateLib,
                         const ComponentTemplateLib &componentTemplateLib,
                         const SkillTemplateLib &skillTemplateLib)
{
    std::string missileName, defaultSkillName;
    std::vector<std::string> skillNames;
    std::vector<JsonParamPtr> params{
        jsonParam(hp_, "hp", true, ge(0.0f)),
        jsonParam(armor_, "armor", true, ge(0.0f)),
        jsonParam(energy_, "energy", true, ge(0.0f)),
        jsonParam(speed_, "speed", true, ge(0.0f)),
        jsonParam(rechargeRate_, "rechargeRate", true, ge(0.0f)),
        jsonParam(missileName, "missile", true, k_nonEmptyStrV),
        jsonParam(dyingDuration_, "dyingDuration", true, gt(0.0f)),
        jsonParam(skillNames, "skills", true),
        jsonParam(defaultSkillName, "defaultSkill", false, k_nonEmptyStrV),
        jsonParam(touchRadius_, "touchRadius", false, ge(0.0f)),
    };

    parse(params, v);

    missileTemplate_ = missileTemplateLib.search(missileName);
    if (!missileTemplate_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find MissileTemplate " + missileName);
    }

    initSkills(skillNames, defaultSkillName, skillTemplateLib);

    CompositeObjectTemplate::init(GameObjectType::ROBOT, name,
                                  v, componentTemplateLib);

    touchRadiusSquare_ = touchRadius_ * touchRadius_;
}

void RobotTemplate::initSkills(const std::vector<std::string> &skillNames,
                               const std::string &defaultSkillName,
                               const SkillTemplateLib &skillTemplateLib)
{
    if (skillNames.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "Skills is empty");
    }

    defaultSkill_ = nullptr;
    skills_.resize(skillNames.size());
    for (std::size_t i = 0; i < skills_.size(); ++i)
    {
        auto t = skillTemplateLib.search(skillNames[i]);
        if (!t)
        {
            THROW_EXCEPT(InvalidArgumentException, "Invalid skill " + skillNames[i]);
        }

        skills_[i] = t->get();

        if (defaultSkillName == skillNames[i])
        {
            defaultSkill_ = skills_[i];
        }
    }
}

} // end of namespace botlib
} // end of namespace mcdane

