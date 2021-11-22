#ifndef INCLUDED_BOTLIB_LIB_PARSER_H
#define INCLUDED_BOTLIB_LIB_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>
#include <botlib_component.h>
#include <botlib_tile_template.h>

namespace mcdane {
namespace botlib {

struct TextureParser {
    TextureParser(const std::string& picDir);

    commonlib::Texture* operator()(const rapidjson::Value& v);

    std::string picDir_;
    std::string fileName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct RectParser {
    RectParser();

    Rectangle* operator()(const rapidjson::Value& v);

    float width_;
    float height_;
    bool hasTexture_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct ComponentTemplateParser {
    ComponentTemplateParser(
            const commonlib::NamedMap<commonlib::Texture>& textureLib,
            const commonlib::NamedMap<Rectangle>& rectLib);

    ComponentTemplate* operator()(const rapidjson::Value& v);

    const commonlib::NamedMap<commonlib::Texture>& textureLib_;
    const commonlib::NamedMap<Rectangle>& rectLib_;
    std::string textureName_;
    std::string rectName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct ComponentParser {
    ComponentParser(
            const commonlib::NamedMap<ComponentTemplate>& componentLib);

    void initComponent(Component& c,
                       const rapidjson::Value& v);

    const commonlib::NamedMap<ComponentTemplate>& componentLib_;
    std::string templateName_;
    commonlib::Vector2 pos_;
    commonlib::Vector2 direction_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct GameObjectTemplateParser {
    GameObjectTemplateParser();

    void load(const rapidjson::Value& v);

    float collideBreath_;
    bool invincible_;
    std::vector<commonlib::JsonParamPtr> params_;
};

struct CompositeObjectTemplateParser {
    CompositeObjectTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentLib);

    void load(const rapidjson::Value& v);

    ComponentParser componentParser_;
    std::vector<Component> components_;
};

struct TileTemplateParser {
    TileTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib);

    TileTemplate* operator()(const rapidjson::Value& v);

    GameObjectTemplateParser gameObjTemplateParser_;
    CompositeObjectTemplateParser compositeObjTemplateParser_;
    float hp_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

