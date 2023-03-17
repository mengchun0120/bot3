#ifndef INCLUDED_BOTLIB_PROGRESS_BAR_TEMPLATE_H
#define INCLUDED_BOTLIB_PROGRESS_BAR_TEMPLATE_H

#include <rapidjson/document.h>
#include <commonlib_color.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class ProgressBarTemplate {
public:
    ProgressBarTemplate() = default;

    ~ProgressBarTemplate() = default;

    void init(const rapidjson::Value &v,
              const VertexArrayLib &vertexArrayLib);

    inline float width() const;

    inline float height() const;

    inline const commonlib::Color &frontColor() const;

    inline const commonlib::Color &backgroundColor() const;

    inline const commonlib::VertexArray *va() const;

    inline float alpha() const;

    inline int numBlocks() const;

    inline const commonlib::VertexArray *borderVertexArray() const;

    inline const commonlib::Color &borderColor() const;

private:
    float width_;
    float height_;
    commonlib::Color frontColor_;
    commonlib::Color backgroundColor_;
    const commonlib::VertexArray *va_;
    float alpha_;
    int numBlocks_;
    const commonlib::VertexArray *borderVertexArray_;
    commonlib::Color borderColor_;
};

float ProgressBarTemplate::width() const
{
    return width_;
}

float ProgressBarTemplate::height() const
{
    return height_;
}

const commonlib::Color &ProgressBarTemplate::frontColor() const
{
    return frontColor_;
}

const commonlib::Color &ProgressBarTemplate::backgroundColor() const
{
    return backgroundColor_;
}

const commonlib::VertexArray *ProgressBarTemplate::va() const
{
    return va_;
}

float ProgressBarTemplate::alpha() const
{
    return alpha_;
}

int ProgressBarTemplate::numBlocks() const
{
    return numBlocks_;
}

const commonlib::VertexArray *ProgressBarTemplate::borderVertexArray() const
{
    return borderVertexArray_;
}

const commonlib::Color &ProgressBarTemplate::borderColor() const
{
    return borderColor_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

