#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_blast_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BlastSkillTemplate::BlastSkillTemplate()
    : SkillTemplate()
    , missileTemplate_(nullptr)
    , keepAlive_(false)
{
}

BlastSkillTemplate::BlastSkillTemplate(const rapidjson::Value& v,
                                       const MissileTemplateLib& missileLib,
                                       const std::string& skillDataDir)
{
    init(v, missileLib, skillDataDir);
}

void BlastSkillTemplate::init(const rapidjson::Value& v,
                              const MissileTemplateLib& missileLib,
                              const std::string& skillDataDir)
{
    SkillTemplate::init(SkillType::BLAST, v);

    std::string missileName, firePosFile, fireDirectionFile;
    std::vector<JsonParamPtr> params{
        jsonParam(firePosFile, "firePosFile", true, k_nonEmptyStrV),
        jsonParam(fireDirectionFile, "fireDirectionFile", true, k_nonEmptyStrV),
        jsonParam(missileName, "missile", true, k_nonEmptyStrV),
        jsonParam(keepAlive_, "keepAlive", false),
    };

    parse(params, v);

    readFirePosDirections(firePosFile, fireDirectionFile, skillDataDir);

    missileTemplate_ = missileLib.search(missileName);
    if (!missileTemplate_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Cannot find missile template " + missileName);
    }
}

void BlastSkillTemplate::readFirePosDirections(
                                const std::string& firePosFile,
                                const std::string& fireDirectionFile,
                                const std::string& skillDataDir)
{
    readList(firePoints_, constructPath({skillDataDir, firePosFile}));
    readList(fireDirections_, constructPath({skillDataDir, fireDirectionFile}));

    if (firePoints_.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "firePoints is empty");
    }

    if (fireDirections_.size() != firePoints_.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "fireDirections don't match firePoints");
    }
}

} // end of namespace botlib
} // end of namespace mcdane
