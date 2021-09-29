#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_H

#include <rapidjson/document.h>

namespace mcdane {
namespace botlib {

class GameObjectTemplate {
public:
    GameObjectTemplate(const rapidjson::Value& v);

    virtual ~GameObjectTemplate() = default;

    inline bool invincible() const;

    inline float collideBreath() const;

private:
    void init(const rapidjson::Value& v);

protected:
    bool invincible_;
    float collideBreath_;
};

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

