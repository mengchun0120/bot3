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

void ProgressBar::init(const ProgressBarTemplate* t,
                       const commonlib::Vector2& pos)
{
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException, "t is null");
    }

    t_ = t;
    pos_ = pos;
    finishedVertices_ = 0;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

void ProgressBar::present()
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
        glDrawArrays(GL_TRIANGLE_STRIP, 0, finishedVertices_);
    }

    if (leftVertices_ > 0)
    {
        program.setColor(t_->frontColor());
        glDrawArrays(GL_TRIANGLE_STRIP, finishedVertices_, leftVertices_);
    }
}

void ProgressBar::setRatio(float ratio)
{
    ratio = clamp(ratio, 0.0f, 1.0f);
    finishedVertices_ = 2 + static_cast<int>(floor(ratio * t_->numBlocks())) * 2;
    leftVertices_ = t_->va()->numVertices(0) - finishedVertices_;
}

} // end of namespace botlib
} // end of namespace mcdane

