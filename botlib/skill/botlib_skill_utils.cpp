#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_move_skill_template.h>
#include <botlib_shoot_missile_skill_template.h>
#include <botlib_blast_skill_template.h>
#include <botlib_targeted_blast_skill_template.h>
#include <botlib_move_skill.h>
#include <botlib_shoot_missile_skill.h>
#include <botlib_blast_skill.h>
#include <botlib_targeted_blast_skill.h>
#include <botlib_skill_utils.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillTemplate* createSkillTemplate(const rapidjson::Value& v,
                                   const MissileTemplateLib& missileLib,
                                   const ProgressPieTemplateLib& progressPieLib,
                                   const std::string& skillDataDir)
{
    std::string typeStr;
    std::vector<JsonParamPtr> params{
        jsonParam(typeStr, "type", true, k_nonEmptyStrV),
    };

    parse(params, v);

    SkillType type = toSkillType(typeStr);

    switch(type)
    {
        case SkillType::MOVE:
        {
            return new MoveSkillTemplate(v, progressPieLib);
        }
        case SkillType::SHOOT_MISSILE:
        {
            return new ShootMissileSkillTemplate(v, progressPieLib);
        }
        case SkillType::BLAST:
        {
            return new BlastSkillTemplate(v, missileLib, progressPieLib, skillDataDir);
        }
        case SkillType::TARGETED_BLAST:
        {
            return new TargetedBlastSkillTemplate(v, missileLib, progressPieLib);
        }
        default:
        {
            break;
        }
    }

    return nullptr;
}

Skill* createSkill(const SkillTemplate* t, Robot* robot)
{
    switch(t->type())
    {
        case SkillType::MOVE:
        {
            return new MoveSkill(static_cast<const MoveSkillTemplate*>(t),
                                 robot);
        }
        case SkillType::SHOOT_MISSILE:
        {
            return new ShootMissileSkill(
                            static_cast<const ShootMissileSkillTemplate*>(t),
                            robot);
        }
        case SkillType::BLAST:
        {
            return new BlastSkill(static_cast<const BlastSkillTemplate*>(t),
                                  robot);
        }
        case SkillType::TARGETED_BLAST:
        {
            return new TargetedBlastSkill(
                            static_cast<const TargetedBlastSkillTemplate*>(t),
                            robot);
        }
        default:
        {
            break;
        }
    }

    return nullptr;
}

} // end of namespace botlib
} // end of namespace mcdane
