#ifndef INCLUDED_BOTLIB_DIRECTION_PIE_H
#define INCLUDED_BOTLIB_DIRECTION_PIE_H

#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class DirectionPie: public Widget {
public:
    DirectionPie();

    ~DirectionPie() override = default;

    void init(float x,
              float y,
              const commonlib::Vector2 &direction1,
              bool visible);

    inline const commonlib::Vector2 &direction() const;

    void setDirection(const commonlib::Vector2 direction1);

    void present() const override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

    inline bool containPos(float x, float y) const override;

private:
    commonlib::Vector2 direction_;
    float radiusSquare_;
};

const commonlib::Vector2 &DirectionPie::direction() const
{
    return direction_;
}

bool DirectionPie::containPos(float x, float y) const
{
    float dx = x - pos_[0], dy = y - pos_[1];
    return dx*dx + dy*dy <= radiusSquare_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
