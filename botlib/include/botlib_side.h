#ifndef INCLUDED_BOTLIB_SIDE_H
#define INCLUDED_BOTLIB_SIDE_H

#include <ostream>

namespace mcdane {
namespace botlib {

enum class Side {
    AI,
    PLAYER
};

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    mcdane::botlib::Side side);

} // end of namespace std

#endif

