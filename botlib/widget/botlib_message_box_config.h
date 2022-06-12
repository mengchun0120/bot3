#ifndef INCLUDED_BOTLIB_MESSAGE_BOX_CONFIG_H
#define INCLUDED_BOTLIB_MESSAGE_BOX_CONFIG_H

#include <string>
#include <commonlib_color.h>

namespace mcdane {
namespace botlib {

class MessageBoxConfig {
public:
    MessageBoxConfig() = default;

    ~MessageBoxConfig() = default;

    void init(const std::string& configFile);

    inline float messageMarginX() const;

    inline float messageMarginY() const;

    inline float messageHeight() const;

    inline float buttonMarginY() const;

    inline float buttonSpacing() const;

    inline float buttonWidth() const;

    inline float buttonHeight() const;

    inline const commonlib::Color& messageBorderColor() const;

private:
    float messageMarginX_;
    float messageMarginY_;
    float messageHeight_;
    float buttonMarginY_;
    float buttonSpacing_;
    float buttonWidth_;
    float buttonHeight_;
    commonlib::Color messageBorderColor_;
};

float MessageBoxConfig::messageMarginX() const
{
    return messageMarginX_;
}

float MessageBoxConfig::messageMarginY() const
{
    return messageMarginY_;
}

float MessageBoxConfig::messageHeight() const
{
    return messageHeight_;
}

float MessageBoxConfig::buttonMarginY() const
{
    return buttonMarginY_;
}

float MessageBoxConfig::buttonSpacing() const
{
    return buttonSpacing_;
}

float MessageBoxConfig::buttonWidth() const
{
    return buttonWidth_;
}

float MessageBoxConfig::buttonHeight() const
{
    return buttonHeight_;
}

const commonlib::Color& MessageBoxConfig::messageBorderColor() const
{
    return messageBorderColor_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

