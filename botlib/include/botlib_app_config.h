#ifndef INCLUDED_BOTLIB_APP_CONFIG_H
#define INCLUDED_BOTLIB_APP_CONFIG_H

#include <string>
#include <memory>
#include <vector>
#include <rapidjson/document.h>

namespace mcdane {
namespace botlib {

class AppConfig {
public:
    inline static const AppConfig& getInstance();

    static void initInstance(const std::string& fileName,
                             const std::string& appDir);

    ~AppConfig() = default;

    void load();

    inline unsigned int width() const;

    inline unsigned int height() const;

    inline const std::string& title() const;

    inline unsigned int inputQueueCapacity() const;

    inline const std::string& fontDir() const;

    inline const std::string& picDir() const;

    inline const std::string& glslDir() const;

    inline const std::string& configDir() const;

    inline const std::string& libDir() const;

    inline const std::vector<std::string>& simpleVertexShaderFiles() const;

    inline const std::vector<std::string>& simpleFragShaderFiles() const;

    inline const std::vector<std::string>& particleVertexShaderFiles() const;

    inline const std::vector<std::string>& particleFragShaderFiles() const;

    inline const std::string& buttonConfigFile() const;

    inline const std::string& labelConfigFile() const;

    inline const std::string& messageBoxConfigFile() const;

    inline const std::string& startScreenConfigFile() const;

    inline const std::string& hpIndicatorConfigFile() const;

    inline const std::string& textureLibFile() const;

    inline const std::string& rectLibFile() const;

    inline const std::string& componentTemplateLibFile() const;

    inline const std::string& tileTemplateLibFile() const;

    inline const std::string& missileTemplateLibFile() const;

    inline const std::string& aiRobotTemplateLibFile() const;

    inline float mapPoolSizeFactor() const;

    inline unsigned int timeDeltaHistoryLen() const;

private:
    void loadBasics(const rapidjson::Document& doc);

    void loadDirectories(const rapidjson::Document& doc,
                         const std::string& appDir);

    void loadShaderFiles(const rapidjson::Document& doc);

    void loadConfigFiles(const rapidjson::Document& doc);

    void loadLibFiles(const rapidjson::Document& doc);

    void loadGameSettings(const rapidjson::Document& doc);

private:
    AppConfig(const std::string& fileName,
              const std::string& appDir);

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
    std::vector<std::string> simpleVertexShaderFiles_;
    std::vector<std::string> simpleFragShaderFiles_;
    std::vector<std::string> particleVertexShaderFiles_;
    std::vector<std::string> particleFragShaderFiles_;
    std::string buttonConfigFile_;
    std::string labelConfigFile_;
    std::string messageBoxConfigFile_;
    std::string startScreenConfigFile_;
    std::string hpIndicatorConfigFile_;
    std::string textureLibFile_;
    std::string rectLibFile_;
    std::string componentTemplateLibFile_;
    std::string tileTemplateLibFile_;
    std::string missileTemplateLibFile_;
    std::string aiRobotTemplateLibFile_;
    float mapPoolSizeFactor_;
    unsigned int timeDeltaHistoryLen_;
};

const AppConfig& AppConfig::getInstance()
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

const std::string& AppConfig::title() const
{
    return title_;
}

unsigned int AppConfig::inputQueueCapacity() const
{
    return inputQueueCapacity_;
}

const std::string& AppConfig::fontDir() const
{
    return fontDir_;
}

const std::string& AppConfig::picDir() const
{
    return picDir_;
}

const std::string& AppConfig::glslDir() const
{
    return glslDir_;
}

const std::string& AppConfig::configDir() const
{
    return configDir_;
}

const std::string& AppConfig::libDir() const
{
    return libDir_;
}

const std::vector<std::string>& AppConfig::simpleVertexShaderFiles() const
{
    return simpleVertexShaderFiles_;
}

const std::vector<std::string>& AppConfig::simpleFragShaderFiles() const
{
    return simpleFragShaderFiles_;
}

const std::vector<std::string>& AppConfig::particleVertexShaderFiles() const
{
    return particleVertexShaderFiles_;
}

const std::vector<std::string>& AppConfig::particleFragShaderFiles() const
{
    return particleFragShaderFiles_;
}

const std::string& AppConfig::buttonConfigFile() const
{
    return buttonConfigFile_;
}

const std::string& AppConfig::labelConfigFile() const
{
    return labelConfigFile_;
}

const std::string& AppConfig::messageBoxConfigFile() const
{
    return messageBoxConfigFile_;
}

const std::string& AppConfig::startScreenConfigFile() const
{
    return startScreenConfigFile_;
}

const std::string& AppConfig::hpIndicatorConfigFile() const
{
    return hpIndicatorConfigFile_;
}

const std::string& AppConfig::textureLibFile() const
{
    return textureLibFile_;
}

const std::string& AppConfig::rectLibFile() const
{
    return rectLibFile_;
}

const std::string& AppConfig::componentTemplateLibFile() const
{
    return componentTemplateLibFile_;
}

const std::string& AppConfig::tileTemplateLibFile() const
{
    return tileTemplateLibFile_;
}

const std::string& AppConfig::missileTemplateLibFile() const
{
    return missileTemplateLibFile_;
}

const std::string& AppConfig::aiRobotTemplateLibFile() const
{
    return aiRobotTemplateLibFile_;
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

