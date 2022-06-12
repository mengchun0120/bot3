#include <commonlib_exception.h>
#include <botlib_goodie_type.h>

namespace mcdane {
namespace botlib {

const std::string& toString(GoodieType type)
{
    using namespace mcdane::commonlib;

    static std::string goodieTypeStr[] = {
        "gold",
        "health",
        "indestructable",
        "double_experience",
        "quick_shooter",
        "quick_mover",
        "double_damage"
    };

    if (!isValidGoodieType(type))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid GoodieType");
    }

    return goodieTypeStr[static_cast<int>(type)];
}

} // end of namespace botlib
} // end of namespace mcdane


namespace std {

std::ostream& operator<<(std::ostream& os, mcdane::botlib::GoodieType type)
{
    return os << mcdane::botlib::toString(type);
}

} // end of namespace std

