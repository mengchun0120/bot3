#ifndef INCLUDED_BOTLIB_SKILL_H
#define INCLUDED_BOTLIB_SKILL_H

#include <botlib_dynamic_skill_flag.h>
#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class Robot;
class UpdateContext;
class ProgressPie;

class Skill {
public:
    Skill();

    Skill(const SkillTemplate* t,
          Robot* robot,
          bool enabled1=false);

    virtual ~Skill();

    void init(const SkillTemplate* t,
              Robot* robot,
              bool enabled1=false);

    inline const SkillTemplate* getTemplate() const;

    inline SkillType type() const;

    inline bool enabled() const;

    inline bool inProcess() const;

    inline bool checkFlag(DynamicSkillFlag f) const;

    inline bool checkFlags(int f) const;

    inline void setEnabled(bool b);

    inline void setInProcess(bool b);

    inline void setFlag(DynamicSkillFlag f, bool b);

    virtual void update(UpdateContext& cxt) = 0;

protected:
    const SkillTemplate* t_;
    int flags_;
    Robot* robot_;
};

const SkillTemplate* Skill::getTemplate() const
{
    return t_;
}

SkillType Skill::type() const
{
    return t_->type();
}

bool Skill::enabled() const
{
    return checkFlag(DynamicSkillFlag::ENABLED);
}

bool Skill::inProcess() const
{
    return checkFlag(DynamicSkillFlag::INPROCESS);
}

bool Skill::checkFlag(DynamicSkillFlag f) const
{
    return flags_ & static_cast<int>(f);
}

bool Skill::checkFlags(int f) const
{
    return flags_ & f;
}

void Skill::setEnabled(bool b)
{
    setFlag(DynamicSkillFlag::ENABLED, b);
}

void Skill::setInProcess(bool b)
{
    setFlag(DynamicSkillFlag::INPROCESS, b);
}

void Skill::setFlag(DynamicSkillFlag f, bool b)
{
    if (b)
    {
        flags_ |= static_cast<int>(f);
    }
    else
    {
        flags_ &= ~static_cast<int>(f);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
