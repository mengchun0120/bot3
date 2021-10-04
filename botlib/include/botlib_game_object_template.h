#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H

#include <botlib_game_object_type.h>

namespace mcdane {
namespace botlib {

class GameObjectTemplate {
public:
    GameObjectTemplate(GameObjectType t,
                       float width,
                       float height,
                       float collideBreath,
                       bool invincible=false);

    virtual ~GameObjectTemplate() = default;

    inline GameObjectType type() const;

    inline float width() const;

    inline float height() const;

    inline float collideBreath() const;

    inline bool invincible() const;

private:
    void init(GameObjectType t,
              float width,
              float height,
              float collideBreath,
              bool invincible=false);

protected:
    GameObjectType type_;
    float width_;
    float height_;
    float collideBreath_;
    bool invincible_;
};

GameObjectType GameObjectTemplate::type() const
{
    return type_;
}

float GameObjectTemplate::width() const
{
    return width_;
}

float GameObjectTemplate::height() const
{
    return height_;
}

bool GameObjectTemplate::invincible() const
{
    return invincible_;
}

float GameObjectTemplate::collideBreath() const
{
    return collideBreath_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

