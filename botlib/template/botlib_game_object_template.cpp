#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_game_object_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectTemplate::GameObjectTemplate(GameObjectType t,
                                       float span,
                                       float collideBreath,
                                       bool invincible)
{
    init(t, span, collideBreath, invincible);
}

void GameObjectTemplate::init(GameObjectType t,
                              float span,
                              float collideBreath,
                              bool invincible)
{
    if (!isValidGameObjectType(t))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid type " + std::to_string(static_cast<int>(t)));
    }

    if (span < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid span " + std::to_string(span));
    }

    type_ = t;
    span_ = span;
    collideBreath_ = collideBreath;
    invincible_ = invincible;
}

std::string GameObjectTemplate::toString() const
{
    std::ostringstream oss;

    oss << "GameObjectTemplate(type=" << type_
        << ", span=" << span_
        << ", collideBreath=" << collideBreath_
        << ", invincible=" << invincible_
        << ", Base=" << Object::toString()
        << ")";

    return oss.str();
}

rapidjson::Value GameObjectTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "GameObjectTemplate", allocator);
    v.AddMember("type", jsonVal(stringVal(type_), allocator), allocator),
    v.AddMember("span", span_, allocator);
    v.AddMember("collideBreath", collideBreath_, allocator);
    v.AddMember("invincible", invincible_, allocator);
    v.AddMember("base", Object::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

