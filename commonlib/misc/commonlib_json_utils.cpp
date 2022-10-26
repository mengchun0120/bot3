#include <cstdio>
#include <rapidjson/filereadstream.h>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>

namespace mcdane {
namespace commonlib {

void readJson(rapidjson::Document& doc,
              const std::string& fileName)
{
    FILE *fp = fopen(fileName.c_str(), "rb");
    if (!fp)
    {
        THROW_EXCEPT(FileException, "Failed to open " + fileName);
    }

    char readBuffer[1000];

    rapidjson::FileReadStream stream(fp, readBuffer, sizeof(readBuffer));
    doc.ParseStream(stream);

    fclose(fp);

    if (doc.HasParseError())
    {
        THROW_EXCEPT(ParseException, "Failed to parse " + fileName);
    }
}

const rapidjson::Value* findJson(const rapidjson::Value& json,
                                 const std::vector<std::string>& path)
{
    const rapidjson::Value* v = &json;

    for (std::size_t i = 0; i < path.size(); ++i)
    {
        if (i < path.size() - 1 && !v->IsObject())
        {
            return nullptr;
        }

        const char* name = path[i].c_str();

        if (!v->HasMember(name))
        {
            return nullptr;
        }

        v = &(*v)[name];
    }

    return v;
}

rapidjson::Value jsonVal(const void* ptr,
                        rapidjson::Document::AllocatorType& allocator)
{
    return jsonVal(stringVal(ptr), allocator);
}

rapidjson::Value jsonVal(const char* str,
                         rapidjson::Document::AllocatorType& allocator)
{
    return jsonVal(std::string(str), allocator);
}

rapidjson::Value jsonVal(const std::string& s,
                        rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetString(s.c_str(), s.size(), allocator);

    return v;
}

rapidjson::Value jsonVal(int i,
                        rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetInt(i);

    return v;
}

rapidjson::Value jsonVal(unsigned int i,
                        rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetUint(i);

    return v;
}

rapidjson::Value jsonVal(long i,
                         rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetInt(i);

    return v;
}

rapidjson::Value jsonVal(unsigned long i,
                         rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetUint(i);

    return v;
}

rapidjson::Value jsonVal(double d,
                         rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetDouble(d);

    return v;
}

rapidjson::Value jsonVal(float f,
                         rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetFloat(f);

    return v;
}

rapidjson::Value jsonVal(bool b,
                         rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value v;

    v.SetBool(b);

    return v;
}

} // end of namespace commonlib
} // end of namespace mcdane

