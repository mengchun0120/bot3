#include <gtest/gtest.h>
#include <commonlib_exception.h>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

TEST(TestArgument, ValidNameOptThrowNoException)
{
    EXPECT_NO_THROW(Argument arg("name", "n", "name", ""));
    EXPECT_NO_THROW(Argument arg("arg01", "1", "arg_01", ""));
    EXPECT_NO_THROW(Argument arg("stash_count", "s", "stash_count", ""));
}

TEST(TestArgument, InvalidNameOptThrowException)
{
    EXPECT_THROW(Argument arg("", "n", "name", ""),
                 InvalidArgumentException);
    EXPECT_THROW(Argument arg("price", "-p", "price", "price"),
                 InvalidArgumentException);
    EXPECT_THROW(Argument arg("weight", "w", "--weight", "weight"),
                 InvalidArgumentException);
}

} // end of namespace commonlib
} // end of namespace mcdane

