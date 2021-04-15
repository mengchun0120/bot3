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

TEST(TestValidator, Gt)
{
    int i = 3, j = 2;
    Validator v = Gt(i, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "(3 > 2)");
}

TEST(TestValidator, Ge)
{
    int i = 2, j = 1;
    Validator v = Ge(i, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "(2 >= 1)");
}

TEST(TestValidator, Lt)
{
    int i = 1, j = 2;
    Validator v = Lt(i, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "(1 < 2)");
}

TEST(TestValidator, Le)
{
    int i = 1, j = 2;
    Validator v = Le(i, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "(1 <= 2)");
}

TEST(TestValidator, And)
{
    int i = 1, j = 2, k = 3;
    Validator v = Le(i, j) && Gt(k, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "((1 <= 2) && (3 > 2))");
}

TEST(TestValidator, Or)
{
    int i = 1, j = 2, k = 3;
    Validator v = Lt(i, j) || Eq(k, j);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "((1 < 2) || (3 == 2))");
}

TEST(TestValidator, Not)
{
    int i = 1, j = 2;
    Validator v = !Lt(j, i);
    ASSERT_TRUE(v.Validate());
    ASSERT_EQ(v.Description(), "!(2 < 1)");
}

} // end of namespace commonlib
} // end of namespace mcdane
