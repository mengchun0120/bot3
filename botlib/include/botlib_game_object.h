#ifndef INCLUDED_BOTLIB_GAME_OBJECT_H
#define INCLUDED_BOTLIB_GAME_OBJECT_H

#include <functional>
#include <commonlib_vector.h>
#include <botlib_game_object_template.h>

namespace mcdane {
namespace botlib {

class GameMap;

class GameObject {
public:
    enum Flag {
        FLAG_ALIVE = 0x00000001,
        FLAG_INVINCIBLE = 0x00000002,
        FLAG_UPDATED = 0x00000004
    };

    using Deleter = std::function<void(GameObject*)>;

    GameObject();

    virtual ~GameObject() = default;

    void init(const GameObjectTemplate* t,
              float x,
              float y);

    inline GameObjectType type() const;

    inline float span() const;

    inline float collideBreath() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2 pos() const;

    inline bool alive() const;

    inline bool invincible() const;

    inline bool updated() const;

    inline unsigned int row() const;

    inline unsigned int col() const;

    virtual void update(GameMap& map,
                        float timeDelta);

    virtual void present() const = 0;

    virtual void setPos(float x,
                        float y);

    virtual void shiftPos(float deltaX,
                          float deltaY);

    void setMapPos(unsigned int r,
                   unsigned int c);

    void clearFlags();

    void setAlive(bool b);

    void setInvincible(bool b);

    void setUpdated(bool b);

public:
    static Deleter k_defaultDeleter;

protected:
    void setFlag(Flag flag,
                 bool b);

protected:
    const GameObjectTemplate* t_;
    commonlib::Vector2 pos_;
    int flags_;
    unsigned int row_;
    unsigned int col_;
};

GameObjectType GameObject::type() const
{
    return t_->type();
}

float GameObject::span() const
{
    return t_->span();
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

bool GameObject::alive() const
{
    return flags_ & FLAG_ALIVE;
}

bool GameObject::invincible() const
{
    return flags_ & FLAG_INVINCIBLE;
}

bool GameObject::updated() const
{
    return flags_ & FLAG_UPDATED;
}

unsigned int GameObject::row() const
{
    return row_;
}

unsigned int GameObject::col() const
{
    return col_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

