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
    GOD_MODE,
    COUNT
};

inline unsigned int goodieTypeCount()
{
    return static_cast<unsigned int>(GoodieType::COUNT);
}

inline GoodieType firstLastingGoodieType()
{
    return GoodieType::DAMAGE_AMPLIFIER;
}

inline unsigned int lastingGoodieTypeCount()
{
    return static_cast<unsigned int>(GoodieType::COUNT) -
           static_cast<unsigned int>(GoodieType::DAMAGE_AMPLIFIER);
}

inline int lastingGoodieTypeIndex(GoodieType t)
{
    return static_cast<int>(t) - static_cast<int>(firstLastingGoodieType());
}

inline bool isValid(GoodieType type)
{
    return static_cast<int>(GoodieType::HEALTH_FILLER) <= static_cast<int>(type) &&
           static_cast<int>(GoodieType::COUNT) > static_cast<int>(type);
}

inline bool isLasting(GoodieType type)
{
    return static_cast<int>(GoodieType::HEALTH_FILLER) < static_cast<int>(type) &&
           static_cast<int>(GoodieType::COUNT) > static_cast<int>(type);
}

const std::string &toString(GoodieType type);

GoodieType toGoodieType(const std::string &s);

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

std::ostream &operator<<(std::ostream& os, mcdane::botlib::GoodieType type);

} // end of namespace std

#endif

