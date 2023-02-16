#ifndef INCLUDED_BOTLIB_STATIC_SKILL_FLAG_H
#define INCLUDED_BOTLIB_STATIC_SKILL_FLAG_H

namespace mcdane {
namespace botlib {

enum class StaticSkillFlag: int {
    OFFENSIVE = 0x00000001,
    KEEPALIVE = 0x00000002,
};

inline int operator|(StaticSkillFlag f1, StaticSkillFlag f2)
{
    return static_cast<int>(f1) | static_cast<int>(f2);
}

inline int operator|(int f1, StaticSkillFlag f2)
{
    return f1 | static_cast<int>(f2);
}

inline int operator|(StaticSkillFlag f1, int f2)
{
    return static_cast<int>(f1) | f2;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
