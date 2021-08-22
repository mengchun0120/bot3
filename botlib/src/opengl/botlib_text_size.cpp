#include <botlib_text_size.h>

namespace mcdane {
namespace botlib {

TextSize toTextSize(const std::string &s)
{
    if (s == "big")
    {
        return TEXT_SIZE_BIG;
    }
    else if (s == "medium")
    {
        return TEXT_SIZE_MEDIUM;
    }
    else if (s == "small")
    {
        return TEXT_SIZE_SMALL;
    }
    else if (s == "tiny")
    {
        return TEXT_SIZE_TINY;
    }

    return TEXT_SIZE_INVALID;
}

} // end of namespace botlib
} // end of namespace mcdane

