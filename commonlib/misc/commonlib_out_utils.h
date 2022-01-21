#ifndef INCLUDED_COMMONLIB_OUT_UTILS_H
#define INCLUDED_COMMONLIB_OUT_UTILS_H

#include <ostream>
#include <vector>
#include <array>
#include <initializer_list>
#include <rapidjson/document.h>

namespace std {

template <typename T>
std::ostream& operator<<(std::ostream& os,
                         const std::vector<T>& v)
{
    os << '[';
    if (v.size() > 0)
    {
        os << v[0];
        for (std::size_t i = 1; i < v.size(); ++i)
        {
            os << ", " << v[i];
        }
    }
    os << ']';
    return os;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os,
                         const std::array<T,N>& v)
{
    os << '[';
    if (N > 0)
    {
        os << v[0];
        for (std::size_t i = 1; i < N; ++i)
        {
            os << ", " << v[i];
        }
    }
    os << ']';
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os,
                         const std::initializer_list<T>& v)
{
    os << '[';
    auto it = v.begin();
    if (it != v.end())
    {
        os << *it;
        for (++it; it != v.end(); ++it)
        {
            os << ", " << *it;
        }
    }
    os << ']';
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const rapidjson::Value& v);

} // end of namespace std

#endif

