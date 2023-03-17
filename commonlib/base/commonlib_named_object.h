#ifndef INCLUDED_COMMONLIB_NAMED_OBJECT_H
#define INCLUDED_COMMONLIB_NAMED_OBJECT_H

#include <string>
#include <rapidjson/document.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

class NamedObject: public Object {
public:
    NamedObject() = default;

    void init(const rapidjson::Value &v,
              bool requireName = false);

    inline const std::string &name() const;

    void setName(const std::string &name1);

protected:
    std::string name_;
};

const std::string &NamedObject::name() const
{
    return name_;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

