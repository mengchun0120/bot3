#include <cmath>
#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_context.h>
#include <botlib_progress_pie_template.h>
#include <botlib_progress_pie.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ProgressPie::init(const ProgressPieTemplate* t,
                       const commonlib::Vector2& pos)
{
    t_ = t;
    pos_ = pos;
    finishedVertices_ = 0;
    leftVertices_ = t_->va()->numVertices(0);
}

void ProgressPie::present()
{
    presentPie();
    if (t_->iconRect())
    {
        presentIcon();
    }
}

void ProgressPie::presentPie()
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();

    program.setUseObjRef(true);
    program.setObjRef(pos_);
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

void ProgressPie::presentIcon()
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();

    t_->iconRect()->draw(program, &pos_, nullptr, nullptr, nullptr,
                         t_->iconImage()->id(), nullptr);
}

void ProgressPie::setFinishedRatio(float ratio)
{
    ratio = clamp(ratio, 0.0f, 1.0f);
    finishedVertices_ = static_cast<int>(floor(t_->numTriangles() * ratio)) * 3;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

void ProgressPie::setPos(const commonlib::Vector2& pos)
{
    pos_ = pos;
}

} // end of namespace botlib
} // end of namespace mcdane


