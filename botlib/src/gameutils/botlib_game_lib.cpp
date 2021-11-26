#include <commonlib_log.h>
#include <botlib_lib_parser.h>
#include <botlib_game_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<GameLib> GameLib::k_gameLib;

void GameLib::initInstance(const std::string& textureLibFile,
                           const std::string& rectLibFile,
                           const std::string& componentTemplateLibFile,
                           const std::string& tileTemplateLibFile,
                           const std::string& picDir)
{
    GameLib* lib = new GameLib();
    lib->load(textureLibFile, rectLibFile, componentTemplateLibFile,
              tileTemplateLibFile, picDir);
    k_gameLib.reset(lib);
}

void GameLib::load(const std::string& textureLibFile,
                   const std::string& rectLibFile,
                   const std::string& componentTemplateLibFile,
                   const std::string& tileTemplateLibFile,
                   const std::string& picDir)
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

    calculateMaxObjSpan();

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

    LOG_INFO << "maxObjSpan=" << maxObjSpan_ << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

