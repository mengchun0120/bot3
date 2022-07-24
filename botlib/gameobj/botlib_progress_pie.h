#ifndef INCLUDED_BOTLIB_PROGRESS_PIE_H
#define INCLUDED_BOTLIB_PROGRESS_PIE_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class ProgressPieTemplate;

class ProgressPie {
public:
    ProgressPie() = default;

    void init(const ProgressPieTemplate* t,
              const commonlib::Vector2& pos);

    void present();

    void setFinishedRatio(float ratio);

private:
    const ProgressPieTemplate* t_;
    commonlib::Vector2 pos_;
    int finishedVertices_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

