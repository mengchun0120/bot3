#ifndef INCLUDED_BOTLIB_ALIGN_H
#define INCLUDED_BOTLIB_ALIGN_H

namespace mcdane {
namespace botlib {

enum class HAlign {
    LEFT,
    MIDDLE,
    RIGHT
};

enum class VAlign {
    TOP,
    MIDDLE,
    BOTTOM
};

inline bool isValidHAlign(HAlign align)
{
    return static_cast<int>(align) >= static_cast<int>(HAlign::LEFT) &&
           static_cast<int>(align) <= static_cast<int>(HAlign::RIGHT);
}

inline bool isValidVAlign(VAlign align)
{
    return static_cast<int>(align) >= static_cast<int>(VAlign::TOP) &&
           static_cast<int>(align) <= static_cast<int>(VAlign::BOTTOM);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

