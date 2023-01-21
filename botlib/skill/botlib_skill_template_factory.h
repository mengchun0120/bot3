#ifndef INCLUDED_BOTLIB_SKILL_TEMPLATE_FACTORY_H
#define INCLUDED_BOTLIB_SKILL_TEMPLATE_FACTORY_H

#include <rapidjson/document.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class SkillTemplate;

class SkillTemplateFactory {
public:
    static SkillTemplate* create(const rapidjson::Value& v,
                                 const MissileTemplateLib& missileLib);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
