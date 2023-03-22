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

    inline float stopRadius() const;

    inline float arrowRadius() const;

    inline float alpha() const;

    inline const commonlib::Texture &baseTexture() const;

    inline const commonlib::Texture &arrowTexture() const;

    inline const Rectangle &baseRect() const;

    inline const Rectangle &arrowRect() const;

private:
    void initTexture(const std::string &baseTextureFile,
                     const std::string &arrowTextureFile);

    void initRect(float baseWidth, float baseHeight,
                  float arrowWidth, float arrowHeight);

private:
    float baseRadius_;
    float stopRadius_;
    float arrowRadius_;
    float alpha_;
    commonlib::Texture baseTexture_;
    commonlib::Texture arrowTexture_;
    Rectangle baseRect_;
    Rectangle arrowRect_;
};

float GameNavigatorConfig::baseRadius() const
{
    return baseRadius_;
}

float GameNavigatorConfig::stopRadius() const
{
    return stopRadius_;
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

const commonlib::Texture &GameNavigatorConfig::arrowTexture() const
{
    return arrowTexture_;
}

const Rectangle &GameNavigatorConfig::baseRect() const
{
    return baseRect_;
}

const Rectangle &GameNavigatorConfig::arrowRect() const
{
    return arrowRect_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
