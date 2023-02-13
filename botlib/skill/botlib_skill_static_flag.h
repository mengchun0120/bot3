#ifndef INCLUDED_BOTLIB_SKILL_STATIC_FLAG_H
#define INCLUDED_BOTLIB_SKILL_STATIC_FLAG_H

namespace mcdane {
namespace botlib {

enum class SkillStaticFlag: int {
    OFFENSIVE = 0x00000001,
    KEEPALIVE = 0x00000002,
};

inline int operator|(SkillStaticFlag f1, SkillStaticFlag f2)
{
    return static_cast<int>(f1) | static_cast<int>(f2);
}

inline int operator|(int f1, SkillStaticFlag f2)
{
    return f1 | static_cast<int>(f2);
}

inline int operator|(SkillStaticFlag f1, int f2)
{
    return static_cast<int>(f1) | f2;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
