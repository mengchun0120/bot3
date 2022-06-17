#ifndef INCLUDED_BOTLIB_GOODIE_TYPE_H
#define INCLUDED_BOTLIB_GOODIE_TYPE_H

#include <string>
#include <ostream>

namespace mcdane {
namespace botlib {

enum class GoodieType {
    HEALTH,
    INDESTRUCTABLE,
    QUICK_SHOOTER,
    QUICK_MOVER,
    DOUBLE_DAMAGE,
    COUNT
};

inline int goodieTypeCount()
{
    return static_cast<int>(GoodieType::COUNT);
}

inline bool isValidGoodieType(GoodieType type)
{
    return static_cast<int>(GoodieType::HEALTH) <= static_cast<int>(type) &&
           static_cast<int>(GoodieType::COUNT) > static_cast<int>(type);
}

const std::string& toString(GoodieType type);

GoodieType strToGoodieType(const std::string& s);

} // end of namespace botlib
} // end of namespace mcdane



namespace std {

std::ostream& operator<<(std::ostream& os, mcdane::botlib::GoodieType type);

} // end of namespace std

#endif

