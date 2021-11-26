#ifndef INCLUDED_COMMONLIB_NAMED_MAP_H
#define INCLUDED_COMMONLIB_NAMED_MAP_H

#include <list>
#include <vector>
#include <iostream>
#include <functional>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class NamedMap {
public:
    using NodeAccessor = std::function<bool(const T*)>;

    NamedMap();

    virtual ~NamedMap();

    template <typename PARSER>
    void load(const std::string& fileName,
              PARSER& parser);

    bool add(const std::string& name,
             T* t);

    T* search(const std::string& name) const;

    inline int getNumObjs() const;

    inline T* getObjAt(int idx);

    inline const T* getObjAt(int idx) const;

    inline const std::string& getNameAt(int idx) const;

    void clear();

    void log() const;

    void traverse(NodeAccessor accessor);

private:
    struct Node {
        Node(char ch);

        Node* left_,* right_;
        char ch_;
        T* ptr_;
    };

    Node* root_;
    std::vector<T*> objs_;
    std::vector<std::string> names_;
};

template <typename T>
NamedMap<T>::NamedMap()
    : root_(nullptr)
{}

template <typename T>
NamedMap<T>::~NamedMap()
{
    clear();
}

template <typename T>
template <typename PARSER>
void NamedMap<T>::load(const std::string& fileName,
                       PARSER& parser)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    if (!doc.IsArray())
    {
        THROW_EXCEPT(ParseException, "Invalid json file: " + fileName);
    }

    const rapidjson::Value& arr = doc.GetArray();
    std::string name;
    std::vector<JsonParamPtr> params{
        jsonParam(name, {"name"}, true, k_nonEmptyStrV)
    };
    int numObjects = arr.Capacity();

    objs_.resize(numObjects);
    names_.resize(numObjects);
    for (int i = 0; i < numObjects; ++i)
    {
        parse(params, arr[i]);
        T* t = parser(arr[i]);
        add(name, t);
        objs_[i] = t;
        names_[i] = name;
    }
}

template <typename T>
bool NamedMap<T>::add(const std::string& name,
                      T* t)
{
    unsigned int i;
    unsigned int sz = name.size();
    Node* parent = nullptr;
    Node* n = root_;

    for (i = 0; i < sz && n; ++i)
    {
        Node* prev = nullptr;
        Node* m = n;
        char c = name[i];

        while (m && m->ch_ < c)
        {
            prev = m;
            m = m->right_;
        }

        if (m && m->ch_ == c)
        {
            parent = m;
            n = m->left_;
        }
        else
        {
            Node* p = new Node(c);

            p->right_ = m;
            if (prev)
            {
                prev->right_ = p;
            }
            else if (parent)
            {
                parent->left_ = p;
            }
            else
            {
                root_ = p;
            }

            parent = p;
            n = nullptr;
        }
    }

    if (n)
    {
        if (n->ptr_ != t)
        {
            LOG_WARN << "Trying to add a different pointer for name " << name
                     << LOG_END;
            return false;
        }
        else
        {
            return true;
        }
    }

    for (; i < sz; ++i)
    {
        n = new Node(name[i]);
        if (parent)
        {
            parent->left_ = n;
        }
        else
        {
            root_ = n;
        }
        parent = n;
    }

    if (parent)
    {
        parent->ptr_ = t;
    }

    return true;
}

template <typename T>
T* NamedMap<T>::search(const std::string& name) const
{
    Node* n = root_;
    unsigned int i = 0;
    unsigned int sz = name.size();

    while (i < sz && n)
    {
        char c = name[i];
        while (n && n->ch_ < c)
        {
            n = n->right_;
        }

        if (!n || n->ch_ != c)
        {
            return nullptr;
        }

        ++i;
        if (i < sz)
        {
            n = n->left_;
        }
    }

    return n ? n->ptr_ : nullptr;
}

template <typename T>
int NamedMap<T>::getNumObjs() const
{
    return static_cast<int>(objs_.size());
}

template <typename T>
T* NamedMap<T>::getObjAt(int idx)
{
    return objs_[idx];
}

template <typename T>
const T* NamedMap<T>::getObjAt(int idx) const
{
    return objs_[idx];
}

template <typename T>
const std::string& NamedMap<T>::getNameAt(int idx) const
{
    return names_[idx];
}

template <typename T>
void NamedMap<T>::clear()
{
    if (!root_)
    {
        return;
    }

    std::list<Node*> q;
    q.push_back(root_);

    while (!q.empty())
    {
        Node* n = q.front();
        q.pop_front();

        if (n->left_)
        {
            q.push_back(n->left_);
        }

        if (n->right_)
        {
            q.push_back(n->right_);
        }

        if (n->ptr_)
        {
            delete n->ptr_;
        }

        delete n;
    }

    objs_.clear();
    names_.clear();
}

template <typename T>
void NamedMap<T>::log() const
{
    if (!root_)
    {
        return;
    }

    std::list<Node*> q;
    q.push_back(root_);

    while (!q.empty())
    {
        Node* n = q.front();
        q.pop_front();

        LOG_INFO << n << ' ' << n->ch_ << ' ' << n->left_ << ' ' << n->right_
                 << LOG_END;

        if (n->left_)
        {
            q.push_back(n->left_);
        }

        if (n->right_)
        {
            q.push_back(n->right_);
        }
    }
}

template <typename T>
void NamedMap<T>::traverse(NodeAccessor accessor)
{
    for (auto it = objs_.cbegin(); it != objs_.cend(); ++it)
    {
        if (!accessor(*it))
        {
            break;
        }
    }
}

template <typename T>
NamedMap<T>::Node::Node(char ch)
    : left_(nullptr)
    , right_(nullptr)
    , ch_(ch)
    , ptr_(nullptr)
{}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

