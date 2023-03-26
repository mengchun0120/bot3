#ifndef INCLUDED_BOTLIB_SKILL_BUTTON_H
#define INCLUDED_BOTLIB_SKILL_BUTTON_H

#include <functional>
#include <botlib_progress_pie.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class SkillButton: public Widget {
public:
    using Action = std::function<void(SkillButton &)>;

public:
    SkillButton() = default;

    ~SkillButton() override = default;

    void init(float x,
              float y,
              const ProgressPieTemplate *t,
              Action action);

    void present() const override;

    bool containPos(float x, float y) const override;

    void onLostFocus() override;

    void onPointerOut() override;

    void onPointerOver(float x, float y) override;

    void onPointerDown(float x, float y) override;

    inline bool enabled() const;

    void setEnabled(bool b);

    void setRatio(float ratio);

private:
    ProgressPie pie_;
    Action action_;
    float radiusSquare_;
    bool enabled_;
};

bool SkillButton::enabled() const
{
    return enabled_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
