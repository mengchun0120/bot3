#ifndef INCLUDED_BOTLIB_GOODIE_TYPE_H
#define INCLUDED_BOTLIB_GOODIE_TYPE_H

#include <string>
#include <ostream>

namespace mcdane {
namespace botlib {

enum class GoodieType {
    HEALTH_FILLER,
    DAMAGE_AMPLIFIER,
    ATTACK_ACCELERATOR,
    SPEED_ACCELERATOR,
    ARMOR_ENHANCER,
    COUNT
};

inline int goodieTypeCount()
{
    return static_cast<int>(GoodieType::COUNT);
}

inline bool isValid(GoodieType type)
{
    return static_cast<int>(GoodieType::HEALTH_FILLER) <= static_cast<int>(type) &&
           static_cast<int>(GoodieType::COUNT) > static_cast<int>(type);
}

inline bool isInstantaneous(GoodieType type)
{
    return static_cast<int>(GoodieType::HEALTH_FILLER) < static_cast<int>(type) &&
           static_cast<int>(GoodieType::COUNT) > static_cast<int>(type);
}

const std::string& toString(GoodieType type);

GoodieType toGoodieType(const std::string& s);

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

std::ostream& operator<<(std::ostream& os, mcdane::botlib::GoodieType type);

} // end of namespace std

#endif

