#include <iostream>
#include <gtest/gtest.h>
#include <commonlib_validator.h>

using namespace ::testing;

namespace mcdane {
namespace commonlib {

TEST(TestValidator, TestDefaultValidator)
{
    Validator v;
    std::string desc = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc, "");
}

TEST(TestValidator, TestEq)
{
    int i = 1, j = 1;
    Validator v = eq(i, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "(1 == 1)");

    j = 3;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "(1 == 3)");
}

TEST(TestValidator, TestNe)
{
    int i = 1, j = 2;
    Validator v = ne(i, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "(1 != 2)");

    j = 1;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "(1 != 1)");
}

TEST(TestValidator, TestGt)
{
    int i = 3, j = 2;
    Validator v = gt(i, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "(3 > 2)");

    j = 4;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "(3 > 4)");
}

TEST(TestValidator, TestGe)
{
    int i = 2, j = 1;
    Validator v = ge(i, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "(2 >= 1)");

    j = 4;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "(2 >= 4)");
}

TEST(TestValidator, TestLt)
{
    int i = 1, j = 2;
    Validator v = lt(i, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "(1 < 2)");

    j = -1;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "(1 < -1)");
}

TEST(TestValidator, TestLe)
{
    int i = 1, j = 2;
    Validator v = le(i, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "(1 <= 2)");

    j = -1;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "(1 <= -1)");
}

TEST(TestValidator, TestAnd)
{
    int i = 1, j = 2, k = 3;
    Validator v = le(i, j) && gt(k, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "((1 <= 2) && (3 > 2))");

    i = 3;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "((3 <= 2) && (3 > 2))");
}

TEST(TestValidator, TestOr)
{
    int i = 1, j = 2, k = 3;
    Validator v = lt(i, j) || eq(k, j);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "((1 < 2) || (3 == 2))");

    i = 3;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "((3 < 2) || (3 == 2))");
}

TEST(TestValidator, TestNot)
{
    int i = 1, j = 2;
    Validator v = !lt(j, i);
    std::string desc1 = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc1, "!(2 < 1)");

    j = 0;
    std::string desc2 = v.description();

    EXPECT_FALSE(v.validate());
    EXPECT_EQ(desc2, "!(0 < 1)");
}

TEST(TestValidator, TestComplexValidator)
{
    Validator v = le(1, 2) && (ge(3, 2) || lt(1, 2));
    std::string desc = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc, "((1 <= 2) && ((3 >= 2) || (1 < 2)))");
}

TEST(TestValidator, TestNonempty)
{
    Validator v = nonempty(std::string("hello"));
    std::string desc = v.description();

    EXPECT_TRUE(v.validate());
    EXPECT_EQ(desc, "Non-empty");
}

} // end of namespace commonlib
} // end of namespace mcdane

