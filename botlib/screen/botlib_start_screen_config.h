#ifndef INCLUDED_BOTLIB_START_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_START_SCREEN_CONFIG_H

#include <string>

namespace mcdane {
namespace botlib {

class StartScreenConfig {
public:
    StartScreenConfig() = default;

    ~StartScreenConfig() = default;

    void init(const std::string& configFile);

    inline float buttonWidth() const;

    inline float buttonHeight() const;

    inline float buttonSpacing() const;

private:
    float buttonWidth_;
    float buttonHeight_;
    float buttonSpacing_;
};

float StartScreenConfig::buttonWidth() const
{
    return buttonWidth_;
}

float StartScreenConfig::buttonHeight() const
{
    return buttonHeight_;
}

float StartScreenConfig::buttonSpacing() const
{
    return buttonSpacing_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

