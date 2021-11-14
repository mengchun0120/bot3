#include <commonlib_log.h>
#include <botlib_lib_parser.h>
#include <botlib_game_lib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<GameLib> GameLib::k_gameLib;

void GameLib::initInstance(const std::string& textureLibFile,
                           const std::string& rectLibFile,
                           const std::string& tileTemplateLibFile,
                           const std::string& picDir)
{
    GameLib* lib = new GameLib();
    lib->load(textureLibFile, rectLibFile, tileTemplateLibFile, picDir);
    k_gameLib.reset(lib);
}

void GameLib::load(const std::string& textureLibFile,
                   const std::string& rectLibFile,
                   const std::string& tileTemplateLibFile,
                   const std::string& picDir)
{
    TextureLibParser textureLibParser(picDir);
    textureLib_.load(textureLibFile, textureLibParser);

    RectLibParser rectLibParser;
    rectLib_.load(rectLibFile, rectLibParser);

    TileTemplateLibParser tileTemplateParser(textureLib_, rectLib_);
    tileTemplateLib_.load(tileTemplateLibFile, tileTemplateParser);

    LOG_INFO << "GameLib loaded successfull" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

