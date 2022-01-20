#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <commonlib_json_utils.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

unsigned int Object::k_curId = 0;

Object::Object()
    : id_(k_curId++)
{}

std::string Object::toString() const
{
    using namespace rapidjson;

    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    Value v = toJson(allocator);
    v.Accept(writer);

    return buffer.GetString();
}

rapidjson::Value Object::toJson(
                        rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "Object", allocator);
    v.AddMember("id", id_, allocator);

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
    using namespace rapidjson;

    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    OStreamWrapper ows(os);
    Writer<OStreamWrapper> writer(ows);

    Value v = obj.toJson(allocator);
    v.Accept(writer);

    return os;
}

} // end of namespace std
