#ifndef INCLUDED_BOTLIB_SKILL_UTILS_H
#define INCLUDED_BOTLIB_SKILL_UTILS_H

#include <rapidjson/document.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class SkillTemplate;
class Skill;
class Robot;

SkillTemplate* createSkillTemplate(const rapidjson::Value& v,
                                   const ProgressPieTemplateLib& progressPieLib,
                                   const std::string& skillDataDir);

Skill* createSkill(const SkillTemplate* t, Robot* robot);

} // end of namespace botlib
} // end of namespace mcdane

#endif
