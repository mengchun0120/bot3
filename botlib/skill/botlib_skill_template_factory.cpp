#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_move_skill_template.h>
#include <botlib_shoot_missile_skill_template.h>
#include <botlib_blast_skill_template.h>
#include <botlib_targeted_blast_skill_template.h>
#include <botlib_skill_template_factory.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillTemplate* SkillTemplateFactory::create(const rapidjson::Value& v,
                                            const MissileTemplateLib& missileLib,
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
            return new ShootMissileSkillTemplate(v);
        }
        case SkillType::BLAST:
        {
            return new BlastSkillTemplate(v, missileLib, skillDataDir);
        }
        case SkillType::TARGETED_BLAST:
        {
            return new TargetedBlastSkillTemplate(v, missileLib);
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
