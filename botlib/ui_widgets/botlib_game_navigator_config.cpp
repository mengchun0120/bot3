#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_app_config.h>
#include <botlib_game_navigator_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameNavigatorConfig::init(const std::string &fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::string baseTextureFile, arrowTextureFile;
    float baseWidth, baseHeight, arrowWidth, arrowHeight;
    std::vector<JsonParamPtr> params{
        jsonParam(baseRadius_, "baseRadius", true, gt(0.0f)),
        jsonParam(toggleRadius_, "toggleRadius", true, gt(0.0f)),
        jsonParam(arrowRadius_, "arrowRadius", true, gt(0.0f)),
        jsonParam(alpha_, "alpha", true, ge(0.0f) && le(1.0f)),
        jsonParam(baseTextureFile, "baseTexture", true, k_nonEmptyStrV),
        jsonParam(arrowTextureFile, "arrowTexture", true, k_nonEmptyStrV),
        jsonParam(baseWidth, "baseWidth", true, gt(0.0f)),
        jsonParam(baseHeight, "baseHeight", true, gt(0.0f)),
        jsonParam(arrowWidth, "arrowWidth", true, gt(0.0f)),
        jsonParam(arrowHeight, "arrowHeight", true, gt(0.0f)),
    };

    parse(params, doc);

    initTexture(baseTextureFile, arrowTextureFile);
    initRect(baseWidth, baseHeight, arrowWidth, arrowHeight);

    LOG_INFO << "GameNavigatorConfig initialized" << LOG_END;
}

void GameNavigatorConfig::initTexture(const std::string &baseTextureFile,
                                      const std::string &arrowTextureFile)
{
    const std::string &picDir = AppConfig::instance().picDir();
    baseTexture_.init(constructPath({picDir, baseTextureFile}));
    arrowTexture_.init(constructPath({picDir, arrowTextureFile}));
}

void GameNavigatorConfig::initRect(float baseWidth, float baseHeight,
                                   float arrowWidth, float arrowHeight)
{
    baseRect_.init(baseWidth, baseHeight, TexRectangle());
    arrowRect_.init(arrowWidth, arrowHeight, TexRectangle());
}

} // end of namespace botlib
} // end of namespace mcdane
