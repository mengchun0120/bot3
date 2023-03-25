#ifndef INCLUDED_BOTLIB_SKILL_BUTTON_H
#define INCLUDED_BOTLIB_SKILL_BUTTON_H

#include <functional>
#include <botlib_progress_pie.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class SkillButton: public Widget {
public:
    using Action = std::function<void()>;

public:
    SkillButton() = default;

    ~SkillButton() override = default;

    void init(float x,
              float y,
              const ProgressPieTemplate *t,
              float coolDown,
              Action action);

    void present() const override;

    void update(float timeDelta);

    bool containPos(float x, float y) const override;

    void onLostFocus() override;

    void onPointerOut() override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

    inline bool enabled() const;

    void reset();

private:
    ProgressPie pie_;
    Action action_;
    float coolDown_;
    bool cooling_;
    float duration_;
    float radiusSquare_;
};

bool SkillButton::enabled() const
{
    return pie_.finished();
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
