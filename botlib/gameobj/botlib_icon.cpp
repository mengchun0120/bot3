#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_icon_template.h>
#include <botlib_icon.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Icon::init(const IconTemplate* t,
                const commonlib::Vector2& pos)
{
    t_ = t;
    pos_ = pos;
}

void Icon::present()
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();

    t_->rect()->draw(program, &pos_, nullptr, nullptr, nullptr,
                     t_->texture()->id(), nullptr);
}

} // end of namespace botlib
} // end of namespace mcdane

