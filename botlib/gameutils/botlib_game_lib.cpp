#include <commonlib_log.h>
#include <botlib_ai_robot_template_parser.h>
#include <botlib_component_template_parser.h>
#include <botlib_missile_template_parser.h>
#include <botlib_rect_parser.h>
#include <botlib_robot_template_parser.h>
#include <botlib_texture_parser.h>
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
    lib->load(picDir,
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
    TextureParser textureParser(picDir);
    textureLib_.load(textureLibFile, textureParser);

    LOG_DEBUG << "textureLib Loaded: "
              << textureLib_
              << LOG_END;

    RectParser rectParser;
    rectLib_.load(rectLibFile, rectParser);

    LOG_DEBUG << "rectLib Loaded: "
              << rectLib_
              << LOG_END;

    ComponentTemplateParser componentTemplateParser(textureLib_, rectLib_);
    componentTemplateLib_.load(componentTemplateLibFile,
                               componentTemplateParser);

    LOG_DEBUG << "componentTemplateLib Loaded: "
              << componentTemplateLib_
              << LOG_END;

    TileTemplateParser tileTemplateParser(componentTemplateLib_);
    tileTemplateLib_.load(tileTemplateLibFile, tileTemplateParser);

    LOG_DEBUG << "tileTemplate Loaded: "
              << tileTemplateLib_
              << LOG_END;

    ParticleEffectTemplateParser particleEffectTemplateParser(libDir, textureLib_);
    particleEffectTemplateLib_.load(particleEffectTemplateLibFile,
                                    particleEffectTemplateParser);

    LOG_DEBUG << "particleEffectTemplateLib Loaded: "
              << particleEffectTemplateLib_
              << LOG_END;

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

