#include <commonlib_log.h>
#include <botlib_ai_robot_template_parser.h>
#include <botlib_component_template_parser.h>
#include <botlib_missile_template_parser.h>
#include <botlib_rect_parser.h>
#include <botlib_robot_template_parser.h>
#include <botlib_texture_parser.h>
#include <botlib_tile_template_parser.h>
#include <botlib_game_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<GameLib> GameLib::k_gameLib;

void GameLib::initInstance(const std::string& picDir,
                           const std::string& textureLibFile,
                           const std::string& rectLibFile,
                           const std::string& componentTemplateLibFile,
                           const std::string& tileTemplateLibFile,
                           const std::string& missileTemplateLibFile,
                           const std::string& aiRobotTemplateLibFile)
{
    GameLib* lib = new GameLib();
    lib->load(picDir, textureLibFile, rectLibFile, componentTemplateLibFile,
              tileTemplateLibFile, missileTemplateLibFile, aiRobotTemplateLibFile);
    k_gameLib.reset(lib);
}

void GameLib::load(const std::string& picDir,
                   const std::string& textureLibFile,
                   const std::string& rectLibFile,
                   const std::string& componentTemplateLibFile,
                   const std::string& tileTemplateLibFile,
                   const std::string& missileTemplateLibFile,
                   const std::string& aiRobotTemplateLibFile)
{
    TextureParser textureParser(picDir);
    textureLib_.load(textureLibFile, textureParser);

    RectParser rectParser;
    rectLib_.load(rectLibFile, rectParser);

    ComponentTemplateParser componentTemplateParser(textureLib_, rectLib_);
    componentTemplateLib_.load(componentTemplateLibFile,
                               componentTemplateParser);

    TileTemplateParser tileTemplateParser(componentTemplateLib_);
    tileTemplateLib_.load(tileTemplateLibFile, tileTemplateParser);

    MissileTemplateParser missileTemplateParser(componentTemplateLib_);
    missileTemplateLib_.load(missileTemplateLibFile, missileTemplateParser);

    AIRobotTemplateParser aiRobotTemplateParser(missileTemplateLib_,
                                                componentTemplateLib_);
    aiRobotTemplateLib_.load(aiRobotTemplateLibFile, aiRobotTemplateParser);

    calculateMaxObjSpan();
    calculateMaxCollideBreath();

    LOG_INFO << "GameLib loaded successfull" << LOG_END;
}

void GameLib::calculateMaxObjSpan()
{
    maxObjSpan_ = 0.0f;

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

    LOG_INFO << "maxObjSpan=" << maxObjSpan_ << LOG_END;
}

void GameLib::calculateMaxCollideBreath()
{
    maxCollideBreath_ = 0.0f;

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

