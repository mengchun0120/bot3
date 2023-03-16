#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_game_object_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectTemplate::GameObjectTemplate()
    : span_(0.0f)
    , collideBreath_(0.0f)
    , invincible_(false)
{
}

void GameObjectTemplate::init(GameObjectType t,
                              const std::string &name,
                              const rapidjson::Value &v)
{
    if (!isValidGameObjectType(t))
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid type " + std::to_string(static_cast<int>(t)));
    }

    type_ = t;
    name_ = name;

    std::vector<JsonParamPtr> params{
        jsonParam(collideBreath_, "collideBreath", true, ge(0.0f)),
        jsonParam(invincible_, "invincible", false)
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane

