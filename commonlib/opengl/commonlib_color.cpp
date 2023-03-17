#include <commonlib_color.h>

namespace mcdane {
namespace commonlib {

Color::Color(unsigned int red,
             unsigned int green,
             unsigned int blue,
             unsigned int alpha)
{
    init(red, green, blue, alpha);
}

Color::Color(std::initializer_list<unsigned int> c)
{
    init(c);
}

Color::Color(const std::vector<unsigned int> &c)
{
    init(c);
}

void Color::init(unsigned int red,
                 unsigned int green,
                 unsigned int blue,
                 unsigned int alpha)
{
    init({red, green, blue, alpha});
}

void Color::init(std::initializer_list<unsigned int> c)
{
    init(c.begin(), c.end());
}

void Color::init(const std::vector<unsigned int> &c)
{
    init(c.begin(), c.end());
}

} // end of namespace commonlib
} // end of namespace mcdane

