#include <cstdio>
#include <rapidjson/filereadstream.h>
#include <commonlib_exception.h>
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

const rapidjson::Value* findJson(const rapidjson::Document& doc,
                                 const std::vector<std::string>& path)
{
    const rapidjson::Value* v = &doc;

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

} // end of namespace commonlib
} // end of namespace mcdane

