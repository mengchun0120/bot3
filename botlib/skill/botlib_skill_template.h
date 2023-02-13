#ifndef INCLUDED_BOTLIB_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SKILL_TEMPLATE_H

#include <rapidjson/document.h>
#include <botlib_skill_static_flag.h>
#include <botlib_skill_type.h>

namespace mcdane {
namespace botlib {

class ProgressPieTemplate;

class SkillTemplate {
public:
    SkillTemplate();

    void init(SkillType type,
              const rapidjson::Value& v);

    inline SkillType type() const;

    inline int flags() const;

    inline int checkFlags(int f) const;

    inline bool checkFlag(SkillStaticFlag f) const;

protected:
    SkillType type_;
    int flags_;
};

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

bool SkillTemplate::checkFlag(SkillStaticFlag f) const
{
    return flags_ & static_cast<int>(f);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
