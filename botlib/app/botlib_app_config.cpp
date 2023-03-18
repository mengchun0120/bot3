#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void marshalFileNames(std::vector<std::string> &newFileNames,
                      const std::vector<std::string> &oldFileNames,
                      const std::string &folder)
{
    newFileNames.resize(oldFileNames.size());
    for (std::size_t i = 0; i < newFileNames.size(); ++i)
    {
        newFileNames[i] = constructPath({folder, oldFileNames[i]});
    }
}

std::shared_ptr<AppConfig> AppConfig::k_instance;

void AppConfig::init(const std::string &path,
                     const std::string &appDir)
{
    if (k_instance)
    {
        LOG_WARN << "AppConfig instance already initialized" << LOG_END;
        return;
    }

    rapidjson::Document doc;
    std::string docPath = constructPath({appDir, path});

    readJson(doc, docPath);

    k_instance.reset(new AppConfig(doc, appDir));
}

AppConfig::AppConfig(const rapidjson::Document &doc,
                     const std::string &appDir)
{
    loadBasics(doc);
    loadDirectories(doc, appDir);
    loadShaderFiles(doc);
    loadConfigFiles(doc);
    loadLibFiles(doc);
    loadGameSettings(doc);

    LOG_INFO << "AppConfig initialized successfully" << LOG_END;
}

void AppConfig::loadBasics(const rapidjson::Document &doc)
{
    std::vector<JsonParamPtr> params{
#ifdef DESKTOP_APP
        jsonParam(width_, {"window", "width"}, true, gt(0u)),
        jsonParam(height_, {"window", "height"}, true, gt(0u)),
        jsonParam(title_, {"window", "title"}, true, k_nonEmptyStrV),
#endif
        jsonParam(inputQueueCapacity_, {"inputQueueCapacity"}, true, gt(0u)),
    };

    parse(params, doc);
}

void AppConfig::loadDirectories(const rapidjson::Document &doc,
                                const std::string &appDir)
{
    std::vector<std::string> fontDir, picDir, glslDir, configDir, libDir, mapDir;
    std::vector<JsonParamPtr> params{
        jsonParam(fontDir, {"directories", "fontDir"}, true, k_nonEmptyStrVecV),
        jsonParam(picDir, {"directories", "picDir"}, true, k_nonEmptyStrVecV),
        jsonParam(glslDir, {"directories", "glslDir"}, true, k_nonEmptyStrVecV),
        jsonParam(configDir, {"directories", "configDir"}, true, k_nonEmptyStrVecV),
        jsonParam(libDir, {"directories", "libDir"}, true, k_nonEmptyStrVecV),
        jsonParam(mapDir, {"directories", "mapDir"}, true, k_nonEmptyStrVecV)
    };

    parse(params, doc);

    fontDir_ = constructPath(appDir, fontDir);
    picDir_ = constructPath(appDir, picDir);
    glslDir_ = constructPath(appDir, glslDir);
    configDir_ = constructPath(appDir, configDir);
    libDir_ = constructPath(appDir, libDir);
    mapDir_ = constructPath(appDir, mapDir);
}

void AppConfig::loadShaderFiles(const rapidjson::Document &doc)
{
    std::vector<std::string> simpleVertexShaderFiles1;
    std::vector<std::string> simpleFragShaderFiles1;
    std::vector<std::string> particleVertexShaderFiles1;
    std::vector<std::string> particleFragShaderFiles1;

    std::vector<JsonParamPtr> params{
        jsonParam(simpleVertexShaderFiles1,
                  {"shaders", "simpleVertexShaderFiles"},
                  true, k_nonEmptyStrVecV),
        jsonParam(simpleFragShaderFiles1,
                  {"shaders", "simpleFragShaderFiles"},
                  true, k_nonEmptyStrVecV),
        jsonParam(particleVertexShaderFiles1,
                  {"shaders", "particleVertexShaderFiles"},
                  true, k_nonEmptyStrVecV),
        jsonParam(particleFragShaderFiles1,
                  {"shaders", "particleFragShaderFiles"},
                  true, k_nonEmptyStrVecV)
    };

    parse(params, doc);

    marshalFileNames(simpleVertexShaderFiles_,
                     simpleVertexShaderFiles1,
                     glslDir_);
    marshalFileNames(simpleFragShaderFiles_,
                     simpleFragShaderFiles1,
                     glslDir_);
    marshalFileNames(particleVertexShaderFiles_,
                     particleVertexShaderFiles1,
                     glslDir_);
    marshalFileNames(particleFragShaderFiles_,
                     particleFragShaderFiles1,
                     glslDir_);
}

void AppConfig::loadConfigFiles(const rapidjson::Document &doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(buttonConfigFile_, {"configs", "buttonConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(labelConfigFile_, {"configs", "labelConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(messageBoxConfigFile_, {"configs", "messageBoxConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(mapNavigatorConfigFile_, {"configs", "mapNavigatorConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(startScreenConfigFile_, {"configs", "startScreenConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(gameScreenConfigFile_, {"configs", "gameScreenConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(showMapScreenConfigFile_, {"configs", "showMapScreenConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(gameConfigFile_, {"configs", "gameConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(hpIndicatorConfigFile_, {"configs", "hpIndicatorConfigFile"},
                  true, k_nonEmptyStrV)
    };

    parse(params, doc);

    buttonConfigFile_ = constructPath({configDir_, buttonConfigFile_});
    labelConfigFile_ = constructPath({configDir_, labelConfigFile_});
    messageBoxConfigFile_ = constructPath({configDir_, messageBoxConfigFile_});
    mapNavigatorConfigFile_ = constructPath({configDir_, mapNavigatorConfigFile_});
    startScreenConfigFile_ = constructPath({configDir_, startScreenConfigFile_});
    gameScreenConfigFile_ = constructPath({configDir_, gameScreenConfigFile_});
    showMapScreenConfigFile_ = constructPath({configDir_, showMapScreenConfigFile_});
    gameConfigFile_ = constructPath({configDir_, gameConfigFile_});
    hpIndicatorConfigFile_ = constructPath({configDir_, hpIndicatorConfigFile_});
}

void AppConfig::loadLibFiles(const rapidjson::Document &doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(textureLibFile_, {"libraries", "textureLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(vertexArrayLibFile_, {"libraries", "vertexArrayLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(vertexArrayDataDir_, {"libraries", "vertexArrayDataDir"},
                  true, k_nonEmptyStrV),
        jsonParam(rectLibFile_, {"libraries", "rectLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(componentTemplateLibFile_,
                  {"libraries", "componentTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(tileTemplateLibFile_, {"libraries", "tileTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(missileTemplateLibFile_, {"libraries", "missileTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(skillTemplateLibFile_, {"libraries", "skillTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(skillDataDir_, {"libraries", "skillDataDir"},
                  true, k_nonEmptyStrV),
        jsonParam(goodieTemplateLibFile_, {"libraries", "goodieTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(aiRobotTemplateLibFile_, {"libraries", "aiRobotTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(particleEffectTemplateLibFile_,
                  {"libraries", "particleEffectTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(particleEffectDataDir_, {"libraries", "particleEffectDataDir"},
                  true, k_nonEmptyStrV),
        jsonParam(chaseShootAIParamLibFile_,
                  {"libraries", "chaseShootAIParamLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(progressPieTemplateLibFile_,
                  {"libraries", "progressPieTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(progressBarTemplateLibFile_,
                  {"libraries", "progressBarTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(iconTemplateLibFile_, {"libraries", "iconTemplateLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(playerTemplateFile_, {"libraries", "playerTemplateFile"},
                  true, k_nonEmptyStrV)
    };

    parse(params, doc);

    textureLibFile_ = constructPath({libDir_, textureLibFile_});
    vertexArrayLibFile_ = constructPath({libDir_, vertexArrayLibFile_});
    vertexArrayDataDir_ = constructPath({libDir_, vertexArrayDataDir_});
    rectLibFile_ = constructPath({libDir_, rectLibFile_});
    componentTemplateLibFile_ = constructPath({libDir_, componentTemplateLibFile_});
    tileTemplateLibFile_ = constructPath({libDir_, tileTemplateLibFile_});
    missileTemplateLibFile_ = constructPath({libDir_, missileTemplateLibFile_});
    skillTemplateLibFile_ = constructPath({libDir_, skillTemplateLibFile_});
    skillDataDir_ = constructPath({libDir_, skillDataDir_});
    goodieTemplateLibFile_ = constructPath({libDir_, goodieTemplateLibFile_});
    aiRobotTemplateLibFile_ = constructPath({libDir_, aiRobotTemplateLibFile_});
    particleEffectTemplateLibFile_ = constructPath(
                                     {libDir_, particleEffectTemplateLibFile_});
    particleEffectDataDir_ = constructPath({libDir_, particleEffectDataDir_});
    chaseShootAIParamLibFile_ = constructPath({libDir_, chaseShootAIParamLibFile_});
    progressPieTemplateLibFile_ = constructPath(
                                    {libDir_, progressPieTemplateLibFile_});
    progressBarTemplateLibFile_ = constructPath(
                                    {libDir_, progressBarTemplateLibFile_});
    iconTemplateLibFile_ = constructPath({libDir_, iconTemplateLibFile_});
    playerTemplateFile_ = constructPath({libDir_, playerTemplateFile_});
}

void AppConfig::loadGameSettings(const rapidjson::Document &doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(mapPoolSizeFactor_, {"game", "mapPoolSizeFactor"},
                  true, gt(0.0f)),
        jsonParam(timeDeltaHistoryLen_, {"game", "timeDeltaHistoryLen"},
                  true, gt(0u))
    };

    parse(params, doc);
}

} // end of namespace botlib
} // end of namespace mcdane
