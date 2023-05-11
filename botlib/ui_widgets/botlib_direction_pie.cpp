#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_direction_pie.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

DirectionPie::DirectionPie()
    : Widget()
    , direction_{0.0f, 0.0f}
{
}

void DirectionPie::init(float x,
                        float y,
                        const Vector2 &direction1,
                        bool visible)
{
    Widget::init(x, y, visible, true);
    direction_ = direction1;

    const DirectionPieConfig &cfg = Context::directionPieConfig();
    radiusSquare_ = cfg.radius() * cfg.radius();
}

void DirectionPie::setDirection(const Vector2 direction1)
{
    direction_ = direction1;
}

void DirectionPie::present() const
{
    const DirectionPieConfig &cfg = Context::directionPieConfig();
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    program.setUseObjRef(true);
    program.setObjRef(pos_);
    program.setUseColor(true);
    program.setColor(cfg.color());
    program.setAlpha(cfg.alpha());

    program.setUseDirection(false);
    program.setPositionTexPos(*cfg.directionCircle());
    glDrawArrays(GL_LINES, 0, cfg.directionCircle()->numVertices(0));

    program.setUseDirection(true);
    program.setDirection(direction_);
    program.setPositionTexPos(*cfg.directionLine());
    glDrawArrays(GL_LINES, 0, cfg.directionLine()->numVertices(0));
}

void DirectionPie::onPointerOver(float x, float y)
{
    Vector2 d{x - pos_[0], y - pos_[1]};
    if (fuzzyEqualZero(d))
    {
        return;
    }

    direction_ = normalize(d);
}

void DirectionPie::onPointerDown(float x, float y)
{
    onPointerOver(x, y);
}

} // end of namespace botlib
} // end of namespace mcdane

