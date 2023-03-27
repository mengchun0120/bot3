#ifndef INCLUDED_BOTLIB_GAME_NAVIGATOR_CONFIG_H
#define INCLUDED_BOTLIB_GAME_NAVIGATOR_CONFIG_H

#include <commonlib_texture.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class GameNavigatorConfig {
public:
    GameNavigatorConfig() = default;

    ~GameNavigatorConfig() = default;

    void init(const std::string &fileName);

    inline float baseRadius() const;

    inline float toggleRadius() const;

    inline float arrowRadius() const;

    inline float alpha() const;

    inline const commonlib::Texture &baseTexture() const;

    inline const commonlib::Texture &toggleButton(int idx) const;

    inline const commonlib::Texture &arrowTexture() const;

    inline const Rectangle &baseRect() const;

    inline const Rectangle &toggleRect() const;

    inline const Rectangle &arrowRect() const;

private:
    void initTexture(const std::string &baseTextureFile,
                     const std::vector<std::string> &toggleButtonFiles,
                     const std::string &arrowTextureFile);

    void initRect(float arrowWidth, float arrowHeight);

private:
    float baseRadius_;
    float toggleRadius_;
    float arrowRadius_;
    float alpha_;
    commonlib::Texture baseTexture_;
    std::vector<commonlib::Texture> toggleButtons_;
    commonlib::Texture arrowTexture_;
    Rectangle baseRect_;
    Rectangle toggleRect_;
    Rectangle arrowRect_;
};

float GameNavigatorConfig::baseRadius() const
{
    return baseRadius_;
}

float GameNavigatorConfig::toggleRadius() const
{
    return toggleRadius_;
}

float GameNavigatorConfig::arrowRadius() const
{
    return arrowRadius_;
}

float GameNavigatorConfig::alpha() const
{
    return alpha_;
}

const commonlib::Texture &GameNavigatorConfig::baseTexture() const
{
    return baseTexture_;
}

const commonlib::Texture &GameNavigatorConfig::toggleButton(int idx) const
{
    return toggleButtons_[idx];
}

const commonlib::Texture &GameNavigatorConfig::arrowTexture() const
{
    return arrowTexture_;
}

const Rectangle &GameNavigatorConfig::baseRect() const
{
    return baseRect_;
}

const Rectangle &GameNavigatorConfig::toggleRect() const
{
    return toggleRect_;
}

const Rectangle &GameNavigatorConfig::arrowRect() const
{
    return arrowRect_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
