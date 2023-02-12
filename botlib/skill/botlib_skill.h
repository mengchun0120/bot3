#ifndef INCLUDED_BOTLIB_SKILL_H
#define INCLUDED_BOTLIB_SKILL_H

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

    void setEnabled(bool b);

    virtual void update(UpdateContext& cxt) = 0;

protected:
    const SkillTemplate* t_;
    Robot* robot_;
    bool enabled_;
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
    return enabled_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
