#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_barrage_blast_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BarrageBlastSkillTemplate::BarrageBlastSkillTemplate()
    : SkillWithCostTemplate()
    , maxShootTimes_(0)
    , shootInterval_(0.0f)
{
}

BarrageBlastSkillTemplate::BarrageBlastSkillTemplate(
                            const rapidjson::Value &v,
                            const ProgressPieTemplateLib &progressPieLib,
                            const std::string &skillDataDir)
{
    init(v, progressPieLib, skillDataDir);
}

void BarrageBlastSkillTemplate::init(
                            const rapidjson::Value &v,
                            const ProgressPieTemplateLib &progressPieLib,
                            const std::string &skillDataDir)
{
    SkillWithCostTemplate::init(SkillType::BARRAGE_BLAST, v, progressPieLib);

    std::string firePosFile, fireDirectionFile;
    std::vector<JsonParamPtr> params{
        jsonParam(maxShootTimes_, "maxShootTimes", true, gt(0)),
        jsonParam(shootInterval_, "shootInterval", true, gt(0.0f)),
        jsonParam(firePosFile, "firePosFile", true, k_nonEmptyStrV),
        jsonParam(fireDirectionFile, "fireDirectionFile", true, k_nonEmptyStrV),
    };

    parse(params, v);

    readFirePosDirections(firePosFile, fireDirectionFile, skillDataDir);
}

void BarrageBlastSkillTemplate::readFirePosDirections(
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
