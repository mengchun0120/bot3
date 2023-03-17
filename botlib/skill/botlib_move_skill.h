#ifndef INCLUDED_BOTLIB_MOVE_SKILL_H
#define INCLUDED_BOTLIB_MOVE_SKILL_H

#include <commonlib_vector.h>
#include <botlib_move_skill_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class MoveSkill: public Skill {
public:
    MoveSkill();

    MoveSkill(const MoveSkillTemplate *t,
              Robot *robot);

    void init(const MoveSkillTemplate *t,
              Robot *robot);

    inline const MoveSkillTemplate *getTemplate() const;

    void update(UpdateContext &cxt) override;

    void setDest(const commonlib::Vector2 &dest);

private:
    void updateWithoutDest(UpdateContext &cxt);

    void updateWithDest(UpdateContext &cxt);

    void checkPassthroughCollide(UpdateContext &cxt);

protected:
    bool destSet_;
    float timeToDest_;
    commonlib::Vector2 dest_;
};

const MoveSkillTemplate *MoveSkill::getTemplate() const
{
    return static_cast<const MoveSkillTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
