#ifndef INCLUDED_BOTLIB_GAME_UTILS_H
#define INCLUDED_BOTLIB_GAME_UTILS_H

#include <vector>

namespace mcdane {
namespace commonlib {

template <typename T>
class Region;

} // end of namespace commonlib

namespace botlib {

int diff(std::vector<commonlib::Region<int>>& result,
         const commonlib::Region<int>& r1,
         const commonlib::Region<int>& r2);

} // end of namespace botlib
} // end of namespace mcdane

#endif
