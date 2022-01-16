#include <sstream>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

std::string Object::toString() const
{
    std::ostringstream oss;

    oss << this;

    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::commonlib::Object& obj)
{
    return os << obj.toString();
}

} // end of namespace std
