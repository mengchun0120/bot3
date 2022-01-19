#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <commonlib_json_utils.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

std::string Object::toString() const
{
    return "";
}

rapidjson::Value Object::toJson(
                        rapidjson::Document::AllocatorType& allocator) const
{
    rapidjson::Value v;

    v.AddMember("class", "Object", allocator);
    v.AddMember("ptr", jsonVal(this, allocator), allocator);

    return v;
}

rapidjson::Value jsonVal(const Object& obj,
                         rapidjson::Document::AllocatorType& allocator)
{
    return obj.toJson(allocator);
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
