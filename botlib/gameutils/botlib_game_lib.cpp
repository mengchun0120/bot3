#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_game_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<GameLib> GameLib::k_gameLib;

void GameLib::initInstance(const AppConfig& cfg)
{
    GameLib* lib = new GameLib(cfg);
    k_gameLib.reset(lib);
}

GameLib::GameLib(const AppConfig& cfg)
{
    load(cfg);
}

void GameLib::load(const AppConfig& cfg)
{
    initTextureLib(cfg.textureLibFile(), cfg.picDir());
    initRectLib(cfg.rectLibFile());
    initComponentTemplateLib(cfg.componentTemplateLibFile());
    initTileTemplateLib(cfg.tileTemplateLibFile());
    initParticleEffectTemplateLib(cfg.particleEffectTemplateLibFile(),
                                  cfg.libDir());
    initMissileTemplateLib(cfg.missileTemplateLibFile());
    initAIRobotTemplateLib(cfg.aiRobotTemplateLibFile());
    playerTemplate_.init(cfg.playerTemplateFile(),
                         missileTemplateLib_,
                         componentTemplateLib_);

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

void GameLib::initMissileTemplateLib(const std::string& missileTemplateLibFile)
{
    auto parser = [&](MissileTemplate& t,
                      const rapidjson::Value& v)
    {
        t.init(v, particleEffectTemplateLib_, componentTemplateLib_);
    };

    missileTemplateLib_.init(missileTemplateLibFile, parser);

    LOG_DEBUG << "missileTemplateLib loaded successfully: "
              << missileTemplateLib_ << LOG_END;
}

void GameLib::initAIRobotTemplateLib(const std::string& aiRobotTemplateLibFile)
{
    auto parser = [&](AIRobotTemplate& t,
                      const rapidjson::Value& v)
    {
        t.init(v, missileTemplateLib_, componentTemplateLib_);
    };

    aiRobotTemplateLib_.init(aiRobotTemplateLibFile, parser);

    LOG_DEBUG << "aiRobotTemplateLib loaded successfully: "
              << aiRobotTemplateLib_ << LOG_END;
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

