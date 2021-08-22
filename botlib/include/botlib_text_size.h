#ifndef INCLUDED_TEXT_SIZE_H
#define INCLUDED_TEXT_SIZE_H

#include <string>

namespace mcdane {
namespace botlib {

enum TextSize {
    TEXT_SIZE_BIG = 0,
    TEXT_SIZE_MEDIUM,
    TEXT_SIZE_SMALL,
    TEXT_SIZE_TINY,
    TEXT_SIZE_COUNT,
    TEXT_SIZE_INVALID
};

inline bool isValidTextSize(TextSize sz)
{
    return sz >= TEXT_SIZE_BIG && sz < TEXT_SIZE_COUNT;
}

TextSize toTextSize(const std::string &s);

} // end of namespace botlib
} // end of namespace mcdane

#endif

