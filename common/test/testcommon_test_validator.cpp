#include <gtest/gtest.h>
#include <common_validator.h>

using namespace ::testing;

namespace mcdane {
namespace common {

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

TEST(TestValidator, EqValidateReturnsTrue)
{
    int i = 1, j = 1;
    Validator v = eq(i, j);
    ASSERT_TRUE(v.validate());
}

TEST(TestValidator, EqDescription)
{
    int i = 1, j = 2;
    Validator v = eq(i, j);
    ASSERT_EQ(v.description(), "(1 == 2)");
}

} // end of namespace common
} // end of namespace mcdane
