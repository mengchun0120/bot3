#ifndef INCLUDED_BOTLIB_PROGRESS_PIE_TEMPLATE_H
#define INCLUDED_BOTLIB_PROGRESS_PIE_TEMPLATE_H

#include <rapidjson/document.h>
#include <commonlib_color.h>
#include <botlib_typedef.h>

namespace mcdane {

namespace commonlib {

class VertexArray;

} // end of namespcae commonlib

namespace botlib {

class ProgressPieTemplate {
public:
    ProgressPieTemplate() = default;

    void init(const rapidjson::Value& v,
              const VertexArrayLib& vertexArrayLib);

    inline const commonlib::VertexArray* va() const;

    inline const commonlib::Color& backgroundColor() const;

    inline const commonlib::Color& frontColor() const;

    inline float alpha() const;

private:
    const commonlib::VertexArray* va_;
    commonlib::Color backgroundColor_;
    commonlib::Color frontColor_;
    float alpha_;
};

const commonlib::VertexArray* ProgressPieTemplate::va() const
{
    return va_;
}

const commonlib::Color& ProgressPieTemplate::backgroundColor() const
{
    return backgroundColor_;
}

const commonlib::Color& ProgressPieTemplate::frontColor() const
{
    return frontColor_;
}

float ProgressPieTemplate::alpha() const
{
    return alpha_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

