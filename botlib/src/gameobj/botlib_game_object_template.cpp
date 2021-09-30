#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_string_utils.h>
#include <botlib_game_object_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectTemplate::GameObjectTemplate(GameObjectType t,
                                       const rapidjson::Value& v)
    : invincible_(false)
    , collideBreath_(0.0f)
{
}

void GameObjectTemplate::init(GameObjectType t,
                              const rapidjson::Value& v)
{
    if (!isValidGameObjectType(t))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid type " + toString(static_cast<int>(t)));
    }

    std::vector<JsonParam> params{
        jsonParam(invincible_, {"invincible"}, false),
        jsonParam(collideBreath_, {"collideBreath"}, false,
                  ge(collideBreath_, 0.0f))
    };

    parse(params, v);
    type_ = type;
}

} // end of namespace botlib
} // end of namespace mcdane

