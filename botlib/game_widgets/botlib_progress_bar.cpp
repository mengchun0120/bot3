#include <cmath>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_context.h>
#include <botlib_progress_bar_template.h>
#include <botlib_progress_bar.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ProgressBar::init(const ProgressBarTemplate *t,
                       const commonlib::Vector2 &pos)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t_ = t;
    pos_ = pos;
    finishedVertices_ = 2;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

void ProgressBar::present()
{
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    program.setUseObjRef(true);
    program.setObjRef(pos_);
    program.setPositionTexPos(*(t_->va()));
    program.setUseColor(true);
    program.setUseDirection(false);
    program.setAlpha(t_->alpha());

    if (finishedVertices_ > 2)
    {
        program.setColor(t_->backgroundColor());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, finishedVertices_);
    }

    if (leftVertices_ > 0)
    {
        program.setColor(t_->frontColor());
        glDrawArrays(GL_TRIANGLE_STRIP, finishedVertices_ - 2, leftVertices_);
    }

    program.setPositionTexPos(*(t_->borderVertexArray()));
    program.setColor(t_->borderColor());
    glDrawArrays(GL_LINE_LOOP, 0, t_->borderVertexArray()->numVertices(0));
}

void ProgressBar::setRatio(float ratio)
{
    float finishedRatio = clamp(1.0f-ratio, 0.0f, 1.0f);
    finishedVertices_ = 2 + static_cast<int>(
                                floor(finishedRatio * t_->numBlocks())) * 2;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

void ProgressBar::setPos(const Vector2 &pos)
{
    pos_ = pos;
}

} // end of namespace botlib
} // end of namespace mcdane

