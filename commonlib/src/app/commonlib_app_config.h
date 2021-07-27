#ifndef INCLUDED_COMMONLIB_APP_CONFIG_H
#define INCLUDED_COMMONLIB_APP_CONFIG_H

#include <string>
#include <memory>

namespace mcdane {
namespace commonlib {

class AppConfig {
public:
    static void initInstance(const std::string& fileName);

    static const AppConfig& getInstance()
    {
        return *k_config;
    }

    ~AppConfig();

    const std::string& logFile() const
    {
        return logFile_;
    }

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

private:
    AppConfig(const std::string& fileName);

    void load(const std::string& fileName);

private:
    static std::shared_ptr<AppConfig> k_config;

    std::string logFile_;
    unsigned int width_;
    unsigned int height_;
    std::string title_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

