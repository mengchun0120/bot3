#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_icon_template.h>
#include <botlib_icon.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Icon::init(const IconTemplate *t,
                const Vector2 *p)
{
    t_ = t;
    if (p)
    {
        setPos(*p);
    }
}

void Icon::present() const
{
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    t_->rect()->draw(program, &pos_, nullptr, nullptr, nullptr,
                     t_->texture()->id(), nullptr);
}

void Icon::setPos(const Vector2 &p)
{
    pos_ = p;
}

} // end of namespace botlib
} // end of namespace mcdane

