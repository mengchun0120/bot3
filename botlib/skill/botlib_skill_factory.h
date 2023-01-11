#ifndef INCLUDED_BOTLIB_SKILL_FACTORY_H
#define INCLUDED_BOTLIB_SKILL_FACTORY_H

namespace mcdane {
namespace botlib {

class Skill;
class SkillTemplate;
class Robot;

class SkillFactory {
public:
    static Skill* create(const SkillTemplate* t, Robot* robot);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
