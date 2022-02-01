#ifndef INCLUDED_COMMONLIB_NAMED_MAP_H
#define INCLUDED_COMMONLIB_NAMED_MAP_H

#include <unordered_map>
#include <functional>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class NamedMap: public Object {
    using Map = std::unordered_map<std::string, T>;

public:
    using NodeAccessor = std::function<bool(const T*)>;

    NamedMap() = default;

    virtual ~NamedMap() = default;

    template <typename PARSER>
    void
    load(
        const std::string& fileName,
        PARSER& parser);

    const T*
    search(
        const std::string& name) const;

    void
    traverse(
        NodeAccessor accessor);

    rapidjson::Value
    toJson(
        rapidjson::Document::AllocatorType& allocator) const override;

private:
    void
    add(
        const std::string& name,
        T* t);

private:
    Map map_;
};

template <typename T>
template <typename PARSER>
void
NamedMap<T>::load(
    const std::string& fileName,
    PARSER& parser)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    if (!doc.IsArray())
    {
        THROW_EXCEPT(
            ParseException,
            "Invalid json file: " + fileName);
    }

    std::string name;

    std::vector<JsonParamPtr> params{
        jsonParam(
            name,
            {"name"},
            true,
            k_nonEmptyStrV)
    };

    const rapidjson::Value& arr = doc.GetArray();
    int numObjects = arr.Capacity();

    for (int i = 0; i < numObjects; ++i)
    {
        parse(params, arr[i]);
        T* t = parser(arr[i]);
        add(name, t);
    }
}

template <typename T>
void
NamedMap<T>::add(
    const std::string& name,
    T* t)
{
    auto it = map_.find(name);
    if (it != map_.end())
    {
        THROW_EXCEPT(
            ParseException,
            "Duplicate name " + name);
    }

    map_[name] = *t;
}

template <typename T>
const T*
NamedMap<T>::search(
    const std::string& name) const
{
    auto it = map_.find(name);
    if (it == map_.end())
    {
        return nullptr;
    }

    return &(it->second);
}

template <typename T>
void
NamedMap<T>::traverse(
    NodeAccessor accessor)
{
    for (auto it = map_.cbegin(); it != map_.cend(); ++it)
    {
        if (!accessor(&(it->second)))
        {
            break;
        }
    }
}

template <typename T>
rapidjson::Value
NamedMap<T>::toJson(
    rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember(
        "class",
        "NamedMap",
        allocator);

    Value objs(kArrayType);

    for (auto it = map_.begin(); it != map_.end(); ++it)
    {
        Value item(kObjectType);

        item.AddMember(
            "name",
            jsonVal(it->first, allocator),
            allocator);

        item.AddMember(
            "value",
            jsonVal(it->second, allocator),
            allocator);

        objs.PushBack(item, allocator);
    }

    v.AddMember(
        "objects",
        objs,
        allocator);

    return v;
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

