#ifndef INCLUDED_BOTLIB_MAP_NAVIGATOR_H
#define INCLUDED_BOTLIB_MAP_NAVIGATOR_H

#include <functional>
#include <vector>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class MapNavigator: public Widget {
public:
    using Action = std::function<void()>;

public:
    MapNavigator();

    ~MapNavigator() override = default;

    void init(float x,
              float y,
              const std::vector<Action> &actions);

    void present() const override;

    void update(float timeDelta);

    bool containPos(float x, float y) const override;

    void onLostFocus() override;

    void onPointerOut() override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

private:
    int controlIdx(float x, float y);

private:
    std::vector<Action> actions_;
    float radiusSquare_;
    int curControlIdx_;
    float timeSinceLastPress_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
