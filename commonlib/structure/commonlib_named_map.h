#ifndef INCLUDED_COMMONLIB_NAMED_MAP_H
#define INCLUDED_COMMONLIB_NAMED_MAP_H

#include <unordered_map>
#include <functional>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_object.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class NamedMap {
    using Map = std::unordered_map<std::string, T>;

public:
    using NodeAccessor = std::function<bool(const T&)>;
    using NodeParser = std::function<void(T&,
                                          const std::string& name,
                                          const rapidjson::Value&)>;

    NamedMap() = default;

    virtual ~NamedMap() = default;

    void init(const std::string& fileName,
              const NodeParser& parser);

    const T* search(const std::string& name) const;

    void traverse(NodeAccessor accessor);

    inline int size() const;

private:
    Map map_;
};

template <typename T>
void NamedMap<T>::init(const std::string& fileName,
                       const NodeParser& parser)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    if (!doc.IsObject())
    {
        THROW_EXCEPT(ParseException, "Invalid json file: " + fileName);
    }

    std::string name;

    for (auto it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
    {
        std::string key(it->name.GetString());
        auto result = map_.emplace(key, T());
        if (!result.second)
        {
            THROW_EXCEPT(ParseException, "Duplicate key found: " + key);
        }

        parser(result.first->second, key, it->value);
    }
}

template <typename T>
const T* NamedMap<T>::search(const std::string& name) const
{
    auto it = map_.find(name);
    if (it == map_.end())
    {
        return nullptr;
    }

    return &(it->second);
}

template <typename T>
void NamedMap<T>::traverse(NodeAccessor accessor)
{
    for (auto it = map_.cbegin(); it != map_.cend(); ++it)
    {
        if (!accessor(it->second))
        {
            break;
        }
    }
}

template <typename T>
int NamedMap<T>::size() const
{
    return map_.size();
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

