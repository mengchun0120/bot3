#ifndef INCLUDED_BOTLIB_APP_CONFIG_H
#define INCLUDED_BOTLIB_APP_CONFIG_H

#include <string>
#include <memory>

namespace mcdane {
namespace botlib {

class AppConfig {
public:
    AppConfig() = default;

    ~AppConfig() = default;

    void load(const std::string& fileName,
              const std::string& appDir);

    unsigned int width() const
    {
        return width_;
    }

    unsigned int height() const
    {
        return height_;
    }

    const std::string& title() const
    {
        return title_;
    }

    unsigned int inputQueueCapacity() const
    {
        return inputQueueCapacity_;
    }

    const std::string& simpleVertexShaderFile() const
    {
        return simpleVertexShaderFile_;
    }

    const std::string& simpleFragShaderFile() const
    {
        return simpleFragShaderFile_;
    }

private:
    void completeFilePath(const std::string& appDir);

private:
    std::string logFile_;
    unsigned int width_;
    unsigned int height_;
    std::string title_;
    unsigned int inputQueueCapacity_;
    std::string simpleVertexShaderFile_;
    std::string simpleFragShaderFile_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

