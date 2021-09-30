#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H

#include <rapidjson/document.h>
#include <botlib_game_object_type.h>

namespace mcdane {
namespace botlib {

class GameObjectTemplate {
public:
    GameObjectTemplate(GameObjectType t,
                       const rapidjson::Value& v);

    virtual ~GameObjectTemplate() = default;

    inline GameObjectType type() const;

    inline bool invincible() const;

    inline float collideBreath() const;

private:
    void init(GameObjectType t,
              const rapidjson::Value& v);

protected:
    GameObjectType type_;
    bool invincible_;
    float collideBreath_;
};

GameObjectType GameObjectTemplate::type() const
{
    return type_;
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

