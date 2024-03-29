#ifndef INCLUDED_BOTLIB_GAME_OBJECT_H
#define INCLUDED_BOTLIB_GAME_OBJECT_H

#include <commonlib_vector.h>
#include <commonlib_region.h>
#include <botlib_game_object_state.h>
#include <botlib_game_obj_flag.h>
#include <botlib_game_object_template.h>

namespace mcdane {
namespace botlib {

class UpdateContext;
class GameMap;
class GameObjectTemplate;

class GameObject {
public:
    GameObject();

    virtual ~GameObject() = default;

    void init(const GameObjectTemplate *t,
              const commonlib::Vector2 &pos1);

    inline GameObjectType type() const;

    inline const GameObjectTemplate *getTemplate() const;

    inline GameObjectState state() const;

    inline float span() const;

    inline float collideBreath() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2 pos() const;

    inline unsigned int id() const;

    inline float collideLeft() const;

    inline float collideRight() const;

    inline float collideBottom() const;

    inline float collideTop() const;

    inline const commonlib::Region<float> &collideRegion() const;

    inline int flags() const;

    inline bool getFlag(GameObjFlag f) const;

    inline bool invincible() const;

    inline bool updated() const;

    inline bool guided() const;

    inline unsigned int row() const;

    inline unsigned int col() const;

    inline GameObject *prev();

    inline GameObject *next();

    inline const GameObject *prev() const;

    inline const GameObject *next() const;

    virtual void update(UpdateContext &cxt);

    virtual void present() const = 0;

    virtual void setPos(const commonlib::Vector2 &pos1);

    virtual void shiftPos(const commonlib::Vector2 &delta);

    void setMapPos(unsigned int row1,
                   unsigned int col1);

    void clearFlags();

    void setState(GameObjectState newState);

    void setInvincible(bool b);

    void setUpdated(bool b);

    void setGuided(bool b);

    void setFlag(GameObjFlag flag, bool b);

    inline void setPrev(GameObject *o);

    inline void setNext(GameObject *o);

    virtual bool canBeDumped(GameMap &map) const = 0;

    virtual void toJson(rapidjson::Value &v,
                        rapidjson::Document::AllocatorType &allocator);

    virtual inline bool touched(const commonlib::Vector2 &p) const;

protected:
    static unsigned int k_curId;

    const GameObjectTemplate *t_;
    GameObjectState state_;
    unsigned int id_;
    commonlib::Vector2 pos_;
    int flags_;
    unsigned int row_;
    unsigned int col_;
    commonlib::Region<float> collideRegion_;
    GameObject *prev_;
    GameObject *next_;
};

GameObjectType GameObject::type() const
{
    return t_->type();
}

const GameObjectTemplate *GameObject::getTemplate() const
{
    return t_;
}

GameObjectState GameObject::state() const
{
    return state_;
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

unsigned int GameObject::id() const
{
    return id_;
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

const commonlib::Region<float> &GameObject::collideRegion() const
{
    return collideRegion_;
}

int GameObject::flags() const
{
    return flags_;
}

bool GameObject::getFlag(GameObjFlag f) const
{
    return flags_ & static_cast<int>(f);
}

bool GameObject::invincible() const
{
    return getFlag(GameObjFlag::INVINCIBLE);
}

bool GameObject::updated() const
{
    return getFlag(GameObjFlag::UPDATED);
}

bool GameObject::guided() const
{
    return getFlag(GameObjFlag::GUIDED);
}

unsigned int GameObject::row() const
{
    return row_;
}

unsigned int GameObject::col() const
{
    return col_;
}

GameObject *GameObject::prev()
{
    return prev_;
}

GameObject *GameObject::next()
{
    return next_;
}

const GameObject *GameObject::prev() const
{
    return prev_;
}

const GameObject *GameObject::next() const
{
    return next_;
}

void GameObject::setPrev(GameObject *o)
{
    prev_ = o;
}

void GameObject::setNext(GameObject *o)
{
    next_ = o;
}

bool GameObject::touched(const commonlib::Vector2 &p) const
{
    return false;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

