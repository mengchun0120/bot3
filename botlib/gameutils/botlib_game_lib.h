#ifndef INLCUDED_BOTLIB_GAME_LIB_H
#define INLCUDED_BOTLIB_GAME_LIB_H

#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <commonlib_vertex_array.h>
#include <commonlib_input_map.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>
#include <botlib_tile_template.h>
#include <botlib_goodie_template.h>
#include <botlib_missile_template.h>
#include <botlib_skill_template.h>
#include <botlib_ai_robot_template.h>
#include <botlib_particle_effect_template.h>
#include <botlib_progress_pie_template.h>
#include <botlib_progress_bar_template.h>
#include <botlib_icon_template.h>
#include <botlib_player_template.h>
#include <botlib_ai_lib.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class AppConfig;

class GameLib {
public:
    GameLib();

    ~GameLib() = default;

    void init(const AppConfig &cfg);

    inline const commonlib::InputMap &inputMap() const;

    inline const TextureLib &textureLib() const;

    inline const commonlib::Texture *findTexture(const std::string &name) const;

    inline const VertexArrayLib &vertexArrayLib() const;

    inline const commonlib::VertexArray *findVertexArray(const std::string &name) const;

    inline const RectLib &rectLib() const;

    inline const Rectangle *findRect(const std::string &name) const;

    inline const ComponentTemplateLib &componentTemplateLib() const;

    inline const ComponentTemplate *findComponentTemplate(
                                            const std::string &name) const;

    inline const TileTemplateLib &tileTemplateLib() const;

    inline const TileTemplate *findTileTemplate(const std::string &name) const;

    inline const GoodieTemplateLib &goodieTemplateLib() const;

    inline const GoodieTemplate *findGoodieTemplate(const std::string &name) const;

    inline const MissileTemplateLib &missileTemplateLib() const;

    inline const MissileTemplate *findMissileTemplate(
                                            const std::string &name) const;

    inline const SkillTemplateLib &skillTemplateLib() const;

    inline const AIRobotTemplateLib &aiRobotTemplateLib() const;

    inline const AIRobotTemplate *findAIRobotTemplate(
                                            const std::string &name) const;

    inline const ParticleEffectTemplateLib &particleEffectTemplateLib() const;

    inline const ParticleEffectTemplate *findParticleEffectTemplate(
                                            const std::string &name) const;

    inline const ProgressPieTemplateLib &progressPieTemplateLib() const;

    inline const ProgressPieTemplate *findProgressPieTemplate(
                                            const std::string &name) const;

    inline const ProgressBarTemplateLib &progressBarTemplateLib() const;

    inline const ProgressBarTemplate *findProgressBarTemplate(
                                            const std::string &name) const;

    inline const IconTemplateLib &iconTemplateLib() const;

    inline const IconTemplate *findIconTemplate(const std::string &name) const;

    inline const PlayerTemplate &playerTemplate() const;

    inline const AILib &aiLib() const;

    inline float maxObjSpan() const;

    inline float maxCollideBreath() const;

    inline float maxProgressPieRadius() const;

    inline float maxTouchSpan() const;

private:
    void initTextureLib(const std::string &textureLibFile,
                        const std::string &picDir);

    void initVertexArrayLib(const std::string &vertexArrayLibFile,
                            const std::string &dataDir);

    void initRectLib(const std::string &rectLibFile);

    void initIconTemplateLib(const std::string &iconTemplateLibFile);

    void initComponentTemplateLib(const std::string &componentTemplateLibFile);

    void initTileTemplateLib(const std::string &tileTemplateLibFile);

    void initParticleEffectTemplateLib(
        const std::string &particleEffectTemplateLibFile,
        const std::string &dataDir);

    void initProgressPieTemplateLib(const std::string &progressPieTemplateLibFile);

    void initProgressBarTemplateLib(const std::string &progressBarTemplateLibFile);

    void initGoodieTemplateLib(const std::string &goodieTemplateLibFile);

    void initMissileTemplateLib(const std::string &missileTemplateLibFile);

    void initSkillTemplateLib(const std::string &skillTemplateLibFile,
                              const std::string &skillDataDir);

    void initAIRobotTemplateLib(const std::string &aiRobotTemplateLibFile);

    void calculateMaxObjSpan();

    void calculateMaxCollideBreath();

    void calculateMaxProgressPieRadius();

    void calculateMaxTouchSpan();

private:
    commonlib::InputMap inputMap_;
    TextureLib textureLib_;
    VertexArrayLib vertexArrayLib_;
    RectLib rectLib_;
    ComponentTemplateLib componentTemplateLib_;
    TileTemplateLib tileTemplateLib_;
    MissileTemplateLib missileTemplateLib_;
    SkillTemplateLib skillTemplateLib_;
    AIRobotTemplateLib aiRobotTemplateLib_;
    ParticleEffectTemplateLib particleEffectTemplateLib_;
    ProgressPieTemplateLib progressPieTemplateLib_;
    ProgressBarTemplateLib progressBarTemplateLib_;
    GoodieTemplateLib goodieTemplateLib_;
    PlayerTemplate playerTemplate_;
    AILib aiLib_;
    IconTemplateLib iconTemplateLib_;
    float maxObjSpan_;
    float maxCollideBreath_;
    float maxProgressPieRadius_;
    float maxTouchSpan_;
};

const commonlib::InputMap &GameLib::inputMap() const
{
    return inputMap_;
}

const TextureLib &GameLib::textureLib() const
{
    return textureLib_;
}

const commonlib::Texture *GameLib::findTexture(const std::string &name) const
{
    return textureLib_.search(name);
}

const VertexArrayLib &GameLib::vertexArrayLib() const
{
    return vertexArrayLib_;
}

const commonlib::VertexArray *GameLib::findVertexArray(const std::string &name) const
{
    return vertexArrayLib_.search(name);
}

const RectLib &GameLib::rectLib() const
{
    return rectLib_;
}

const Rectangle *GameLib::findRect(const std::string &name) const
{
    return rectLib_.search(name);
}

const ComponentTemplateLib &GameLib::componentTemplateLib() const
{
    return componentTemplateLib_;
}

const ComponentTemplate *GameLib::findComponentTemplate(
                                        const std::string &name) const
{
    return componentTemplateLib_.search(name);
}

const TileTemplateLib &GameLib::tileTemplateLib() const
{
    return tileTemplateLib_;
}

const TileTemplate *GameLib::findTileTemplate(const std::string &name) const
{
    return tileTemplateLib_.search(name);
}

const GoodieTemplateLib &GameLib::goodieTemplateLib() const
{
    return goodieTemplateLib_;
}

const GoodieTemplate *GameLib::findGoodieTemplate(const std::string &name) const
{
    return goodieTemplateLib_.search(name);
}

const MissileTemplateLib &GameLib::missileTemplateLib() const
{
    return missileTemplateLib_;
}

const SkillTemplateLib &GameLib::skillTemplateLib() const
{
    return skillTemplateLib_;
}

const MissileTemplate *GameLib::findMissileTemplate(
                                       const std::string &name) const
{
    return missileTemplateLib_.search(name);
}

const AIRobotTemplateLib &GameLib::aiRobotTemplateLib() const
{
    return aiRobotTemplateLib_;
}

const AIRobotTemplate *GameLib::findAIRobotTemplate(
                                        const std::string &name) const
{
    return aiRobotTemplateLib_.search(name);
}

const ParticleEffectTemplateLib &GameLib::particleEffectTemplateLib() const
{
    return particleEffectTemplateLib_;
}

const ParticleEffectTemplate *GameLib::findParticleEffectTemplate(
                                        const std::string &name) const
{
    return particleEffectTemplateLib_.search(name);
}

const ProgressPieTemplateLib &GameLib::progressPieTemplateLib() const
{
    return progressPieTemplateLib_;
}

const ProgressPieTemplate *GameLib::findProgressPieTemplate(
                                            const std::string &name) const
{
    return progressPieTemplateLib_.search(name);
}

const ProgressBarTemplateLib &GameLib::progressBarTemplateLib() const
{
    return progressBarTemplateLib_;
}

const ProgressBarTemplate *GameLib::findProgressBarTemplate(
                                            const std::string &name) const
{
    return progressBarTemplateLib_.search(name);
}

const IconTemplateLib &GameLib::iconTemplateLib() const
{
    return iconTemplateLib_;
}

const IconTemplate *GameLib::findIconTemplate(const std::string &name) const
{
    return iconTemplateLib_.search(name);
}

const PlayerTemplate &GameLib::playerTemplate() const
{
    return playerTemplate_;
}

const AILib &GameLib::aiLib() const
{
    return aiLib_;
}

float GameLib::maxObjSpan() const
{
    return maxObjSpan_;
}

float GameLib::maxCollideBreath() const
{
    return maxCollideBreath_;
}

float GameLib::maxProgressPieRadius() const
{
    return maxProgressPieRadius_;
}

float GameLib::maxTouchSpan() const
{
    return maxTouchSpan_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

