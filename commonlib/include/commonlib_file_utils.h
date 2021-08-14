#ifndef INCLUDED_COMMONLIB_FILE_UTILS_H
#define INCLUDED_COMMONLIB_FILE_UTILS_H

#include <initializer_list>
#include <string>

namespace mcdane {
namespace commonlib {

std::string readTextFile(const std::string &fileName);

std::string constructPath(std::initializer_list<std::string> pathParts);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
