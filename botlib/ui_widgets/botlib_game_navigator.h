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
    using ToggleFunc = std::function<void(bool)>;

public:
    GameNavigator() = default;

    ~GameNavigator() override = default;

    void init(float x,
              float y,
              SteerFunc steerFunc,
              ToggleFunc toggleFunc);

    void present() const override;

    bool containPos(float x, float y) const override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

private:
    void pressBase(float dx, float dy);

    void pressToggle();

private:
    bool directionValid_;
    commonlib::Vector2 curDirection_;
    commonlib::Vector2 arrowPos_;
    SteerFunc steerFunc_;
    ToggleFunc toggleFunc_;
    bool greenOrRed_;
    float baseRadiusSquare_, toggleRadiusSquare_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
