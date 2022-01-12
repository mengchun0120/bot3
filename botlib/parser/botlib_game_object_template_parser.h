#ifndef INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_GAME_OBJECT_TEMPLATE_PARSER_H

#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>

namespace mcdane {
namespace botlib {

class GameObjectTemplateParser {
public:
    GameObjectTemplateParser();

    void load(const rapidjson::Value& v);

protected:
    float collideBreath_;
    bool invincible_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

