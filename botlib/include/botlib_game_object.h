#ifndef INCLUDED_BOTLIB_GAME_OBJECT_H
#define INCLUDED_BOTLIB_GAME_OBJECT_H

#include <functional>
#include <commonlib_vector.h>
#include <commonlib_region.h>
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
              const commonlib::Vector2& pos1);

    inline GameObjectType type() const;

    inline float span() const;

    inline float collideBreath() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2 pos() const;

    inline float collideLeft() const;

    inline float collideRight() const;

    inline float collideBottom() const;

    inline float collideTop() const;

    inline const commonlib::Region<float>& collideRegion() const;

    inline bool alive() const;

    inline bool invincible() const;

    inline bool updated() const;

    inline unsigned int row() const;

    inline unsigned int col() const;

    virtual void update(GameMap& map,
                        float timeDelta);

    virtual void present() const = 0;

    virtual void setPos(const commonlib::Vector2& pos1);

    virtual void shiftPos(const commonlib::Vector2& delta);

    void setMapPos(unsigned int row1,
                   unsigned int col1);

    void clearFlags();

    void setAlive(bool b);

    void setInvincible(bool b);

    void setUpdated(bool b);

    void setFlag(Flag flag,
                 bool b);

public:
    static Deleter k_defaultDeleter;

protected:
protected:
    const GameObjectTemplate* t_;
    commonlib::Vector2 pos_;
    int flags_;
    unsigned int row_;
    unsigned int col_;
    commonlib::Region<float> collideRegion_;
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

float GameObject::collideLeft() const
{
    return x() - collideBreath();
}

float GameObject::collideRight() const
{
    return x() + collideBreath();
}

float GameObject::collideBottom() const
{
    return y() - collideBreath();
}

float GameObject::collideTop() const
{
    return y() + collideBreath();
}

const commonlib::Region<float>& GameObject::collideRegion() const
{
    return collideRegion_;
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

