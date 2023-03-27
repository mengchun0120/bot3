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
    std::vector<std::string> toggleButtonFiles;
    float arrowWidth, arrowHeight;
    std::vector<JsonParamPtr> params{
        jsonParam(baseRadius_, "baseRadius", true, gt(0.0f)),
        jsonParam(toggleRadius_, "toggleRadius", true, gt(0.0f)),
        jsonParam(arrowRadius_, "arrowRadius", true, gt(0.0f)),
        jsonParam(alpha_, "alpha", true, ge(0.0f) && le(1.0f)),
        jsonParam(baseTextureFile, "baseTexture", true, k_nonEmptyStrV),
        jsonParam(toggleButtonFiles, "toggleButtons", true),
        jsonParam(arrowTextureFile, "arrowTexture", true, k_nonEmptyStrV),
        jsonParam(arrowWidth, "arrowWidth", true, gt(0.0f)),
        jsonParam(arrowHeight, "arrowHeight", true, gt(0.0f)),
    };

    parse(params, doc);

    initTexture(baseTextureFile, toggleButtonFiles, arrowTextureFile);
    initRect(arrowWidth, arrowHeight);

    LOG_INFO << "GameNavigatorConfig initialized" << LOG_END;
}

void GameNavigatorConfig::initTexture(
                    const std::string &baseTextureFile,
                    const std::vector<std::string> &toggleButtonFiles,
                    const std::string &arrowTextureFile)
{
    const std::string &picDir = AppConfig::instance().picDir();

    baseTexture_.init(constructPath({picDir, baseTextureFile}));

    toggleButtons_.resize(toggleButtonFiles.size());
    for (unsigned int i = 0; i < toggleButtonFiles.size(); ++i)
    {
        toggleButtons_[i].init(constructPath({picDir, toggleButtonFiles[i]}));
    }

    arrowTexture_.init(constructPath({picDir, arrowTextureFile}));
}

void GameNavigatorConfig::initRect(float arrowWidth, float arrowHeight)
{
    baseRect_.init(2.0f * baseRadius_, 2.0f * baseRadius_, TexRectangle());
    toggleRect_.init(2.0f * toggleRadius_, 2.0 * toggleRadius_, TexRectangle());
    arrowRect_.init(arrowWidth, arrowHeight, TexRectangle());
}

} // end of namespace botlib
} // end of namespace mcdane
