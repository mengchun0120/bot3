#include <botlib_text_size.h>

namespace mcdane {
namespace botlib {

TextSize toTextSize(const std::string &s)
{
    if (s == "big")
    {
        return TextSize::BIG;
    }
    else if (s == "medium")
    {
        return TextSize::MEDIUM;
    }
    else if (s == "small")
    {
        return TextSize::SMALL;
    }
    else if (s == "tiny")
    {
        return TextSize::TINY;
    }

    return TextSize::INVALID;
}

} // end of namespace botlib
} // end of namespace mcdane

