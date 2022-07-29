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

    void init(const rapidjson::Value& v,
              const VertexArrayLib& vertexArrayLib);

    inline float width() const;

    inline float height() const;

    inline const commonlib::Color& frontColor() const;

    inline const commonlib::Color& backgroundColor() const;

    inline const commonlib::VertexArray* va() const;

private:
    float width_;
    float height_;
    commonlib::Color frontColor_;
    commonlib::Color backgroundColor_;
    const commonlib::VertexArray* va_;
};

float ProgressBarTemplate::width() const
{
    return width_;
}

float ProgressBarTemplate::height() const
{
    return height_;
}

const commonlib::Color& ProgressBarTemplate::frontColor() const
{
    return frontColor_;
}

const commonlib::Color& ProgressBarTemplate::backgroundColor() const
{
    return backgroundColor_;
}

const commonlib::VertexArray* ProgressBarTemplate::va() const
{
    return va_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

