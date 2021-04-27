#ifndef INCLUDED_COMMONLIB_PARSE_H
#define INCLUDED_COMMONLIB_PARSE_H

#include <string>

namespace mcdane {
namespace commonlib {

inline void parse(std::string &str,
                  const std::string &s)
{
    str = s;
}

inline void parse(int &i,
                  const std::string &s)
{
    i = std::stoi(s);
}

inline void parse(long &l,
                  const std::string &s)
{
    l = std::stol(s);
}

inline void parse(long long &l,
                  const std::string &s)
{
    l = std::stoll(s);
}

inline void parse(float &f,
                  const std::string &s)
{
    f = std::stof(s);
}

inline void parse(double &d,
                  const std::string &s)
{
    d = std::stod(s);
}

inline void parse(long double &d,
                  const std::string &s)
{
    d = std::stold(s);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

