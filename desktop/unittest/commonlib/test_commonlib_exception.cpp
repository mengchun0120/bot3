#include <regex>
#include <cassert>
#include <commonlib_exception.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testMyException()
{
    try
    {
        THROW_EXCEPT(MyException, "Failure");
    }
    catch(const MyException &e)
    {
        std::regex r("^\\S+\\:\\d+ Failure$");
        assert(regex_match(e.what(), r));
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

