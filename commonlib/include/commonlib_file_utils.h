#ifndef INCLUDED_COMMONLIB_FILE_UTILS_H
#define INCLUDED_COMMONLIB_FILE_UTILS_H

#include <initializer_list>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <commonlib_exception.h>

namespace mcdane {
namespace commonlib {

std::string getFileSeparator();

std::string readTextFile(const std::string &fileName);

std::string constructPath(std::initializer_list<std::string> pathParts);

std::string constructPath(const std::string& dir,
                          const std::vector<std::string>& path);

template <typename T>
void readList(std::vector<T>& v,
              const std::string& fileName)
{
    std::ifstream in(fileName);
    std::list<T> tmp;

    while (in.good())
    {
        T t;
        in >> t;
        tmp.push_back(t);
    }

    if (!in.eof())
    {
        THROW_EXCEPT(FileException, "Failed to read file " + fileName);
    }

    v.resize(tmp.size());
    std::copy(tmp.begin(), tmp.end(), v.begin());
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
