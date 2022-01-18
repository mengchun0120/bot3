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

rapidjson::Value Object::toJson() const
{
    using namespace rapidjson;

    Document doc(kObjectType);
    Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("class", "Object", allocator);
    doc.AddMember("ptr", mcdane::commonlib::toJson(this, allocator), allocator);

    return doc;
}

rapidjson::Value toJson(const Object& obj,
                        rapidjson::Document::AllocatorType& allocator)
{
    return obj.toJson();
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
