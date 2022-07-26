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

    inline float radius() const;

    inline const commonlib::VertexArray* va() const;

    inline const commonlib::Color& backgroundColor() const;

    inline const commonlib::Color& frontColor() const;

    inline float alpha() const;

    inline int numTriangles() const;

private:
    float radius_;
    const commonlib::VertexArray* va_;
    commonlib::Color backgroundColor_;
    commonlib::Color frontColor_;
    float alpha_;
    int numTriangles_;
};

float ProgressPieTemplate::radius() const
{
    return radius_;
}

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

int ProgressPieTemplate::numTriangles() const
{
    return numTriangles_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

