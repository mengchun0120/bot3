#ifndef INCLUDED_BOTLIB_TEXT_BOX_CONFIG_H
#define INCLUDED_BOTLIB_TEXT_BOX_CONFIG_H

#include <string>
#include <commonlib_color.h>
#include <botlib_text_size.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class TextSystem;

class TextBoxConfig {
public:
    TextBoxConfig() = default;

    void init(const std::string &fileName,
              const TextSystem &textSys);

    inline float blinkTime() const;

    inline TextSize textSize() const;

    inline float textHeight() const;

    inline const commonlib::Color &borderColor() const;

    inline const commonlib::Color &backColor() const;

    inline const commonlib::Color &textColor() const;

    inline float caretWidth() const;

    inline float caretHeight() const;

    inline const Rectangle &caretRect() const;

    inline const commonlib::Color &caretColor() const;

    inline float leftMargin() const;

    inline float topMargin() const;

    inline float minWidth() const;

    inline float minHeight() const;

private:
    float blinkTime_;
    TextSize textSize_;
    float textHeight_;
    commonlib::Color borderColor_, backColor_, textColor_;
    float caretWidth_, caretHeight_;
    Rectangle caretRect_;
    commonlib::Color caretColor_;
    float leftMargin_, topMargin_;
    float minWidth_, minHeight_;
};

float TextBoxConfig::blinkTime() const
{
    return blinkTime_;
}

TextSize TextBoxConfig::textSize() const
{
    return textSize_;
}

float TextBoxConfig::textHeight() const
{
    return textHeight_;
}

const commonlib::Color &TextBoxConfig::borderColor() const
{
    return borderColor_;
}

const commonlib::Color &TextBoxConfig::backColor() const
{
    return backColor_;
}

const commonlib::Color &TextBoxConfig::textColor() const
{
    return textColor_;
}

float TextBoxConfig::caretWidth() const
{
    return caretWidth_;
}

float TextBoxConfig::caretHeight() const
{
    return caretHeight_;
}

const Rectangle &TextBoxConfig::caretRect() const
{
    return caretRect_;
}

const commonlib::Color &TextBoxConfig::caretColor() const
{
    return caretColor_;
}

float TextBoxConfig::leftMargin() const
{
    return leftMargin_;
}

float TextBoxConfig::topMargin() const
{
    return topMargin_;
}

float TextBoxConfig::minWidth() const
{
    return minWidth_;
}

float TextBoxConfig::minHeight() const
{
    return minHeight_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
