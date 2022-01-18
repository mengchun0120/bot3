#ifndef INCLUDED_COMMONLIB_JSON_UTILS_H
#define INCLUDED_COMMONLIB_JSON_UTILS_H

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <rapidjson/document.h>

namespace mcdane {
namespace commonlib {

void readJson(rapidjson::Document& doc,
              const std::string& fileName);

const rapidjson::Value* findJson(const rapidjson::Value& json,
                                 const std::vector<std::string>& path);

rapidjson::Value toJson(const void* ptr,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(const std::string& s,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(int i,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(unsigned int i,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(long i,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(unsigned long i,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(int64_t i,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(uint64_t i,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(double d,
                        rapidjson::Document::AllocatorType& allocator);

rapidjson::Value toJson(float f,
                        rapidjson::Document::AllocatorType& allocator);

template <typename T>
rapidjson::Value toJson(const std::vector<T>& vec,
                        rapidjson::Document::AllocatorType& allocator)
{
    using namespace rapidjson;

    Value v(kArrayType);

    for (const T& t: vec)
    {
        v.PushBack(toJson(t, allocator), allocator);
    }

    return v;
}

template <typename T, unsigned int N>
rapidjson::Value toJson(const std::array<T,N>& arr,
                        rapidjson::Document::AllocatorType& allocator)
{
    using namespace rapidjson;

    Value v(kArrayType);

    for (const T& t: arr)
    {
        v.PushBack(toJson(t, allocator), allocator);
    }

    return v;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
