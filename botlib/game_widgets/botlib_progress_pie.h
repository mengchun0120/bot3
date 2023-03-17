#ifndef INCLUDED_BOTLIB_PROGRESS_PIE_H
#define INCLUDED_BOTLIB_PROGRESS_PIE_H

#include <vector>
#include <commonlib_vector.h>
#include <botlib_icon.h>

namespace mcdane {
namespace botlib {

class ProgressPieTemplate;
class Icon;

class ProgressPie {
public:
    ProgressPie() = default;

    ProgressPie(const ProgressPieTemplate *t);

    ~ProgressPie() = default;

    void init(const ProgressPieTemplate *t);

    void present(const commonlib::Vector2 &pos,
                 int iconIndex=-1) const;

    void setFinishedRatio(float ratio);

private:
    void initIcons();

    void presentPie(const commonlib::Vector2 &pos) const;

private:
    const ProgressPieTemplate *t_;
    int finishedVertices_;
    int leftVertices_;
    std::vector<Icon> icons_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

