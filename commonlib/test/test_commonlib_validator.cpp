#include <gtest/gtest.h>
#include <commonlib_validator.h>

using namespace ::testing;

namespace mcdane {
namespace commonlib {

TEST(TestValidator, Default)
{
    Validator v;
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "");
}

TEST(TestValidator, Eq)
{
    int i = 1, j = 1;
    Validator v = Eq(i, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "(1 == 1)");
}

TEST(TestValidator, Ne)
{
    int i = 1, j = 2;
    Validator v = Ne(i, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "(1 != 2)");
}

} // end of namespace commonlib
} // end of namespace mcdane
