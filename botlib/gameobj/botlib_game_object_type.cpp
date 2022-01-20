#include <botlib_game_object_type.h>

namespace mcdane {
namespace botlib {

std::string stringVal(GameObjectType t)
{
    static std::string typeStr[] = {
        "tile",
        "robot",
        "missile",
        "effect"
    };

    return typeStr[static_cast<int>(t)];
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os, mcdane::botlib::GameObjectType t)
{
    static std::string typeStr[] = {
        "tile",
        "robot",
        "missile",
        "effect"
    };

    return os << typeStr[static_cast<int>(t)];
}

} // end of namespace std

