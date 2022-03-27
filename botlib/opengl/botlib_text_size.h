#ifndef INCLUDED_TEXT_SIZE_H
#define INCLUDED_TEXT_SIZE_H

#include <string>

namespace mcdane {
namespace botlib {

enum class TextSize {
    BIG = 0,
    MEDIUM,
    SMALL,
    TINY,
    COUNT,
    INVALID = COUNT,
};

constexpr int firstTextSize()
{
    return static_cast<int>(TextSize::BIG);
}

constexpr int textSizeCount()
{
    return static_cast<int>(TextSize::COUNT);
}

inline bool isValidTextSize(TextSize sz)
{
    int intSize = static_cast<int>(sz);
    return intSize >= firstTextSize()  && intSize < textSizeCount();
}

TextSize toTextSize(const std::string &s);

bool isValidTextSizeStr(const std::string& s);

} // end of namespace botlib
} // end of namespace mcdane

#endif

