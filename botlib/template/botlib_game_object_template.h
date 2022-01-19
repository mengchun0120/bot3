#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H

#include <botlib_game_object_type.h>
#include <commonlib_object.h>

namespace mcdane {
namespace botlib {

class GameObjectTemplate: public commonlib::Object {
public:
    GameObjectTemplate() = default;

    GameObjectTemplate(GameObjectType t,
                       float span,
                       float collideBreath,
                       bool invincible=false);

    virtual ~GameObjectTemplate() = default;

    void init(GameObjectType t,
              float span,
              float collideBreath,
              bool invincible=false);

    inline GameObjectType type() const;

    inline float span() const;

    inline float collideBreath() const;

    inline bool invincible() const;

    std::string toString() const override;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

protected:
    GameObjectType type_;
    float span_;
    float collideBreath_;
    bool invincible_;
};

GameObjectType GameObjectTemplate::type() const
{
    return type_;
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

