#ifndef INCLUDE_COMMONLIB_STRING_UTILS_H
#define INCLUDE_COMMONLIB_STRING_UTILS_H

#include <sstream>
#include <commonlib_out_utils.h>

namespace mcdane {
namespace commonlib {

template <typename T>
std::string stringVal(const T &v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
