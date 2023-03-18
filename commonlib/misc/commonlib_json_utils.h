#ifndef INCLUDED_COMMONLIB_JSON_UTILS_H
#define INCLUDED_COMMONLIB_JSON_UTILS_H

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <ostream>
#include <rapidjson/document.h>

namespace mcdane {
namespace commonlib {

void readJson(rapidjson::Document &doc,
              const std::string &path);

const rapidjson::Value *findJson(const rapidjson::Value &json,
                                 const std::vector<std::string> &path);

rapidjson::Value jsonVal(const void *ptr,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(const char *str,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(const std::string &s,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(int i,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(unsigned int i,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(long i,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(unsigned long i,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(double d,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(float f,
                         rapidjson::Document::AllocatorType &allocator);

rapidjson::Value jsonVal(bool b,
                         rapidjson::Document::AllocatorType &allocator);

template <typename T>
rapidjson::Value jsonVal(const std::vector<T> &vec,
                         rapidjson::Document::AllocatorType &allocator)
{
    using namespace rapidjson;

    Value v(kArrayType);

    for (const T &t: vec)
    {
        v.PushBack(jsonVal(t, allocator), allocator);
    }

    return v;
}

template <typename T, std::size_t N>
rapidjson::Value jsonVal(const std::array<T,N> &arr,
                         rapidjson::Document::AllocatorType &allocator)
{
    using namespace rapidjson;

    Value v(kArrayType);

    for (const T &t: arr)
    {
        v.PushBack(jsonVal(t, allocator), allocator);
    }

    return v;
}

template <typename T>
rapidjson::Value jsonVal(const T *const arr,
                         int size,
                         rapidjson::Document::AllocatorType &allocator)
{
    using namespace rapidjson;

    Value v(kArrayType);

    for (int i = 0; i < size; ++i)
    {
        v.PushBack(jsonVal(arr[i], allocator), allocator);
    }

    return v;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif
