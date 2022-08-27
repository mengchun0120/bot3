#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H

#include <string>
#include <botlib_game_object_type.h>

namespace mcdane {
namespace botlib {

class GameObjectTemplate {
public:
    GameObjectTemplate() = default;

    virtual ~GameObjectTemplate() = default;

    void init(GameObjectType t,
              const std::string& name,
              const rapidjson::Value& v);

    inline GameObjectType type() const;

    inline const std::string& name() const;

    inline float span() const;

    inline float collideBreath() const;

    inline bool invincible() const;

protected:
    GameObjectType type_;
    std::string name_;
    float span_;
    float collideBreath_;
    bool invincible_;
};

GameObjectType GameObjectTemplate::type() const
{
    return type_;
}

const std::string& GameObjectTemplate::name() const
{
    return name_;
}

float GameObjectTemplate::span() const
{
    return span_;
}

float GameObjectTemplate::collideBreath() const
{
    return collideBreath_;
}

bool GameObjectTemplate::invincible() const
{
    return invincible_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

