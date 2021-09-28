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
}

void AppConfig::loadBasics(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(width_, {"window", "width"}, true, gt(width_, 0u)),
        jsonParam(height_, {"window", "height"}, true, gt(height_, 0u)),
        jsonParam(title_, {"window", "title"}, true, nonempty(title_)),
        jsonParam(inputQueueCapacity_, {"inputQueueCapacity"}, true,
                  gt(inputQueueCapacity_, 0u))
    };

    parse(params, doc);
}


void AppConfig::loadDirectories(const rapidjson::Document& doc,
                                const std::string& appDir)
{
    std::vector<std::string> fontDir, picDir, glslDir, configDir;
    std::vector<JsonParamPtr> params{
        jsonParam(fontDir, {"directories", "fontDir"}, true, nonempty(fontDir)),
        jsonParam(picDir, {"directories", "picDir"}, true, nonempty(picDir)),
        jsonParam(glslDir, {"directories", "glslDir"}, true, nonempty(glslDir)),
        jsonParam(configDir, {"directories", "configDir"}, true,
                  nonempty(configDir)),
    };

    parse(params, doc);

    fontDir_ = constructPath(appDir, fontDir);
    picDir_ = constructPath(appDir, picDir);
    glslDir_ = constructPath(appDir, glslDir);
    configDir_ = constructPath(appDir, configDir);
}

void AppConfig::loadShaderFiles(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(simpleVertexShaderFile_, {"shaders", "simpleVertexShaderFile"},
                  true, nonempty(simpleVertexShaderFile_)),
        jsonParam(simpleFragShaderFile_, {"shaders", "simpleFragShaderFile"},
                  true, nonempty(simpleFragShaderFile_)
        )
    };

    parse(params, doc);

    simpleVertexShaderFile_ = constructPath({glslDir_, simpleVertexShaderFile_});
    simpleFragShaderFile_ = constructPath({glslDir_, simpleFragShaderFile_});
}

void AppConfig::loadConfigFiles(const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(buttonConfigFile_, {"configs", "buttonConfigFile"},
                  true, nonempty(buttonConfigFile_)),
        jsonParam(labelConfigFile_, {"configs", "labelConfigFile"},
                  true, nonempty(labelConfigFile_)),
        jsonParam(messageBoxConfigFile_, {"configs", "messageBoxConfigFile"},
                  true, nonempty(messageBoxConfigFile_)),
        jsonParam(startScreenConfigFile_, {"configs", "startScreenConfigFile"},
                  true, nonempty(startScreenConfigFile_))
    };

    parse(params, doc);

    buttonConfigFile_ = constructPath({configDir_, buttonConfigFile_});
    labelConfigFile_ = constructPath({configDir_, labelConfigFile_});
    messageBoxConfigFile_ = constructPath({configDir_, messageBoxConfigFile_});
    startScreenConfigFile_ = constructPath({configDir_, startScreenConfigFile_});
}

} // end of namespace botlib
} // end of namespace mcdane

