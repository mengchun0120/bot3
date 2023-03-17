#ifndef INCLUDED_BOTLIB_MAP_NAVIGATOR_H
#define INCLUDED_BOTLIB_MAP_NAVIGATOR_H

#include <functional>
#include <vector>
#include <botlib_widget.h>

namespace mcdane {
namespace commonlib {

class Texture;

} // end of namespace commonlib

namespace botlib {

class MapNavigator: public Widget {
public:
    using Action = std::function<void()>;

public:
    MapNavigator();

    ~MapNavigator() override = default;

    void init(float x,
              float y,
              float radius,
              const commonlib::Texture *texture,
              const std::vector<Action> &actions);

    void present() const override;

    bool containPos(float x, float y);

    void onLostFocus() override;

    void onPointerOut() override;

    void onPointerOver() override;

    void onPointerDown() override;

private:
    float radius_;
    const commonlib::Texture *texture_;
    std::vector<Action> actions_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
