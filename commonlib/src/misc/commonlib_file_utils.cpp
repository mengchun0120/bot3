#include <fstream>
#include <commonlib_exception.h>
#include <commonlib_file_utils.h>

namespace mcdane {
namespace commonlib {

std::string getFileSeparator()
{
#ifdef _WIN32
    return "\\";
#elif __linux__
    return "/";
#endif
}

std::string readTextFile(const std::string &fileName)
{
    std::ifstream in(fileName);

    if (!in)
    {
        THROW_EXCEPT(FileException, "Failed to open file " + fileName);
    }

    std::stringstream ss;
    ss << in.rdbuf();

    if (in.bad())
    {
        THROW_EXCEPT(FileException, "Failed to read file " + fileName);
    }

    return ss.str();
}

std::string constructPath(std::initializer_list<std::string> pathParts)
{
    if (pathParts.size() == 0) {
        return "";
    }

    std::ostringstream oss;
    std::string separator = getFileSeparator();
    auto it = pathParts.begin();

    oss << *it;
    for (++it; it != pathParts.end(); ++it) {
        oss << separator << *it;
    }

    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane

