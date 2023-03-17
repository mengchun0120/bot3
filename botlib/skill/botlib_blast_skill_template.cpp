#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_blast_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BlastSkillTemplate::BlastSkillTemplate()
    : SkillWithCostTemplate()
{
}

BlastSkillTemplate::BlastSkillTemplate(const rapidjson::Value &v,
                                       const ProgressPieTemplateLib &progressPieLib,
                                       const std::string &skillDataDir)
{
    init(v, progressPieLib, skillDataDir);
}

void BlastSkillTemplate::init(const rapidjson::Value &v,
                              const ProgressPieTemplateLib &progressPieLib,
                              const std::string &skillDataDir)
{
    SkillWithCostTemplate::init(SkillType::BLAST, v, progressPieLib);

    std::string firePosFile, fireDirectionFile;
    std::vector<JsonParamPtr> params{
        jsonParam(firePosFile, "firePosFile", true, k_nonEmptyStrV),
        jsonParam(fireDirectionFile, "fireDirectionFile", true, k_nonEmptyStrV),
    };

    parse(params, v);

    readFirePosDirections(firePosFile, fireDirectionFile, skillDataDir);
}

void BlastSkillTemplate::readFirePosDirections(
                                const std::string &firePosFile,
                                const std::string &fireDirectionFile,
                                const std::string &skillDataDir)
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
