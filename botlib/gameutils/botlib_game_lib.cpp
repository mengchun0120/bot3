#include <commonlib_log.h>
#include <botlib_ai_robot_template_parser.h>
#include <botlib_component_template_parser.h>
#include <botlib_missile_template_parser.h>
#include <botlib_robot_template_parser.h>
#include <botlib_tile_template_parser.h>
#include <botlib_particle_effect_template_parser.h>
#include <botlib_player_template_parser.h>
#include <botlib_game_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<GameLib> GameLib::k_gameLib;

void GameLib::initInstance(const std::string& picDir,
                           const std::string& libDir,
                           const std::string& textureLibFile,
                           const std::string& rectLibFile,
                           const std::string& componentTemplateLibFile,
                           const std::string& tileTemplateLibFile,
                           const std::string& missileTemplateLibFile,
                           const std::string& aiRobotTemplateLibFile,
                           const std::string& particleEffectTemplateLibFile,
                           const std::string& playerTemplateFile)
{
    GameLib* lib = new GameLib();
    lib->load(
        picDir,
        libDir,
        textureLibFile,
        rectLibFile,
        componentTemplateLibFile,
        tileTemplateLibFile,
        missileTemplateLibFile,
        aiRobotTemplateLibFile,
        particleEffectTemplateLibFile,
        playerTemplateFile);

    k_gameLib.reset(lib);
}

void GameLib::load(const std::string& picDir,
                   const std::string& libDir,
                   const std::string& textureLibFile,
                   const std::string& rectLibFile,
                   const std::string& componentTemplateLibFile,
                   const std::string& tileTemplateLibFile,
                   const std::string& missileTemplateLibFile,
                   const std::string& aiRobotTemplateLibFile,
                   const std::string& particleEffectTemplateLibFile,
                   const std::string& playerTemplateFile)
{
    initTextureLib(textureLibFile, picDir);
    initRectLib(rectLibFile);
    initComponentTemplateLib(componentTemplateLibFile);
    initTileTemplateLib(tileTemplateLibFile);
    initParticleEffectTemplateLib(particleEffectTemplateLibFile, libDir);

    MissileTemplateParser missileTemplateParser(componentTemplateLib_,
                                                particleEffectTemplateLib_);
    missileTemplateLib_.load(missileTemplateLibFile, missileTemplateParser);

    LOG_DEBUG << "missileTemplateLib Loaded: "
              << missileTemplateLib_
              << LOG_END;

    AIRobotTemplateParser aiRobotTemplateParser(missileTemplateLib_,
                                                componentTemplateLib_);
    aiRobotTemplateLib_.load(aiRobotTemplateLibFile, aiRobotTemplateParser);

    LOG_DEBUG << "aiRobotTemplateLib Loaded: "
              << aiRobotTemplateLib_
              << LOG_END;

    PlayerTemplateParser playerTemplateParser(missileTemplateLib_,
                                              componentTemplateLib_);
    playerTemplateParser.load(playerTemplate_, playerTemplateFile);

    LOG_DEBUG << "playerTemplate Loaded: "
              << playerTemplate_
              << LOG_END;

    calculateMaxObjSpan();
    calculateMaxCollideBreath();

    LOG_DEBUG << "maxObjSpan=" << maxObjSpan_
              << "maxCollideBreath=" << maxCollideBreath_
              << LOG_END;

    LOG_INFO << "GameLib loaded successfull" << LOG_END;
}

void GameLib::initTextureLib(const std::string& textureLibFile,
                             const std::string& picDir)
{
    auto parser = [&](Texture& texture,
                      const rapidjson::Value& v)
    {
        texture.init(v, picDir, true);
    };

    textureLib_.init(textureLibFile, parser);

    LOG_DEBUG << "textureLib loaded successfully: " << textureLib_ << LOG_END;
}

void GameLib::initRectLib(const std::string& rectLibFile)
{
    auto parser = [&](Rectangle& rect,
                      const rapidjson::Value& v)
    {
        rect.init(v, true);
    };

    rectLib_.init(rectLibFile, parser);

    LOG_DEBUG << "rectLib loaded successfully: " << rectLib_ << LOG_END;
}

void GameLib::initComponentTemplateLib(
                    const std::string& componentTemplateLibFile)
{
    auto parser = [&](ComponentTemplate& t,
                      const rapidjson::Value& v)
    {
        t.init(v, textureLib_, rectLib_);
    };

    componentTemplateLib_.init(componentTemplateLibFile, parser);

    LOG_DEBUG << "componentTemplateLib loaded successfully: "
              << componentTemplateLib_ << LOG_END;
}

void GameLib::initTileTemplateLib(const std::string& tileTemplateLibFile)
{
    auto parser = [&](TileTemplate& t,
                      const rapidjson::Value& v)
    {
        t.init(v, componentTemplateLib_);
    };

    tileTemplateLib_.init(tileTemplateLibFile, parser);

    LOG_DEBUG << "tileTemplateLib loaded successfully: "
              << tileTemplateLib_ << LOG_END;
}

void GameLib::initParticleEffectTemplateLib(
    const std::string& particleEffectTemplateLibFile,
    const std::string& libDir)
{
    auto parser = [&](ParticleEffectTemplate& t,
                      const rapidjson::Value& v)
    {
        t.init(v, textureLib_, libDir);
    };

    particleEffectTemplateLib_.init(particleEffectTemplateLibFile, parser);

    LOG_DEBUG << "particleEffectTemplateLib loaded successfully: "
              << particleEffectTemplateLib_ << LOG_END;
}

void GameLib::calculateMaxObjSpan()
{
    maxObjSpan_ = playerTemplate_.span();

    auto accessor = [this](const GameObjectTemplate* t)->bool
    {
        if (t->span() > maxObjSpan_)
        {
            maxObjSpan_ = t->span();
        }

        return true;
    };

    tileTemplateLib_.traverse(accessor);
    missileTemplateLib_.traverse(accessor);
    aiRobotTemplateLib_.traverse(accessor);
    particleEffectTemplateLib_.traverse(accessor);

    LOG_INFO << "maxObjSpan=" << maxObjSpan_ << LOG_END;
}

void GameLib::calculateMaxCollideBreath()
{
    maxCollideBreath_ = playerTemplate_.collideBreath();

    auto accessor = [this](const GameObjectTemplate* t)->bool
    {
        if (t->collideBreath() > maxCollideBreath_)
        {
            maxCollideBreath_ = t->collideBreath();
        }

        return true;
    };

    tileTemplateLib_.traverse(accessor);
    missileTemplateLib_.traverse(accessor);
    aiRobotTemplateLib_.traverse(accessor);

    LOG_INFO << "maxCollideBreath=" << maxCollideBreath_ << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

