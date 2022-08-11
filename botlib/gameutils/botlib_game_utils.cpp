#include <commonlib_log.h>
#include <commonlib_region.h>
#include <botlib_game_utils.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

int diff(std::vector<Region<int>>& result,
         const Region<int>& r1,
         const Region<int>& r2)
{
    if (!overlap(r1, r2))
    {
        result.resize(1);
        result[0].init(r1);
        return 1;
    }

    int leftExtra = r1.left() < r2.left() ? 1 : 0;
    int rightExtra = r1.right() > r2.right() ? 1 : 0;
    int bottomExtra = r1.bottom() < r2.bottom() ? 1 : 0;
    int topExtra = r1.top() > r2.top() ? 1 : 0;
    int resultSize = leftExtra + rightExtra + bottomExtra + topExtra;

    if (resultSize == 0)
    {
        return 0;
    }

    int index = 0;

    result.resize(resultSize);

    if (leftExtra)
    {
        result[index].init(r1.left(), r2.left()-1, r1.bottom(), r1.top());
        ++index;
    }

    if (rightExtra)
    {
        result[index].init(r2.right()+1, r1.right(), r1.bottom(), r1.top());
        ++index;
    }

    if (bottomExtra)
    {
        result[index].init(leftExtra ? r2.left() : r1.left(),
                           rightExtra ? r2.right() : r1.right(),
                           r1.bottom(), r2.bottom()-1);
        ++index;
    }

    if (topExtra)
    {
        result[index].init(leftExtra ? r2.left() : r1.left(),
                           rightExtra ? r2.right() : r1.right(),
                           r2.top()+1, r1.top());
    }

    return resultSize;
}

} // end of namespace botlib
} // end of namespace mcdane

