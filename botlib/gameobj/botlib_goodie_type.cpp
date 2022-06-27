#include <commonlib_exception.h>
#include <botlib_goodie_type.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

static std::string k_goodieTypeStr[] = {
    "health filler",
    "damage amplifier",
    "attack accelerator",
    "speed accelerator",
    "armor enhancer"
};

const std::string& toString(GoodieType type)
{
    if (!isValid(type))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid GoodieType");
    }

    return k_goodieTypeStr[static_cast<int>(type)];
}

GoodieType toGoodieType(const std::string& s)
{
    for (int i = 0; i < goodieTypeCount(); ++i)
    {
        if (k_goodieTypeStr[i] == s)
        {
            return static_cast<GoodieType>(i);
        }
    }

    THROW_EXCEPT(InvalidArgumentException, "Invalid GoodieType string " + s);
}

} // end of namespace botlib
} // end of namespace mcdane


namespace std {

std::ostream& operator<<(std::ostream& os, mcdane::botlib::GoodieType type)
{
    return os << mcdane::botlib::toString(type);
}

} // end of namespace std

