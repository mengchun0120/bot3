#ifndef INCLUDED_COMMONLIB_PARSE_H
#define INCLUDED_COMMONLIB_PARSE_H

#include <string>

namespace mcdane {
namespace commonlib {

inline void Parse(std::string &str,
                  const std::string &s)
{
    str = s;
}

inline void Parse(int &i,
                  const std::string &s)
{
    i = std::stoi(s);
}

inline void Parse(long &l,
                  const std::string &s)
{
    l = std::stol(s);
}

inline void Parse(long long &l,
                  const std::string &s)
{
    l = std::stoll(s);
}

inline void Parse(float &f,
                  const std::string &s)
{
    f = std::stof(s);
}

inline void Parse(double &d,
                  const std::string &s)
{
    d = std::stod(s);
}

inline void Parse(long double &d,
                  const std::string &s)
{
    d = std::stold(s);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

