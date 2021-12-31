#include <botlib_game_object_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameObjectTemplateParser::GameObjectTemplateParser()
    : invincible_(false)
    , params_{
        jsonParam(collideBreath_, "collideBreath", true, ge(0.0f)),
        jsonParam(invincible_, "invincible", false)
      }
{
}

void GameObjectTemplateParser::load(const rapidjson::Value& v)
{
    invincible_ = false;
    parse(params_, v);
}

} // end of namespace botlib
} // end of namespace mcdane

