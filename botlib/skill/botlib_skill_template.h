#ifndef INCLUDED_BOTLIB_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SKILL_TEMPLATE_H

#include <memory>
#include <rapidjson/document.h>
#include <commonlib_named_map.h>
#include <botlib_typedef.h>
#include <botlib_skill_flag.h>
#include <botlib_skill_type.h>

namespace mcdane {
namespace botlib {

class ProgressPieTemplate;

class SkillTemplate {
public:
    SkillTemplate();

    void init(SkillType type,
              const rapidjson::Value& v,
              const ProgressPieTemplateLib& progressPieLib);

    inline SkillType type() const;

    inline int flags() const;

    inline int checkFlags(int f) const;

    inline bool checkFlag(SkillFlag f) const;

    inline float coolDown() const;

    inline float energyCost() const;

    inline bool keepAlive() const;

    inline const ProgressPieTemplate* pieTemplate() const;

private:
    void initPie(const std::string& pieName,
                 const ProgressPieTemplateLib& progressPieLib);

protected:
    SkillType type_;
    int flags_;
    float coolDown_;
    float energyCost_;
    bool keepAlive_;
    const ProgressPieTemplate* pieTemplate_;
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

bool SkillTemplate::checkFlag(SkillFlag f) const
{
    return flags_ & static_cast<int>(f);
}

bool SkillTemplate::keepAlive() const
{
    return keepAlive_;
}

const ProgressPieTemplate* SkillTemplate::pieTemplate() const
{
    return pieTemplate_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
