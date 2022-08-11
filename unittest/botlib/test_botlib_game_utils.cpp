#include <cassert>
#include <algorithm>
#include <iostream>
#include <commonlib_region.h>
#include <commonlib_out_utils.h>
#include <botlib_game_utils.h>
#include <test_botlib.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

bool checkDiffResult(const std::vector<Region<int>>& result,
                 const std::vector<Region<int>>& expected)
{
    if (result.size() != expected.size())
    {
        return false;
    }

    for (auto it = result.begin(); it != result.end(); ++it)
    {
        auto it1 = std::find(expected.begin(), expected.end(), *it);
        if (it1 == expected.end())
        {
            return false;
        }
    }

    return true;
}

void testDiffRegion_NonOverlap()
{
    Region<int> r1(2, 5, 2, 5);
    Region<int> r2(0, 1, 0, 1);
    std::vector<Region<int>> result1;

    int num = diff(result1, r1, r2);
    assert(num == 1);
    assert(checkDiffResult(result1, {r1}));

    Region<int> r3(6, 7, 0, 7);
    std::vector<Region<int>> result2;

    num = diff(result2, r1, r3);
    assert(num == 1);
    assert(checkDiffResult(result2, {r1}));
}

void testDiffRegion_Overlap()
{
    Region<int> r1(2, 5, 2, 5);
    Region<int> r2(0, 3, 0, 3);
    std::vector<Region<int>> result1;
    std::vector<Region<int>> expected1{
        {0, 1, 0, 3},
        {2, 3, 0, 1}
    };

    int num = diff(result1, r2, r1);
    assert(num == 2);
    assert(checkDiffResult(result1, expected1));

    Region<int> r3(1, 7, 3, 7);
    std::vector<Region<int>> result2;
    std::vector<Region<int>> expected2{
        {1, 1, 3, 7},
        {6, 7, 3, 7},
        {2, 5, 6, 7}
    };

    num = diff(result2, r3, r1);
    assert(num == 3);
    assert(checkDiffResult(result2, expected2));

    Region<int> r4(1, 7, 0, 7);
    std::vector<Region<int>> result3;
    std::vector<Region<int>> expected3{
        {1, 1, 0, 7},
        {6, 7, 0, 7},
        {2, 5, 0, 1},
        {2, 5, 6, 7}
    };

    num = diff(result3, r4, r1);
    assert(num == 4);
    assert(checkDiffResult(result3, expected3));

    Region<int> r5(2, 4, 3, 7);
    std::vector<Region<int>> result4;
    std::vector<Region<int>> expected4{
        {2, 4, 6, 7}
    };

    num = diff(result4, r5, r1);
    assert(num == 1);
    assert(checkDiffResult(result4, expected4));

    Region<int> r6(2, 5, 3, 5);
    std::vector<Region<int>> result5;

    num = diff(result5, r6, r1);
    assert(num == 0);
}

void testDiffRegion()
{
    testDiffRegion_NonOverlap();
    testDiffRegion_Overlap();
}

void testGameUtils()
{
    testDiffRegion();
}

} // end of namespace botlib
} // end of namespace mcdane
