#ifndef INCLUDED_COMMONLIB_FILE_UTILS_H
#define INCLUDED_COMMONLIB_FILE_UTILS_H

#include <initializer_list>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <commonlib_exception.h>
#include <commonlib_log.h>

namespace mcdane {
namespace commonlib {

std::string getFileSeparator();

std::string readText(const std::string &path);

std::string constructPath(std::initializer_list<std::string> pathParts);

std::string constructPath(const std::string &dir,
                          const std::vector<std::string> &path);

std::string constructPath(const std::vector<std::string> &path);

template <typename T>
void readList(std::vector<T> &v, std::istream &s)
{
    std::list<T> tmp;

    T t;
    while (s >> t)
    {
        tmp.push_back(t);
    }

    v.resize(tmp.size());
    std::copy(tmp.begin(), tmp.end(), v.begin());
}

template <typename T>
void readList(std::vector<T> &v, const std::string &path)
{
    std::string str = readText(path);
    std::istringstream in(str);
    readList(v, in);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
