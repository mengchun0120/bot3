#ifndef INCLUDED_COMMONLIB_OBJECT_H
#define INCLUDED_COMMONLIB_OBJECT_H

#include <ostream>
#include <string>
#include <rapidjson/document.h>

namespace mcdane {
namespace commonlib {

class Object {
public:
    Object();

    virtual ~Object() = default;

    inline unsigned int id() const;

    virtual rapidjson::Value toJson(
                    rapidjson::Document::AllocatorType& allocator) const;

private:
    static unsigned int k_curId;
    unsigned int id_;
};

unsigned int Object::id() const
{
    return id_;
}

rapidjson::Value jsonVal(const Object& obj,
                         rapidjson::Document::AllocatorType& allocator);

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::commonlib::Object& obj);

} // end of namespace std

#endif

