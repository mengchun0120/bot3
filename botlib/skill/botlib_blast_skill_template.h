#ifndef INCLUDED_BOTLIB_BLAST_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_BLAST_SKILL_TEMPLATE_H

#include <string>
#include <vector>
#include <commonlib_vector.h>
#include <botlib_skill_with_cost_template.h>

namespace mcdane {
namespace botlib {

class BlastSkillTemplate: public SkillWithCostTemplate {
public:
    BlastSkillTemplate();

    BlastSkillTemplate(const rapidjson::Value& v,
                       const ProgressPieTemplateLib& progressPieLib,
                       const std::string& skillDataDir);

    void init(const rapidjson::Value& v,
              const ProgressPieTemplateLib& progressPieLib,
              const std::string& skillDataDir);

    inline const std::vector<commonlib::Vector2>& firePoints() const;

    inline const std::vector<commonlib::Vector2>& fireDirections() const;

private:
    void readFirePosDirections(const std::string& firePosFile,
                               const std::string& fireDirectionFile,
                               const std::string& skillDataDir);

protected:
    std::vector<commonlib::Vector2> firePoints_;
    std::vector<commonlib::Vector2> fireDirections_;
};

const std::vector<commonlib::Vector2>& BlastSkillTemplate::firePoints() const
{
    return firePoints_;
}

const std::vector<commonlib::Vector2>& BlastSkillTemplate::fireDirections() const
{
    return fireDirections_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
