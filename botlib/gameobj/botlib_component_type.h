#ifndef INCLUDED_BOTLIB_COMPONENT_TYPE_H
#define INCLUDED_BOTLIB_COMPONENT_TYPE_H

#include <string>

namespace mcdane {
namespace botlib {

enum class ComponentType {
    TILE,
    BASE,
    GUN,
    MISSILE,
    GOODIE
};

constexpr int COMPONENT_TYPE_COUNT = 5;

const std::string& toString(ComponentType type);

ComponentType toComponentType(const std::string& typeStr);

} // end of namespace botlib
} // end of namespace mcdane

#endif
