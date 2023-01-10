#ifndef INCLUDED_BOTLIB_SKILL_FLAG_H
#define INCLUDED_BOTLIB_SKILL_FLAG_H

namespace mcdane {
namespace botlib {

enum class SkillFlag: int {
    OFFENSIVE = 0x00000001,
};

inline int operator|(SkillFlag f1, SkillFlag f2)
{
    return static_cast<int>(f1) | static_cast<int>(f2);
}

inline int operator|(int f1, SkillFlag f2)
{
    return f1 | static_cast<int>(f2);
}

inline int operator|(SkillFlag f1, int f2)
{
    return static_cast<int>(f1) | f2;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
