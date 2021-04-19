#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <commonlib_exception.h>

using namespace ::testing;

namespace mcdane {
namespace commonlib {

TEST(TestMyException, WhatIsCorrectFormat)
{
    try
    {
        THROW_EXCEPT(MyException, "Failure");
    }
    catch(const MyException &e)
    {
        ASSERT_THAT(e.what(), MatchesRegex("^\\S+\\:\\d+ Failure$"));
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

