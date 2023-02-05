#include <cmath>
#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_context.h>
#include <botlib_icon.h>
#include <botlib_progress_pie_template.h>
#include <botlib_progress_pie.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ProgressPie::init(const ProgressPieTemplate* t)
{
    t_ = t;
    finishedVertices_ = 0;
    leftVertices_ = t_->va()->numVertices(0);
    initIcons();
}

void ProgressPie::present(const commonlib::Vector2& pos,
                          int iconIndex)
{
    presentPie(pos);
    if (iconIndex >= 0)
    {
        icons_[iconIndex].present(pos);
    }
}

void ProgressPie::setFinishedRatio(float ratio)
{
    ratio = clamp(ratio, 0.0f, 1.0f);
    finishedVertices_ = static_cast<int>(floor(t_->numTriangles() * ratio)) * 3;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

void ProgressPie::initIcons()
{
    if (t_->numIcons() <= 0)
    {
        return;
    }

    int iconCount = t_->numIcons();

    icons_.resize(iconCount);
    for (int i = 0; i < iconCount; ++i)
    {
        icons_[i].init(t_->iconTemplate(i));
    }
}

void ProgressPie::presentPie(const commonlib::Vector2& pos)
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();

    program.setUseObjRef(true);
    program.setObjRef(pos);
    program.setPositionTexPos(*(t_->va()));
    program.setUseColor(true);
    program.setUseDirection(false);
    program.setAlpha(t_->alpha());

    if (finishedVertices_ > 0)
    {
        program.setColor(t_->backgroundColor());
        glDrawArrays(GL_TRIANGLES, 0, finishedVertices_);
    }

    if (leftVertices_ > 0)
    {
        program.setColor(t_->frontColor());
        glDrawArrays(GL_TRIANGLES, finishedVertices_, leftVertices_);
    }
}

} // end of namespace botlib
} // end of namespace mcdane


