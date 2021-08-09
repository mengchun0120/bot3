#ifndef INCLUDED_COMMONLIB_APP_CONFIG_H
#define INCLUDED_COMMONLIB_APP_CONFIG_H

#include <string>
#include <memory>

namespace mcdane {
namespace commonlib {

class AppConfig {
public:
    AppConfig() = default;

    ~AppConfig() = default;

    void load(const std::string& fileName);

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
private:
    std::string logFile_;
    unsigned int width_;
    unsigned int height_;
    std::string title_;
    unsigned int inputQueueCapacity_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

