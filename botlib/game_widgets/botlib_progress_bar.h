#ifndef INCLUDED_BOTLIB_PRORESS_BAR_H
#define INCLUDED_BOTLIB_PRORESS_BAR_H

#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class ProgressBarTemplate;

class ProgressBar {
public:
    ProgressBar() = default;

    void init(const ProgressBarTemplate* t,
              const commonlib::Vector2& pos);

    void present();

    void setRatio(float ratio);

private:
    const ProgressBarTemplate *t_;
    commonlib::Vector2 pos_;
    int finishedVertices_;
    int leftVertices_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

