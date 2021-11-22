#ifndef INLCUDED_BOTLIB_GAME_LIB_H
#define INLCUDED_BOTLIB_GAME_LIB_H

#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>
#include <botlib_tile_template.h>

namespace mcdane {
namespace botlib {

class GameLib {
public:
    static void initInstance(const std::string& textureLibFile,
                             const std::string& rectLibFile,
                             const std::string& componentTemplateLibFile,
                             const std::string& tileTemplateLibFile,
                             const std::string& picDir);

    inline static const GameLib& getInstance();

    ~GameLib() = default;

    inline const commonlib::Texture* findTexture(const std::string& name) const;

    inline const Rectangle* findRect(const std::string& name) const;

    inline const ComponentTemplate* findComponentTemplate(
                                                const std::string& name) const;

    inline const TileTemplate* findTileTemplate(const std::string& name) const;

private:
    GameLib() = default;

    void load(const std::string& textureLibFile,
              const std::string& rectLibFile,
              const std::string& componentTemplateLibFile,
              const std::string& tileTemplateLibFile,
              const std::string& picDir);

private:
    static std::shared_ptr<GameLib> k_gameLib;

    commonlib::NamedMap<commonlib::Texture> textureLib_;
    commonlib::NamedMap<Rectangle> rectLib_;
    commonlib::NamedMap<ComponentTemplate> componentTemplateLib_;
    commonlib::NamedMap<TileTemplate> tileTemplateLib_;
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

} // end of namespace botlib
} // end of namespace mcdane

#endif

