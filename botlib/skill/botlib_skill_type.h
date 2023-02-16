#ifndef INCLUDED_BOTLIB_SKILL_TYPE_H
#define INCLUDED_BOTLIB_SKILL_TYPE_H

#include <vector>
#include <string>

namespace mcdane {
namespace botlib {

enum class SkillType {
    MOVE,
    SHOOT_MISSILE,
    BLAST,
    TARGETED_BLAST,
    BARRAGE,
};

const std::string& toString(SkillType type);

SkillType toSkillType(const std::string& typeStr);

inline bool isSkillWithCost(SkillType type)
{
    return static_cast<int>(type) >= static_cast<int>(SkillType::SHOOT_MISSILE);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
