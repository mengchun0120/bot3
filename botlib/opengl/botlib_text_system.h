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

    void init(const std::string &fontDir);

    void draw(SimpleShaderProgram &program,
              const std::string &s,
              const commonlib::Point2 &pos,
              TextSize size,
              const commonlib::Color *color=nullptr) const;

    void draw(SimpleShaderProgram &program,
              const char *s,
              int len,
              const commonlib::Point2 &pos,
              TextSize size,
              const commonlib::Color *color=nullptr) const;

    template <typename ITERATOR>
    void draw(SimpleShaderProgram &program,
              ITERATOR begin,
              ITERATOR end,
              const commonlib::Point2 &pos,
              TextSize size,
              const commonlib::Color *color=nullptr) const;

    commonlib::Vector2 getSize(const std::string &s,
                               TextSize size) const;

    float getWidth(const char *s, int len, TextSize size) const;

    float getWidth(const std::string &s, TextSize size) const;

    template <typename ITERATOR>
    float getWidth(ITERATOR begin, ITERATOR end, TextSize size) const;

    inline float getWidth(int ch, TextSize textSize) const;

    inline float getHeight(TextSize size) const;

private:
    static std::string fontTextureFile(const std::string &fontDir,
                                       int ch);

    void initFontTextures(const std::string &fontDir);

    void initFontHeights();

    void initFontRect();

    void initFontRectForTextSize(Rectangle *&rects,
                                 std::vector<int> &rectIdx,
                                 int textSize);

    int getRectWidthForTextSize(std::vector<int> &widths,
                                int textSize);

    inline const Rectangle &getRect(int ch, TextSize textSize) const;

    inline const commonlib::Texture &getTexture(int ch) const;

private:
    static const float k_scaleFactors[textSizeCount()];

    std::vector<float> fontHeights_;
    Rectangle* *fontRects_;
    std::vector<std::vector<int>> fontRectIdx_;
    commonlib::Texture *fontTextures_;
};

template <typename ITERATOR>
void TextSystem::draw(SimpleShaderProgram &program,
                      ITERATOR begin,
                      ITERATOR end,
                      const commonlib::Point2 &pos,
                      TextSize size,
                      const commonlib::Color *color) const
{
    commonlib::Point2 p{pos[0], pos[1] + getHeight(size)/2.0f};

    for (auto it = begin; it != end; ++it)
    {
        const Rectangle &curRect = getRect(*it, size);
        float halfWidth = curRect.width() / 2.0f;
        const commonlib::Texture &texture = getTexture(*it);

        p[0] += halfWidth;
        curRect.draw(program, &p, nullptr, nullptr, nullptr,
                     texture.id(), color);

        p[0] += halfWidth;
    }
}

template <typename ITERATOR>
float TextSystem::getWidth(ITERATOR begin, ITERATOR end, TextSize size) const
{
    float width = 0.0f;
    for (auto it = begin; it != end; ++it)
    {
        width += getWidth(*it, size);
    }

    return width;
}

float TextSystem::getWidth(int ch, TextSize textSize) const
{
    return getRect(ch, textSize).width();
}

float TextSystem::getHeight(TextSize size) const
{
    return fontHeights_[static_cast<int>(size)];
}

const Rectangle &TextSystem::getRect(int ch, TextSize textSize) const
{
    int idx = fontRectIdx_[static_cast<int>(textSize)][ch-MIN_CHAR];
    return fontRects_[static_cast<int>(textSize)][idx];
}

const commonlib::Texture &TextSystem::getTexture(int ch) const
{
    return fontTextures_[ch-MIN_CHAR];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

