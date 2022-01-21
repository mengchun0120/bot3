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

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    mcdane::botlib::Side side)
{
    using namespace mcdane::botlib;
    using namespace mcdane::commonlib;

    switch (side)
    {
        case Side::AI:
            return os << "AI";
        case Side::PLAYER:
            return os << "PLAYER";
        default:
            THROW_EXCEPT(InvalidArgumentException,
                         "Invalid side" +
                         std::to_string(static_cast<int>(side)));
    }
}

} // end of namespace std

