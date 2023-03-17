#include <commonlib_parse.h>

namespace mcdane {
namespace commonlib {

void parse(bool &b,
           const rapidjson::Value &v)
{
    if (!v.IsBool())
    {
        THROW_EXCEPT(ParseException, " object is not a bool");
    }

    b = v.GetBool();
}

void parse(int &i,
           const rapidjson::Value &v)
{
    if (!v.IsInt())
    {
        THROW_EXCEPT(ParseException, " object is not an int");
    }

    i = v.GetInt();
}

void parse(unsigned int &u,
           const rapidjson::Value &v)
{
    if (!v.IsUint())
    {
        THROW_EXCEPT(ParseException, " object is not an unsigned int");
    }

    u = v.GetUint();
}

void parse(int64_t &i,
           const rapidjson::Value &v)
{
    if (!v.IsInt64())
    {
        THROW_EXCEPT(ParseException, " object is not an int64_t");
    }

    i = v.GetInt64();
}

void parse(uint64_t &u,
           const rapidjson::Value &v)
{
    if (!v.IsUint64())
    {
        THROW_EXCEPT(ParseException, " object is not a uint64_t");
    }

    u = v.GetUint64();
}

void parse(float &f,
           const rapidjson::Value &v)
{
    double d;
    parse(d, v);
    f = static_cast<float>(d);
}

void parse(double &d,
           const rapidjson::Value &v)
{
    if (!v.IsDouble())
    {
        THROW_EXCEPT(ParseException, " object is not a double");
    }

    d = v.GetDouble();
}

void parse(std::string &s,
           const rapidjson::Value &v)
{
    if (!v.IsString())
    {
        THROW_EXCEPT(ParseException, " object is not a string");
    }

    s = v.GetString();
}

void parse(Color &c,
           const rapidjson::Value &v)
{
    std::vector<unsigned int> parts;
    parse(parts, v);
    c.init(parts);
}

} // end of namespace commonlib
} // end of namespace mcdane

