#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_move_skill_template.h>
#include <botlib_shoot_missile_skill_template.h>
#include <botlib_blast_skill_template.h>
#include <botlib_targeted_blast_skill_template.h>
#include <botlib_barrage_skill_template.h>
#include <botlib_barrage_blast_skill_template.h>
#include <botlib_move_skill.h>
#include <botlib_shoot_missile_skill.h>
#include <botlib_blast_skill.h>
#include <botlib_targeted_blast_skill.h>
#include <botlib_barrage_skill.h>
#include <botlib_barrage_blast_skill.h>
#include <botlib_skill_utils.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillTemplate* createSkillTemplate(const rapidjson::Value& v,
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
            return new MoveSkillTemplate(v);
        }
        case SkillType::SHOOT_MISSILE:
        {
            return new ShootMissileSkillTemplate(v, progressPieLib);
        }
        case SkillType::BLAST:
        {
            return new BlastSkillTemplate(v, progressPieLib, skillDataDir);
        }
        case SkillType::TARGETED_BLAST:
        {
            return new TargetedBlastSkillTemplate(v, progressPieLib);
        }
        case SkillType::BARRAGE:
        {
            return new BarrageSkillTemplate(v, progressPieLib);
        }
        case SkillType::BARRAGE_BLAST:
        {
            return new BarrageBlastSkillTemplate(v, progressPieLib, skillDataDir);
        }
        default:
        {
            std::string typeStr = std::to_string(static_cast<int>(type));
            THROW_EXCEPT(InvalidArgumentException, "Invalid skill " + typeStr);
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
        case SkillType::BARRAGE:
        {
            return new BarrageSkill(
                            static_cast<const BarrageSkillTemplate*>(t),
                            robot);
        }
        case SkillType::BARRAGE_BLAST:
        {
            return new BarrageBlastSkill(
                            static_cast<const BarrageBlastSkillTemplate*>(t),
                            robot);
        }
        default:
        {
            std::string typeStr = std::to_string(static_cast<int>(t->type()));
            THROW_EXCEPT(InvalidArgumentException, "Invalid skill " + typeStr);
        }
    }

    return nullptr;
}

} // end of namespace botlib
} // end of namespace mcdane
