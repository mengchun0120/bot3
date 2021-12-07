#ifndef INLCUDED_BOTLIB_GAME_LIB_H
#define INLCUDED_BOTLIB_GAME_LIB_H

#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>
#include <botlib_tile_template.h>
#include <botlib_ai_robot_template.h>

namespace mcdane {
namespace botlib {

class GameLib {
public:
    static void initInstance(const std::string& picDir,
                             const std::string& textureLibFile,
                             const std::string& rectLibFile,
                             const std::string& componentTemplateLibFile,
                             const std::string& tileTemplateLibFile,
                             const std::string& aiRobotTemplateLibFile);

    inline static const GameLib& getInstance();

    ~GameLib() = default;

    inline const commonlib::Texture* findTexture(const std::string& name) const;

    inline const Rectangle* findRect(const std::string& name) const;

    inline const ComponentTemplate* findComponentTemplate(
                                                const std::string& name) const;

    inline const TileTemplate* findTileTemplate(const std::string& name) const;

    inline const AIRobotTemplate* findAIRobotTemplate(
                                                const std::string& name) const;

    inline float maxObjSpan() const;

    inline float maxCollideBreath() const;

private:
    GameLib() = default;

    void load(const std::string& picDir,
              const std::string& textureLibFile,
              const std::string& rectLibFile,
              const std::string& componentTemplateLibFile,
              const std::string& tileTemplateLibFile,
              const std::string& aiRobotTemplateLibFile);

    void calculateMaxObjSpan();

    void calculateMaxCollideBreath();

private:
    static std::shared_ptr<GameLib> k_gameLib;

    commonlib::NamedMap<commonlib::Texture> textureLib_;
    commonlib::NamedMap<Rectangle> rectLib_;
    commonlib::NamedMap<ComponentTemplate> componentTemplateLib_;
    commonlib::NamedMap<TileTemplate> tileTemplateLib_;
    commonlib::NamedMap<AIRobotTemplate> aiRobotTemplateLib_;
    float maxObjSpan_;
    float maxCollideBreath_;
};

const GameLib& GameLib::getInstance()
{
    return *k_gameLib;
}

const commonlib::Texture* GameLib::findTexture(const std::string& name) const
{
    return textureLib_.search(name);
}

const Rectangle* GameLib::findRect(const std::string& name) const
{
    return rectLib_.search(name);
}

const ComponentTemplate* GameLib::findComponentTemplate(
                                                const std::string& name) const
{
    return componentTemplateLib_.search(name);
}

const TileTemplate* GameLib::findTileTemplate(const std::string& name) const
{
    return tileTemplateLib_.search(name);
}

const AIRobotTemplate* GameLib::findAIRobotTemplate(
                                                const std::string& name) const
{
    return aiRobotTemplateLib_.search(name);
}

float GameLib::maxObjSpan() const
{
    return maxObjSpan_;
}

float GameLib::maxCollideBreath() const
{
    return maxCollideBreath_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

