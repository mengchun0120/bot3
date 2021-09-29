#ifndef INCLUDED_BOTLIB_GAME_OBJECT_H
#define INCLUDED_BOTLIB_GAME_OBJECT_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class GameObject {
public:
    GameObject() = default;

    virtual ~GameObject() = default;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2 pos() const;

    virtual void update() = 0;

    virtual void present() = 0;

protected:
    commonlib::Vector2 pos_;
};

float GameObject::x() const
{
    return pos_[0];
}

float GameObject::y() const
{
    return pos_[1];
}

const commonlib::Vector2 GameObject::pos() const
{
    return pos_;
}


} // end of namespace botlib
} // end of namespace mcdane

#endif

