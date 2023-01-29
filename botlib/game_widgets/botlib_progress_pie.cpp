#include <cmath>
#include <commonlib_log.h>
#include <commonlib_math_utils.h>
#include <botlib_context.h>
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
}

void ProgressPie::present(const commonlib::Vector2& pos)
{
    presentPie(pos);
    if (t_->iconRect())
    {
        presentIcon(pos);
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

void ProgressPie::presentIcon(const commonlib::Vector2& pos)
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();

    t_->iconRect()->draw(program, &pos, nullptr, nullptr, nullptr,
                         t_->iconImage()->id(), nullptr);
}

void ProgressPie::setFinishedRatio(float ratio)
{
    ratio = clamp(ratio, 0.0f, 1.0f);
    finishedVertices_ = static_cast<int>(floor(t_->numTriangles() * ratio)) * 3;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

} // end of namespace botlib
} // end of namespace mcdane


