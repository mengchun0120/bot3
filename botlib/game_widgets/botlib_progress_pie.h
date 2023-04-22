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

    ~ProgressPie() = default;

    void init(const ProgressPieTemplate *t,
              const commonlib::Vector2 *p=nullptr);

    inline const ProgressPieTemplate *getTemplate() const;

    void present(int iconIdx=0) const;

    void setPos(const commonlib::Vector2 &p);

    void setFinishedRatio(float ratio);

    inline bool finished() const;

private:
    void initIcons(const commonlib::Vector2 *p);

    void presentPie() const;

private:
    const ProgressPieTemplate *t_;
    commonlib::Vector2 pos_;
    int finishedVertices_;
    int leftVertices_;
    std::vector<Icon> icons_;
};

const ProgressPieTemplate *ProgressPie::getTemplate() const
{
    return t_;
}

bool ProgressPie::finished() const
{
    return leftVertices_ == 0;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

