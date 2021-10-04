#ifndef INCLUDED_BOTLIB_LIB_PARSER_H
#define INCLUDED_BOTLIB_LIB_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_tile_template.h>

namespace mcdane {
namespace botlib {

struct TextureLibParser {
    TextureLibParser(const std::string& picDir);

    commonlib::Texture* operator()(const rapidjson::Value& v);

    std::string picDir_;
    std::string fileName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct RectLibParser {
    RectLibParser();

    Rectangle* operator()(const rapidjson::Value& v);

    float width_;
    float height_;
    bool hasTexture_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct GameObjectTemplateParser {
    GameObjectTemplateParser();

    void load(const rapidjson::Value& v);

    float width_;
    float height_;
    float collideBreath_;
    bool invincible_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct TileTemplateLibParser {
    TileTemplateLibParser(
            const commonlib::NamedMap<commonlib::Texture>& textureLib,
            const commonlib::NamedMap<Rectangle>& rectLib);

    TileTemplate* operator()(const rapidjson::Value& v);

    GameObjectTemplateParser gameObjParser_;
    const commonlib::NamedMap<commonlib::Texture>& textureLib_;
    const commonlib::NamedMap<Rectangle>& rectLib_;
    float hp_;
    std::string textureName_;
    std::string rectName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

