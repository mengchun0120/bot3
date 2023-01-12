#ifndef INCLUDED_BOTLIB_SKILL_H
#define INCLUDED_BOTLIB_SKILL_H

namespace mcdane {
namespace botlib {

class SkillTemplate;
class Robot;
class UpdateContext;

class Skill {
public:
    Skill();

    Skill(const SkillTemplate* t,
          Robot* robot,
          bool enabled1);

    virtual ~Skill() = default;

    void init(const SkillTemplate* t,
              Robot* robot,
              bool enabled1);

    inline const SkillTemplate* getTemplate() const;

    inline bool enaled() const;

    void setEnabled(bool enabled1);

    virtual bool available() const = 0;

    virtual void apply(UpdateContext& cxt) = 0;

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

bool Skill::enaled() const
{
    return enabled_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
