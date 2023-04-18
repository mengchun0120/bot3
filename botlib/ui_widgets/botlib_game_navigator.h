#ifndef INCLUDED_BOTLIB_GAME_NAVIGATOR_H
#define INCLUDED_BOTLIB_GAME_NAVIGATOR_H

#include <functional>
#include <commonlib_vector.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class GameNavigator: public Widget {
public:
    using SteerFunc = std::function<void(const commonlib::Vector2 &)>;

public:
    GameNavigator() = default;

    ~GameNavigator() override = default;

    void init(float x,
              float y,
              SteerFunc steerFunc);

    inline bool directionValid() const;

    inline const commonlib::Vector2 &curDirection() const;

    void disableDirection();

    void setDirection(const commonlib::Vector2 &direction);

    void present() const override;

    bool containPos(float x, float y) const override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

    void onPointerUp(float x, float y) override;

private:
    void onPointer(float x, float y);

    void resetArrowPos();

private:
    bool directionValid_;
    commonlib::Vector2 curDirection_;
    commonlib::Vector2 arrowPos_;
    SteerFunc steerFunc_;
    float radiusSquare_;
};

bool GameNavigator::directionValid() const
{
    return directionValid_;
}

const commonlib::Vector2 &GameNavigator::curDirection() const
{
    return curDirection_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
