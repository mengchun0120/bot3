#include <string>
#include <botlib_side.h>

namespace mcdane {
namespace botlib {

Side strToSide(const std::string& s)
{
    if (s == "ai")
    {
        return Side::AI;
    }
    else if (s == "player")
    {
        return Side::PLAYER;
    }

    return Side::UNKNOWN;
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    mcdane::botlib::Side side)
{
    static string sideStr[] = {
        "AI",
        "PLAYER"
    };

    os << sideStr[static_cast<int>(side)];

    return os;
}

} // end of namespace std

