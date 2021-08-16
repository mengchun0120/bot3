#ifndef INCLUDED_COMMONLIB_FILE_UTILS_H
#define INCLUDED_COMMONLIB_FILE_UTILS_H

#include <initializer_list>
#include <string>
#include <sstream>

namespace mcdane {
namespace commonlib {

std::string getFileSeparator();

std::string readTextFile(const std::string &fileName);

std::string constructPath(std::initializer_list<std::string> pathParts);

template <typename P>
std::string constructPath(const std::string& dir, const P& path)
{
    std::ostringstream oss;
    std::string separator = getFileSeparator();

    oss << dir;
    for (auto it = path.cbegin(); it != path.cend(); ++it)
    {
        oss << separator << *it;
    }

    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
