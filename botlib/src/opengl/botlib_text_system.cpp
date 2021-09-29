#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_file_utils.h>
#include <botlib_text_system.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

const float TextSystem::k_scaleFactors[] = {1.0f, 0.75f, 0.5f, 0.36f};

std::string fontTextureFile(const std::string& fontDir,
                            int ch)
{
    std::string file = "ascii_" + std::to_string(ch) + ".png";
    return constructPath({fontDir, file});
}

TextSystem::TextSystem()
    : fontRects_(nullptr)
    , fontTextures_(nullptr)
{
}

TextSystem::~TextSystem()
{
    if (fontRects_)
    {
        for (int s = firstTextSize(); s < textSizeCount(); ++s)
        {
            delete[] fontRects_[s];
        }
        delete[] fontRects_;
    }
    delete[] fontTextures_;
}

void TextSystem::load(const std::string& fontDir)
{
    loadFontTextures(fontDir);
    loadFontHeights();
    loadFontRect();
}

void TextSystem::draw(SimpleShaderProgram& program,
                      const std::string& s,
                      const Point2& pos,
                      TextSize size,
                      const Color* color) const
{
    if (!isValidTextSize(size))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid size");
    }

    if (s.size() == 0)
    {
        return;
    }

    Point2 p{
        pos[0] + getRect(s[0], size).width()/2.0f,
        pos[1] + fontHeights_[static_cast<int>(size)]/2.0f
    };

    for (std::size_t i = 0; i < s.size(); ++i)
    {
        const Rectangle& curRect = getRect(s[i], size);
        const Texture& texture = getTexture(s[i]);

        curRect.draw(program, &p, nullptr, nullptr, nullptr,
                     texture.id(), color);

        if (i < s.size() - 1)
        {
            const Rectangle& nextRect = getRect(s[i+1], size);
            p[0] += (curRect.width() + nextRect.width()) / 2.0f;
        }
    }
}

commonlib::Vector2 TextSystem::getSize(const std::string& s,
                                       TextSize size) const
{
    commonlib::Vector2 sz{0.0f, 0.0f};

    if (s.size() == 0)
    {
        return sz;
    }

    sz[0] = getWidth(s, size);
    sz[1] = getHeight(size);

    return sz;
}

float TextSystem::getWidth(const std::string& s,
                           TextSize size) const
{
    if (!isValidTextSize(size))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid size");
    }

    if (s.size() == 0)
    {
        return 0.0f;
    }

    float width = 0.0f;
    for (std::size_t i = 0; i < s.size(); ++i)
    {
        width += getRect(s[i], size).width();
    }

    return width;
}

float TextSystem::getHeight(TextSize size) const
{
    if (!isValidTextSize(size))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid size" +
                     toString(static_cast<int>(size)));
    }

    return fontHeights_[static_cast<int>(size)];
}

void TextSystem::loadFontTextures(const std::string& fontDir)
{
    fontTextures_ = new Texture[CHAR_COUNT];
    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        std::string fontFile = fontTextureFile(fontDir, MIN_CHAR+i);
        fontTextures_[i].init(fontFile);
    }
}

void TextSystem::loadFontHeights()
{
    fontHeights_.resize(textSizeCount());
    for (int s = firstTextSize(); s < textSizeCount(); ++s)
    {
        float h = fontTextures_[0].height() * k_scaleFactors[s];
        fontHeights_[s] = static_cast<float>(floor(h));
    }
}

void TextSystem::loadFontRect()
{
    fontRects_ = new Rectangle*[textSizeCount()];
    fontRectIdx_.resize(textSizeCount());

    for (int s = firstTextSize(); s < textSizeCount(); ++s)
    {
        loadFontRectForTextSize(fontRects_[s], fontRectIdx_[s], s);
    }
}

void TextSystem::loadFontRectForTextSize(Rectangle*& rects,
                                         std::vector<int>& rectIdx,
                                         int textSize)
{
    std::unordered_map<int,int> widthRectMap;
    std::vector<int> widths;
    float height = fontHeights_[textSize];
    int count = getRectWidthForTextSize(widths, textSize);
    int idx = 0;

    rects = new Rectangle[count];
    rectIdx.resize(CHAR_COUNT);

    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        int w = widths[i];
        auto it = widthRectMap.find(w);
        if (it == widthRectMap.end())
        {
            widthRectMap[w] = idx;
            rectIdx[i] = idx;
            rects[idx].load(static_cast<float>(w), height, TexRectangle());
            ++idx;
        }
        else
        {
            rectIdx[i] = it->second;
        }
    }
}

int TextSystem::getRectWidthForTextSize(std::vector<int>& widths,
                                        int textSize)
{
    float factor = k_scaleFactors[textSize];
    std::unordered_set<int> widthSet;
    int count = 0;

    widths.resize(CHAR_COUNT);
    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        float w = fontTextures_[i].width() * factor;
        int width = static_cast<int>(floor(w));

        widths[i] = width;

        auto it = widthSet.find(width);
        if (it == widthSet.end())
        {
            widthSet.insert(width);
            ++count;
        }
    }

    return count;
}

} // end of namespace botlib
} // end of namespace mcdane

