#ifndef INCLUDED_BOTLIB_PROGRESS_PIE_H
#define INCLUDED_BOTLIB_PROGRESS_PIE_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class ProgressPieTemplate;

class ProgressPie {
public:
    ProgressPie() = default;

    void init(const ProgressPieTemplate* t);

    void present(const commonlib::Vector2& pos);

    void setFinishedRatio(float ratio);

private:
    void presentPie(const commonlib::Vector2& pos);

    void presentIcon(const commonlib::Vector2& pos);

private:
    const ProgressPieTemplate* t_;
    int finishedVertices_;
    int leftVertices_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

