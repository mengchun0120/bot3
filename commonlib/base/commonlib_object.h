#ifndef INCLUDED_COMMONLIB_OBJECT_H
#define INCLUDED_COMMONLIB_OBJECT_H

#include <ostream>
#include <string>

namespace mcdane {
namespace commonlib {

class Object {
public:
    Object() = default;

    virtual ~Object() = default;

    virtual std::string toString() const;
};

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::commonlib::Object& obj);

} // end of namespace std

#endif

