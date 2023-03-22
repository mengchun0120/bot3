#ifndef INCLUDED_BOTLIB_GAME_NAVIGATOR_H
#define INCLUDED_BOTLIB_GAME_NAVIGATOR_H

#include <functional>
#include <commonlib_vector.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class GameNavigator: public Widget {
public:
    using MoveAction = std::function<void(const commonlib::Vector2 &)>;
    using StopAction = std::function<void()>;

public:
    GameNavigator() = default;

    ~GameNavigator() override = default;

    void init(float x,
              float y,
              MoveAction &moveAction,
              StopAction &stopAction);

    void present() const override;

    bool containPos(float x, float y) const override;

    void onLostFocus() override;

    void onPointerOut() override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

private:
    void pressBase(float x, float y);

    void pressStop();

private:
    bool directionValid_;
    commonlib::Vector2 curDirection_;
    commonlib::Vector2 arrowPos_;
    MoveAction moveAction_;
    StopAction stopAction_;
    float baseRadiusSquare_, stopRadiusSquare_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
