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
};

const std::string& toString(SkillType type);

SkillType toSkillType(const std::string& typeStr);

} // end of namespace botlib
} // end of namespace mcdane

#endif
