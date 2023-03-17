#ifndef INCLUDED_BOTLIB_BUTTON_CONFIG_H
#define INCLUDED_BOTLIB_BUTTON_CONFIG_H

#include <string>
#include <vector>
#include <commonlib_color.h>
#include <commonlib_texture.h>
#include <botlib_button.h>

namespace mcdane {
namespace botlib {

class ButtonConfig {
public:
    ButtonConfig() = default;

    ~ButtonConfig() = default;

    void init(const std::string &configFile,
              const std::string &picDir);

    inline const commonlib::Color *textColor(Button::State s) const;

    inline const commonlib::Texture &texture() const;

private:
    void validateTextColor();

private:
    std::vector<commonlib::Color> textColors_;
    commonlib::Texture texture_;
};

const commonlib::Color *ButtonConfig::textColor(Button::State s) const
{
    return &textColors_[s];
}

const commonlib::Texture &ButtonConfig::texture() const
{
    return texture_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

