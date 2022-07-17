#ifndef INCLUDED_COMMONLIB_OBJECT_H
#define INCLUDED_COMMONLIB_OBJECT_H

#include <ostream>
#include <string>
#include <rapidjson/document.h>

namespace mcdane {
namespace commonlib {

class Object {
public:
    Object() = default;

    virtual ~Object() = default;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

