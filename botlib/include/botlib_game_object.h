#ifndef INCLUDED_BOTLIB_GAME_OBJECT_H
#define INCLUDED_BOTLIB_GAME_OBJECT_H

#include <commonlib_vector.h>
#include <botlib_game_object_template.h>

namespace mcdane {
namespace botlib {

class GameObject {
public:
    GameObject();

    GameObject(const GameObjectTemplate* t,
               float x,
               float y);

    virtual ~GameObject() = default;

    void init(const GameObjectTemplate* t,
              float x,
              float y);

    inline GameObjectType type() const;

    inline float collideBreath() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2 pos() const;

    inline float width() const;

    inline float height() const;

    inline bool alive() const;

    inline virtual void update();

    virtual void present() = 0;

    virtual void setPos(float x,
                        float y);

protected:
    const GameObjectTemplate* t_;
    commonlib::Vector2 pos_;
    bool alive_;
};

GameObjectType GameObject::type() const
{
    return t_->type();
}

float GameObject::collideBreath() const
{
    return t_->collideBreath();
}

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

float GameObject::width() const
{
    return t_->width();
}

float GameObject::height() const
{
    return t_->height();
}

bool GameObject::alive() const
{
    return alive_;
}

void GameObject::update()
{
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

