#ifndef INCLUDED_BOTLIB_PROGRESS_PIE_TEMPLATE_H
#define INCLUDED_BOTLIB_PROGRESS_PIE_TEMPLATE_H

#include <vector>
#include <rapidjson/document.h>
#include <commonlib_color.h>
#include <botlib_icon_template.h>
#include <botlib_typedef.h>

namespace mcdane {

namespace commonlib {

class VertexArray;

} // end of namespcae commonlib

namespace botlib {

class ProgressPieTemplate {
public:
    ProgressPieTemplate();

    void init(const rapidjson::Value &v,
              const VertexArrayLib &vertexArrayLib,
              const IconTemplateLib &iconLib);

    inline float radius() const;

    inline const commonlib::VertexArray *va() const;

    inline const commonlib::Color &backgroundColor() const;

    inline const commonlib::Color &frontColor() const;

    inline float alpha() const;

    inline int numTriangles() const;

    inline int numIcons() const;

    inline const IconTemplate *iconTemplate(int idx) const;

private:
    void initVertexArray(const std::string &vertexArrayName,
                         const VertexArrayLib &vertexArrayLib);

    void initIcons(const std::vector<std::string> &iconNames,
                   const IconTemplateLib &iconLib);

private:
    float radius_;
    const commonlib::VertexArray *va_;
    commonlib::Color backgroundColor_;
    commonlib::Color frontColor_;
    float alpha_;
    int numTriangles_;
    std::vector<const IconTemplate*> icons_;
};

float ProgressPieTemplate::radius() const
{
    return radius_;
}

const commonlib::VertexArray *ProgressPieTemplate::va() const
{
    return va_;
}

const commonlib::Color &ProgressPieTemplate::backgroundColor() const
{
    return backgroundColor_;
}

const commonlib::Color &ProgressPieTemplate::frontColor() const
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

int ProgressPieTemplate::numIcons() const
{
    return static_cast<int>(icons_.size());
}

const IconTemplate *ProgressPieTemplate::iconTemplate(int idx) const
{
    return icons_[idx];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

