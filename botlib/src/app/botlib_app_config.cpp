#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<AppConfig> AppConfig::k_instance;

void AppConfig::initInstance(const std::string& fileName,
                             const std::string& appDir)
{
    if (k_instance)
    {
        LOG_WARN << "AppConfig instance already initialized" << LOG_END;
        return;
    }

    k_instance.reset(new AppConfig(fileName, appDir));
}

AppConfig::AppConfig(const std::string& fileName,
                     const std::string& appDir)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    loadBasics(doc);
    loadDirectories(doc, appDir);
    loadShaderFiles(doc);
    loadConfigFiles(doc);
    loadLibFiles(doc);
    loadGameSettings(doc);

    LOG_INFO << "AppConfig initialized successfully" << LOG_END;
}

void AppConfig::loadBasics(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(width_, {"window", "width"}, true, gt(0u)),
        jsonParam(height_, {"window", "height"}, true, gt(0u)),
        jsonParam(title_, {"window", "title"}, true, k_nonEmptyStrV),
        jsonParam(inputQueueCapacity_, {"inputQueueCapacity"}, true, gt(0u))
    };

    parse(params, doc);
}


void AppConfig::loadDirectories(const rapidjson::Document& doc,
                                const std::string& appDir)
{
    std::vector<std::string> fontDir, picDir, glslDir, configDir, libDir;
    std::vector<JsonParamPtr> params{
        jsonParam(fontDir, {"directories", "fontDir"}, true, k_nonEmptyStrVecV),
        jsonParam(picDir, {"directories", "picDir"}, true, k_nonEmptyStrVecV),
        jsonParam(glslDir, {"directories", "glslDir"}, true, k_nonEmptyStrVecV),
        jsonParam(configDir, {"directories", "configDir"}, true, k_nonEmptyStrVecV),
        jsonParam(libDir, {"directories", "libDir"}, true, k_nonEmptyStrVecV)
    };

    parse(params, doc);

    fontDir_ = constructPath(appDir, fontDir);
    picDir_ = constructPath(appDir, picDir);
    glslDir_ = constructPath(appDir, glslDir);
    configDir_ = constructPath(appDir, configDir);
    libDir_ = constructPath(appDir, libDir);
}

void AppConfig::loadShaderFiles(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(simpleVertexShaderFile_, {"shaders", "simpleVertexShaderFile"},
                  true, k_nonEmptyStrV),
        jsonParam(simpleFragShaderFile_, {"shaders", "simpleFragShaderFile"},
                  true, k_nonEmptyStrV)
    };

    parse(params, doc);

    simpleVertexShaderFile_ = constructPath({glslDir_, simpleVertexShaderFile_});
    simpleFragShaderFile_ = constructPath({glslDir_, simpleFragShaderFile_});
}

void AppConfig::loadConfigFiles(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(buttonConfigFile_, {"configs", "buttonConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(labelConfigFile_, {"configs", "labelConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(messageBoxConfigFile_, {"configs", "messageBoxConfigFile"},
                  true, k_nonEmptyStrV),
        jsonParam(startScreenConfigFile_, {"configs", "startScreenConfigFile"},
                  true, k_nonEmptyStrV)
    };

    parse(params, doc);

    buttonConfigFile_ = constructPath({configDir_, buttonConfigFile_});
    labelConfigFile_ = constructPath({configDir_, labelConfigFile_});
    messageBoxConfigFile_ = constructPath({configDir_, messageBoxConfigFile_});
    startScreenConfigFile_ = constructPath({configDir_, startScreenConfigFile_});
}

void AppConfig::loadLibFiles(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(textureLibFile_, {"libraries", "textureLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(rectLibFile_, {"libraries", "rectLibFile"},
                  true, k_nonEmptyStrV),
        jsonParam(tileTemplateLibFile_, {"libraries", "tileTemplateLibFile"},
                  true, k_nonEmptyStrV)
    };

    parse(params, doc);

    textureLibFile_ = constructPath({libDir_, textureLibFile_});
    rectLibFile_ = constructPath({libDir_, rectLibFile_});
    tileTemplateLibFile_ = constructPath({libDir_, tileTemplateLibFile_});
}

void AppConfig::loadGameSettings(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(mapPoolSizeFactor_, {"game", "mapPoolSizeFactor"},
                  true, gt(0.0f))
    };

    parse(params, doc);
}

} // end of namespace botlib
} // end of namespace mcdane

