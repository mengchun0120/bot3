#ifndef INCLUDED_BOTLIB_LABEL_H
#define INCLUDED_BOTLIB_LABEL_H

#include <string>
#include <rapidjson/document.h>
#include <commonlib_color.h>
#include <botlib_text_size.h>
#include <botlib_align.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class Label: public Widget {
public:
    static void initConfig(const rapidjson::Value& cfg);

    Label() = default;

    Label(float x,
          float y,
          float z,
          float width,
          float height,
          const std::string text = "",
          TextSize textSize = TextSize::SMALL,
          HAlign halign = HAlign::LEFT,
          VAlign valign = VAlign::TOP,
          const commonlib::Color& textColor = k_defaultTextColor,
          const commonlib::Color& backgroundColor = k_defaultBackgroundColor,
          const commonlib::Color& borderColor = k_defaultBorderColor,
          bool visible = true);

    ~Label() override = default;

    void init(float x,
              float y,
              float z,
              float width,
              float height,
              const std::string text = "",
              TextSize textSize = TextSize::SMALL,
              HAlign halign = HAlign::LEFT,
              VAlign valign = VAlign::TOP,
              const commonlib::Color& textColor = k_defaultTextColor,
              const commonlib::Color& backgroundColor = k_defaultBackgroundColor,
              const commonlib::Color& borderColor = k_defaultBorderColor,
              bool visible = true);

    void setPos(float x,
                float y,
                float z) override;

    void shiftPos(float dx,
                  float dy) override;

    void present() const override;

    void setText(const std::string& text);

    void setTextSize(TextSize textSize);

    void setHAlign(HAlign halign);

    void setVAlign(VAlign valign);

private:
    void updateTextPos();

    float calculateTextPosX();

    float calculateTextPosY();

private:
    static commonlib::Color k_defaultTextColor;
    static commonlib::Color k_defaultBackgroundColor;
    static commonlib::Color k_defaultBorderColor;

    std::string text_;
    commonlib::Vector2 textPos_;
    TextSize textSize_;
    HAlign halign_;
    VAlign valign_;
    commonlib::Color textColor_;
    commonlib::Color backgroundColor_;
    commonlib::Color borderColor_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

