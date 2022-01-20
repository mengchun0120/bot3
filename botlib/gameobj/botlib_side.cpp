#include <string>
#include <commonlib_exception.h>
#include <botlib_side.h>

using namespace mcdane::commonlib;

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

    THROW_EXCEPT(InvalidArgumentException, "Invalid side " + s);
}

std::string stringVal(Side s)
{
    switch (s)
    {
        case Side::AI:
            return "AI";
        case Side::PLAYER:
            return "PLAYER";
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid side");
    }
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

