#ifndef INCLUDED_BOTLIB_APP_CONFIG_H
#define INCLUDED_BOTLIB_APP_CONFIG_H

#include <string>

namespace mcdane {
namespace botlib {

class AppConfig {
public:
    AppConfig() = default;

    ~AppConfig() = default;

    void load(const std::string& fileName,
              const std::string& appDir);

    inline unsigned int width() const;

    inline unsigned int height() const;

    inline const std::string& title() const;

    inline unsigned int inputQueueCapacity() const;

    inline const std::string& simpleVertexShaderFile() const;

    inline const std::string& simpleFragShaderFile() const;

    inline const std::string& fontDir() const;

    inline const std::string& picDir() const;

    inline const std::string& buttonConfigFile() const;

private:
    std::string logFile_;
    unsigned int width_;
    unsigned int height_;
    std::string title_;
    unsigned int inputQueueCapacity_;
    std::string simpleVertexShaderFile_;
    std::string simpleFragShaderFile_;
    std::string fontDir_;
    std::string picDir_;
    std::string buttonConfigFile_;
};

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

const std::string& AppConfig::simpleVertexShaderFile() const
{
    return simpleVertexShaderFile_;
}

const std::string& AppConfig::simpleFragShaderFile() const
{
    return simpleFragShaderFile_;
}

const std::string& AppConfig::fontDir() const
{
    return fontDir_;
}

const std::string& AppConfig::picDir() const
{
    return picDir_;
}

const std::string& AppConfig::buttonConfigFile() const
{
    return buttonConfigFile_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

