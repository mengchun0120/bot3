#include <cassert>
#include <iostream>
#include <commonlib_file_utils.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testFileUtils_TestConstructPath()
{
#ifdef _WIN32
    std::string expected[] = {
        "lib\\total",
        "dir\\res",
        "zero\\hello",
        "veg\\list\\tu",
    };
#elif __linux__
    std::string expected[] = {
        "lib/total",
        "dir/res",
        "zero/hello",
        "veg/list/tu",
    };
#endif

    std::cout << constructPath({"lib", "", "total"}) << std::endl;
    assert(constructPath({"lib", "", "total"}) == expected[0]);
    assert(constructPath({"", "", "dir", "res"}) == expected[1]);
    assert(constructPath("", {"zero", "", "hello", ""}) == expected[2]);
    assert(constructPath("veg", {"list", "tu"}) == expected[3]);
}

void testFileUtils()
{
    testFileUtils_TestConstructPath();
}

} // end of namespace commonlib
} // end of namespace mcdane
