#ifndef INCLUDED_BOTLIB_APP_CONFIG_H
#define INCLUDED_BOTLIB_APP_CONFIG_H

#include <string>
#include <memory>
#include <vector>
#include <rapidjson/document.h>

#ifdef __ANDROID__
#include <android/asset_manager.h>
#endif

namespace mcdane {
namespace botlib {

class AppConfig {
public:
    inline static const AppConfig &instance();

    static void init(const std::string &path,
                     const std::string &appDir="");

    AppConfig(const rapidjson::Document &doc,
              const std::string &appDir="");

    ~AppConfig() = default;

    inline unsigned int width() const;

    inline unsigned int height() const;

    inline const std::string &title() const;

    inline unsigned int inputQueueCapacity() const;

    inline const std::string &fontDir() const;

    inline const std::string &picDir() const;

    inline const std::string &glslDir() const;

    inline const std::string &configDir() const;

    inline const std::string &libDir() const;

    inline const std::string &mapDir() const;

    inline const std::vector<std::string> &simpleVertexShaderFiles() const;

    inline const std::vector<std::string> &simpleFragShaderFiles() const;

    inline const std::vector<std::string> &particleVertexShaderFiles() const;

    inline const std::vector<std::string> &particleFragShaderFiles() const;

    inline const std::string &buttonConfigFile() const;

    inline const std::string &labelConfigFile() const;

    inline const std::string &messageBoxConfigFile() const;

    inline const std::string &startScreenConfigFile() const;

    inline const std::string &gameScreenConfigFile() const;

    inline const std::string &showMapScreenConfigFile() const;

    inline const std::string &gameConfigFile() const;

    inline const std::string &hpIndicatorConfigFile() const;

    inline const std::string &textureLibFile() const;

    inline const std::string &vertexArrayLibFile() const;

    inline const std::string &vertexArrayDataDir() const;

    inline const std::string &rectLibFile() const;

    inline const std::string &componentTemplateLibFile() const;

    inline const std::string &tileTemplateLibFile() const;

    inline const std::string &missileTemplateLibFile() const;

    inline const std::string &skillTemplateLibFile() const;

    inline const std::string &skillDataDir() const;

    inline const std::string &goodieTemplateLibFile() const;

    inline const std::string &aiRobotTemplateLibFile() const;

    inline const std::string &particleEffectTemplateLibFile() const;

    inline const std::string &particleEffectDataDir() const;

    inline const std::string &chaseShootAIParamLibFile() const;

    inline const std::string &progressPieTemplateLibFile() const;

    inline const std::string &progressBarTemplateLibFile() const;

    inline const std::string &iconTemplateLibFile() const;

    inline const std::string &playerTemplateFile() const;

    inline float mapPoolSizeFactor() const;

    inline unsigned int timeDeltaHistoryLen() const;

private:
    void loadBasics(const rapidjson::Document &doc);

    void loadDirectories(const rapidjson::Document &doc,
                         const std::string &appDir);

    void loadShaderFiles(const rapidjson::Document &doc);

    void loadConfigFiles(const rapidjson::Document &doc);

    void loadLibFiles(const rapidjson::Document &doc);

    void loadGameSettings(const rapidjson::Document &doc);

private:
    static std::shared_ptr<AppConfig> k_instance;

    std::string logFile_;
    unsigned int width_;
    unsigned int height_;
    std::string title_;
    unsigned int inputQueueCapacity_;
    std::string fontDir_;
    std::string picDir_;
    std::string glslDir_;
    std::string configDir_;
    std::string libDir_;
    std::string mapDir_;
    std::vector<std::string> simpleVertexShaderFiles_;
    std::vector<std::string> simpleFragShaderFiles_;
    std::vector<std::string> particleVertexShaderFiles_;
    std::vector<std::string> particleFragShaderFiles_;
    std::string buttonConfigFile_;
    std::string labelConfigFile_;
    std::string messageBoxConfigFile_;
    std::string startScreenConfigFile_;
    std::string gameScreenConfigFile_;
    std::string showMapScreenConfigFile_;
    std::string gameConfigFile_;
    std::string hpIndicatorConfigFile_;
    std::string textureLibFile_;
    std::string vertexArrayLibFile_;
    std::string vertexArrayDataDir_;
    std::string rectLibFile_;
    std::string componentTemplateLibFile_;
    std::string tileTemplateLibFile_;
    std::string missileTemplateLibFile_;
    std::string skillTemplateLibFile_;
    std::string skillDataDir_;
    std::string goodieTemplateLibFile_;
    std::string aiRobotTemplateLibFile_;
    std::string particleEffectTemplateLibFile_;
    std::string particleEffectDataDir_;
    std::string chaseShootAIParamLibFile_;
    std::string progressPieTemplateLibFile_;
    std::string progressBarTemplateLibFile_;
    std::string iconTemplateLibFile_;
    std::string playerTemplateFile_;
    float mapPoolSizeFactor_;
    unsigned int timeDeltaHistoryLen_;
};

const AppConfig & AppConfig::instance()
{
    return *k_instance;
}

unsigned int AppConfig::width() const
{
    return width_;
}

unsigned int AppConfig::height() const
{
    return height_;
}

const std::string & AppConfig::title() const
{
    return title_;
}

unsigned int AppConfig::inputQueueCapacity() const
{
    return inputQueueCapacity_;
}

const std::string & AppConfig::fontDir() const
{
    return fontDir_;
}

const std::string & AppConfig::picDir() const
{
    return picDir_;
}

const std::string & AppConfig::glslDir() const
{
    return glslDir_;
}

const std::string & AppConfig::configDir() const
{
    return configDir_;
}

const std::string & AppConfig::libDir() const
{
    return libDir_;
}

const std::string & AppConfig::mapDir() const
{
    return mapDir_;
}

const std::vector<std::string> & AppConfig::simpleVertexShaderFiles() const
{
    return simpleVertexShaderFiles_;
}

const std::vector<std::string> & AppConfig::simpleFragShaderFiles() const
{
    return simpleFragShaderFiles_;
}

const std::vector<std::string> & AppConfig::particleVertexShaderFiles() const
{
    return particleVertexShaderFiles_;
}

const std::vector<std::string> &AppConfig::particleFragShaderFiles() const
{
    return particleFragShaderFiles_;
}

const std::string & AppConfig::buttonConfigFile() const
{
    return buttonConfigFile_;
}

const std::string & AppConfig::labelConfigFile() const
{
    return labelConfigFile_;
}

const std::string & AppConfig::messageBoxConfigFile() const
{
    return messageBoxConfigFile_;
}

const std::string & AppConfig::startScreenConfigFile() const
{
    return startScreenConfigFile_;
}

const std::string & AppConfig::gameScreenConfigFile() const
{
    return gameScreenConfigFile_;
}

const std::string & AppConfig::showMapScreenConfigFile() const
{
    return showMapScreenConfigFile_;
}

const std::string & AppConfig::gameConfigFile() const
{
    return gameConfigFile_;
}

const std::string & AppConfig::hpIndicatorConfigFile() const
{
    return hpIndicatorConfigFile_;
}

const std::string & AppConfig::textureLibFile() const
{
    return textureLibFile_;
}

const std::string & AppConfig::vertexArrayLibFile() const
{
    return vertexArrayLibFile_;
}

const std::string & AppConfig::vertexArrayDataDir() const
{
    return vertexArrayDataDir_;
}

const std::string & AppConfig::rectLibFile() const
{
    return rectLibFile_;
}

const std::string & AppConfig::componentTemplateLibFile() const
{
    return componentTemplateLibFile_;
}

const std::string & AppConfig::tileTemplateLibFile() const
{
    return tileTemplateLibFile_;
}

const std::string & AppConfig::missileTemplateLibFile() const
{
    return missileTemplateLibFile_;
}

const std::string & AppConfig::skillTemplateLibFile() const
{
    return skillTemplateLibFile_;
}

const std::string & AppConfig::skillDataDir() const
{
    return skillDataDir_;
}

const std::string & AppConfig::goodieTemplateLibFile() const
{
    return goodieTemplateLibFile_;
}

const std::string & AppConfig::aiRobotTemplateLibFile() const
{
    return aiRobotTemplateLibFile_;
}

const std::string & AppConfig::particleEffectTemplateLibFile() const
{
    return particleEffectTemplateLibFile_;
}

const std::string & AppConfig::particleEffectDataDir() const
{
    return particleEffectDataDir_;
}

const std::string & AppConfig::chaseShootAIParamLibFile() const
{
    return chaseShootAIParamLibFile_;
}

const std::string & AppConfig::progressPieTemplateLibFile() const
{
    return progressPieTemplateLibFile_;
}

const std::string & AppConfig::progressBarTemplateLibFile() const
{
    return progressBarTemplateLibFile_;
}

const std::string & AppConfig::iconTemplateLibFile() const
{
    return iconTemplateLibFile_;
}

const std::string & AppConfig::playerTemplateFile() const
{
    return playerTemplateFile_;
}

float AppConfig::mapPoolSizeFactor() const
{
    return mapPoolSizeFactor_;
}

unsigned int AppConfig::timeDeltaHistoryLen() const
{
    return timeDeltaHistoryLen_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
