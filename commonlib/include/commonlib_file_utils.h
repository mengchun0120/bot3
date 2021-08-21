#ifndef INCLUDED_COMMONLIB_FILE_UTILS_H
#define INCLUDED_COMMONLIB_FILE_UTILS_H

#include <initializer_list>
#include <string>
#include <vector>
#include <sstream>

namespace mcdane {
namespace commonlib {

std::string getFileSeparator();

std::string readTextFile(const std::string &fileName);

std::string constructPath(std::initializer_list<std::string> pathParts);

std::string constructPath(const std::string& dir,
                          const std::vector<std::string>& path);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
