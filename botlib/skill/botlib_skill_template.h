#ifndef INCLUDED_BOTLIB_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SKILL_TEMPLATE_H

#include <rapidjson/document.h>
#include <botlib_static_skill_flag.h>
#include <botlib_skill_type.h>

namespace mcdane {
namespace botlib {

class ProgressPieTemplate;

class SkillTemplate {
public:
    SkillTemplate();

    void init(SkillType type,
              const rapidjson::Value &v);

    inline SkillType type() const;

    inline int flags() const;

    inline bool isOffensive() const;

    inline bool keepAlive() const;

    inline int checkFlags(int f) const;

    inline bool checkFlag(StaticSkillFlag f) const;

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

bool SkillTemplate::isOffensive() const
{
    return checkFlag(StaticSkillFlag::OFFENSIVE);
}

bool SkillTemplate::keepAlive() const
{
    return checkFlag(StaticSkillFlag::KEEPALIVE);
}

int SkillTemplate::checkFlags(int f) const
{
    return flags_ & f;
}

bool SkillTemplate::checkFlag(StaticSkillFlag f) const
{
    return flags_ & static_cast<int>(f);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
