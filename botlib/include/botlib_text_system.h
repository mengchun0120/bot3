#ifndef INCLUDED_BOTLIB_TEXT_SYSTEM_H
#define INCLUDED_BOTLIB_TEXT_SYSTEM_H

#include <vector>
#include <commonlib_texture.h>
#include <botlib_simple_shader_program.h>
#include <botlib_text_size.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class TextSystem {
public:
    static constexpr int MIN_CHAR = 32;
    static constexpr int MAX_CHAR = 126;
    static constexpr int CHAR_COUNT = MAX_CHAR - MIN_CHAR + 1;

    TextSystem();

    ~TextSystem();

    void load(const std::string& fontDir);

    void draw(SimpleShaderProgram& program,
              const std::string& s,
              const commonlib::Point2& pos,
              TextSize size,
              const commonlib::Color* color=nullptr) const;

    commonlib::Vector2 getSize(const std::string& s,
                               TextSize size) const;

    float getWidth(const std::string& s,
                   TextSize size) const;

    float getHeight(TextSize size) const;

private:
    void loadFontTextures(const std::string& fontDir);

    void loadFontHeights();

    void loadFontRect();

    void loadFontRectForTextSize(Rectangle*& rects,
                                 std::vector<int>& rectIdx,
                                 int textSize);

    int getRectWidthForTextSize(std::vector<int>& widths,
                                int textSize);

    inline const Rectangle& getRect(int ch, TextSize textSize) const;

    inline const commonlib::Texture& getTexture(int ch) const;

private:
    static const float k_scaleFactors[textSizeCount()];

    std::vector<float> fontHeights_;
    Rectangle** fontRects_;
    std::vector<std::vector<int>> fontRectIdx_;
    commonlib::Texture* fontTextures_;
};

const Rectangle& TextSystem::getRect(int ch, TextSize textSize) const
{
    int idx = fontRectIdx_[static_cast<int>(textSize)][ch-MIN_CHAR];
    return fontRects_[static_cast<int>(textSize)][idx];
}

const commonlib::Texture& TextSystem::getTexture(int ch) const
{
    return fontTextures_[ch-MIN_CHAR];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

