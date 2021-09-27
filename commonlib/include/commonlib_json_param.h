#ifndef INCLUDED_COMMONLIB_JSON_PARAM_H
#define INCLUDED_COMMONLIB_JSON_PARAM_H

#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_validator.h>
#include <commonlib_json_utils.h>
#include <commonlib_parse.h>

namespace mcdane {
namespace commonlib {

class JsonParam {
public:
    JsonParam(std::initializer_list<std::string> path,
              bool required=true,
              const Validator& v=Validator()) noexcept
        : path_(path)
        , required_(required)
        , validator_(v)
    {}

    virtual void parse(const rapidjson::Value& doc) = 0;

protected:
    std::vector<std::string> path_;
    bool required_;
    Validator validator_;
};

using JsonParamPtr = std::shared_ptr<JsonParam>;

template <typename T>
class TypedJsonParam: public JsonParam {
public:
    TypedJsonParam(T& var,
                   const std::initializer_list<std::string> path,
                   bool required=true,
                   Validator v=Validator()) noexcept
        : JsonParam(path, required, v)
        , var_(var)
    {}

    void parse(const rapidjson::Value& doc) override;

protected:
    T& var_;
};

template <typename T>
JsonParamPtr jsonParam(T& var,
                       const std::initializer_list<std::string> path,
                       bool required=true,
                       Validator v=Validator())
{
    return JsonParamPtr(new TypedJsonParam<T>(var, path, required, v));
}

template <typename T>
void TypedJsonParam<T>::parse(const rapidjson::Value& value)
{
    const rapidjson::Value* v = findJson(value, path_);
    if (!v)
    {
        if (required_)
        {
            THROW_EXCEPT(ParseException,
                         "Failed to find path " + toString(path_));
        }

        return;
    }

    mcdane::commonlib::parse(var_, *v);

    if (!validator_.validate())
    {
        THROW_EXCEPT(ParseException,
                     "Validation failed for " + toString(path_) +
                     ": " + validator_.description());
    }
}

void parse(std::vector<JsonParamPtr>& params,
           const rapidjson::Value& v);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
