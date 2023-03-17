#ifndef INCLUDED_BOTLIB_LABEL_H
#define INCLUDED_BOTLIB_LABEL_H

#include <string>
#include <commonlib_color.h>
#include <botlib_text_size.h>
#include <botlib_align.h>
#include <botlib_rectangular_widget.h>

namespace mcdane {
namespace botlib {

class Label: public RectangularWidget {
public:
    Label() = default;

    Label(float x,
          float y,
          float width,
          float height,
          const std::string text = "",
          TextSize textSize = TextSize::SMALL,
          HAlign halign = HAlign::LEFT,
          VAlign valign = VAlign::TOP,
          const commonlib::Color *textColor = nullptr,
          const commonlib::Color *backColor = nullptr,
          const commonlib::Color *borderColor = nullptr,
          bool visible = true);

    ~Label() override = default;

    void init(float x,
              float y,
              float width,
              float height,
              const std::string text = "",
              TextSize textSize = TextSize::SMALL,
              HAlign halign = HAlign::LEFT,
              VAlign valign = VAlign::TOP,
              const commonlib::Color *textColor = nullptr,
              const commonlib::Color *backColor = nullptr,
              const commonlib::Color *borderColor = nullptr,
              bool visible = true);

    void setPos(float x, float y) override;

    void shiftPos(float dx, float dy) override;

    void present() const override;

    void setText(const std::string &text);

    void setTextSize(TextSize textSize);

    void setHAlign(HAlign halign);

    void setVAlign(VAlign valign);

private:
    void updateTextPos();

    void initColors(const commonlib::Color *textColor,
                    const commonlib::Color *backColor,
                    const commonlib::Color *borderColor);

    float calculateTextPosX();

    float calculateTextPosY();

private:
    std::string text_;
    commonlib::Vector2 textPos_;
    TextSize textSize_;
    HAlign halign_;
    VAlign valign_;
    commonlib::Color textColor_;
    commonlib::Color backColor_;
    commonlib::Color borderColor_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

