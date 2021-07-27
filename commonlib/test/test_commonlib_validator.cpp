#include <gtest/gtest.h>
#include <commonlib_validator.h>

using namespace ::testing;

namespace mcdane {
namespace commonlib {

class TestValidator: public testing::Test {
public:
    Validator v_;
};

TEST_F(TestValidator, TestDefaultValidator)
{
    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "");
}

TEST_F(TestValidator, TestEq)
{
    int i = 1, j = 1;
    v_ = eq(i, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 == 1)");

    j = 3;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 == 3)");
}

TEST_F(TestValidator, TestNe)
{
    int i = 1, j = 2;
    v_ = ne(i, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 != 2)");

    j = 1;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 != 1)");
}

TEST_F(TestValidator, TestGt)
{
    int i = 3, j = 2;
    v_ = gt(i, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "(3 > 2)");

    j = 4;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "(3 > 4)");
}

TEST_F(TestValidator, TestGe)
{
    int i = 2, j = 1;
    v_ = ge(i, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "(2 >= 1)");

    j = 4;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "(2 >= 4)");
}

TEST_F(TestValidator, TestLt)
{
    int i = 1, j = 2;
    v_ = lt(i, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 < 2)");

    j = -1;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 < -1)");
}

TEST_F(TestValidator, TestLe)
{
    int i = 1, j = 2;
    v_ = le(i, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 <= 2)");

    j = -1;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "(1 <= -1)");
}

TEST_F(TestValidator, TestAnd)
{
    int i = 1, j = 2, k = 3;
    v_ = le(i, j) && gt(k, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "((1 <= 2) && (3 > 2))");

    i = 3;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "((3 <= 2) && (3 > 2))");
}

TEST_F(TestValidator, TestOr)
{
    int i = 1, j = 2, k = 3;
    v_ = lt(i, j) || eq(k, j);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "((1 < 2) || (3 == 2))");

    i = 3;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "((3 < 2) || (3 == 2))");
}

TEST_F(TestValidator, TestNot)
{
    int i = 1, j = 2;
    v_ = !lt(j, i);

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "!(2 < 1)");

    j = 0;
    EXPECT_FALSE(v_.validate());
    EXPECT_EQ(v_.description(), "!(0 < 1)");
}

TEST_F(TestValidator, TestComplexValidator)
{
    v_ = le(1, 2) && (ge(3, 2) || lt(1, 3));

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "((1 <= 2) && ((3 >= 2) || (1 < 3)))");
}

TEST_F(TestValidator, TestNonempty)
{
    v_ = nonempty(std::string("hello"));

    EXPECT_TRUE(v_.validate());
    EXPECT_EQ(v_.description(), "Non-empty");
}

} // end of namespace commonlib
} // end of namespace mcdane

