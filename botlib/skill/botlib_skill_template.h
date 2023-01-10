#ifndef INCLUDED_BOTLIB_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SKILL_TEMPLATE_H

#include <memory>
#include <rapidjson/document.h>
#include <commonlib_named_map.h>
#include <botlib_skill_type.h>

namespace mcdane {
namespace botlib {

class SkillTemplate {
public:
    SkillTemplate();

    void init(SkillType type, const rapidjson::Value& v);

    inline SkillType type() const;

    inline int flags() const;

    inline int checkFlags(int f) const;

    inline float coolDown() const;

    inline float energyCost() const;

protected:
    SkillType type_;
    int flags_;
    float coolDown_;
    float energyCost_;
};

using SkillTemplateLib = commonlib::NamedMap<std::unique_ptr<SkillTemplate>>;

SkillType SkillTemplate::type() const
{
    return type_;
}

int SkillTemplate::flags() const
{
    return flags_;
}

int SkillTemplate::checkFlags(int f) const
{
    return flags_ & f;
}

float SkillTemplate::coolDown() const
{
    return coolDown_;
}

float SkillTemplate::energyCost() const
{
    return energyCost_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
