#ifndef INCLUDED_BOTLIB_BARRAGE_BLAST_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_BARRAGE_BLAST_SKILL_TEMPLATE_H

#include <string>
#include <vector>
#include <commonlib_vector.h>
#include <botlib_skill_with_cost_template.h>

namespace mcdane {
namespace botlib {

class BarrageBlastSkillTemplate: public SkillWithCostTemplate {
public:
    BarrageBlastSkillTemplate();

    BarrageBlastSkillTemplate(
              const rapidjson::Value& v,
              const ProgressPieTemplateLib& progressPieLib,
              const std::string& skillDataDir);

    void init(const rapidjson::Value& v,
              const ProgressPieTemplateLib& progressPieLib,
              const std::string& skillDataDir);

    inline const std::vector<commonlib::Vector2>& firePoints() const;

    inline const std::vector<commonlib::Vector2>& fireDirections() const;

    inline int maxShootTimes() const;

    inline float shootInterval() const;

private:
    void readFirePosDirections(const std::string& firePosFile,
                               const std::string& fireDirectionFile,
                               const std::string& skillDataDir);

private:
    std::vector<commonlib::Vector2> firePoints_;
    std::vector<commonlib::Vector2> fireDirections_;
    int maxShootTimes_;
    float shootInterval_;
};

const std::vector<commonlib::Vector2>&
BarrageBlastSkillTemplate::firePoints() const
{
    return firePoints_;
}

const std::vector<commonlib::Vector2>&
BarrageBlastSkillTemplate::fireDirections() const
{
    return fireDirections_;
}

int BarrageBlastSkillTemplate::maxShootTimes() const
{
    return maxShootTimes_;
}

float BarrageBlastSkillTemplate::shootInterval() const
{
    return shootInterval_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
