#ifndef INCLUDED_BOTLIB_CONSTANTS_H
#define INCLUDED_BOTLIB_CONSTANTS_H

namespace mcdane {
namespace botlib {

struct Constants {
    static constexpr unsigned int FLOATS_PER_POS = 2;
    static constexpr unsigned int FLOATS_PER_TEXPOS = 2;
    static constexpr unsigned int POS_SIZE = FLOATS_PER_POS * sizeof(float);
    static constexpr unsigned int TEXPOS_SIZE = FLOATS_PER_TEXPOS * sizeof(float);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

