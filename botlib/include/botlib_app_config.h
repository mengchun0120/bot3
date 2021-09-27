#ifndef INCLUDED_BOTLIB_APP_CONFIG_H
#define INCLUDED_BOTLIB_APP_CONFIG_H

#include <string>
#include <memory>
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

    inline const std::string& simpleVertexShaderFile() const;

    inline const std::string& simpleFragShaderFile() const;

    inline const std::string& buttonConfigFile() const;

    inline const std::string& labelConfigFile() const;

    inline const std::string& messageBoxConfigFile() const;

    inline const std::string& startScreenConfigFile() const;

private:
    void loadBasics(const rapidjson::Document& doc);

    void loadDirectories(const rapidjson::Document& doc,
                         const std::string& appDir);

    void loadShaderFiles(const rapidjson::Document& doc);

    void loadConfigFiles(const rapidjson::Document& doc);

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
    std::string simpleVertexShaderFile_;
    std::string simpleFragShaderFile_;
    std::string buttonConfigFile_;
    std::string labelConfigFile_;
    std::string messageBoxConfigFile_;
    std::string startScreenConfigFile_;
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

const std::string& AppConfig::simpleVertexShaderFile() const
{
    return simpleVertexShaderFile_;
}

const std::string& AppConfig::simpleFragShaderFile() const
{
    return simpleFragShaderFile_;
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

} // end of namespace botlib
} // end of namespace mcdane

#endif

