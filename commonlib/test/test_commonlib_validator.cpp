#include <gtest/gtest.h>
#include <commonlib_validator.h>

using namespace ::testing;

namespace mcdane {
namespace commonlib {

TEST(TestValidator, DefaultValidateReturnsTrue)
{
    Validator v;
    ASSERT_TRUE(v.validate());
}

TEST(TestValidator, DefaultDescriptionIsEmpty)
{
    Validator v;
    ASSERT_EQ(v.description(), "");
}

TEST(TestValidator, Eq)
{
    int i = 1, j = 1;
    Validator v = eq(i, j);
    ASSERT_TRUE(v.validate());
    ASSERT_EQ(v.description(), "(1 == 1)");
}

TEST(TestValidator, Ne)
{
    int i = 1, j = 2;
    Validator v = ne(i, j);
    ASSERT_TRUE(v.validate());
    ASSERT_EQ(v.description(), "(1 != 2)");
}

} // end of namespace commonlib
} // end of namespace mcdane
