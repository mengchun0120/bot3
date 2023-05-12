#ifndef INCLUDED_BOTLIB_SKILL_BUTTON_H
#define INCLUDED_BOTLIB_SKILL_BUTTON_H

#include <functional>
#include <botlib_progress_pie.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class SkillWithCost;

class SkillButton: public Widget {
public:
    using Action = std::function<void(SkillButton &)>;

public:
    SkillButton() = default;

    ~SkillButton() override = default;

    void init(float x,
              float y,
              const ProgressPieTemplate *t,
              Action action=nullptr,
              SkillWithCost *skill=nullptr);

    void present() const override;

    void update(float timeDelta) override;

    bool containPos(float x, float y) const override;

    void onPointerDown(float x, float y) override;

    inline bool enabled() const;

    void setPos(float x, float y) override;

    void shiftPos(float dx, float dy) override;

    void setEnabled(bool b);

    void setRatio(float ratio);

private:
    SkillWithCost *skill_;
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
