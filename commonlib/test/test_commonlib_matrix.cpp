#include <sstream>
#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest_pred_impl.h>
#include <commonlib_matrix.h>

namespace mcdane {
namespace commonlib {

class TestMatrix: public ::testing::Test {
public:
    Matrix<2,3> m1_;
    Matrix<2,3> m2_;
    Matrix<3,2> m3_;
    Matrix4 m4_;
    Vector3 v1_;
    Vector2 v2_;
    Vector4 v4_;

    TestMatrix():
        m1_{Vector3{1.0f, 2.0f, 3.0f}, Vector3{3.0f, 4.0f, 5.0f}},
        m2_{Vector3{2.0f, 3.0f, 4.0f}, Vector3{4.0f, 5.0f, 6.0f}},
        m3_{Vector2{1.0f, 2.0f}, Vector2{2.0f, 3.0f}, Vector2{3.0f, 4.0f}},
        v1_{1.0f, 2.0f, 3.0f},
        v2_{3.0f, 4.0f},
        v4_{1.0f, 2.0f, 3.0f, 1.0f}
    {}
};

TEST_F(TestMatrix, MatrixPlusMatrix)
{
    Matrix<2,3> expected{
        Vector3{1.0f+2.0f, 2.0f+3.0f, 3.0f+4.0f},
        Vector3{3.0f+4.0f, 4.0f+5.0f, 5.0f+6.0f}
    };
    EXPECT_EQ(m1_ + m2_, expected);
}

TEST_F(TestMatrix, MatrixMinusMatrix)
{
    Matrix<2,3> expected{
        Vector3{1.0f-2.0f, 2.0f-3.0f, 3.0f-4.0f},
        Vector3{3.0f-4.0f, 4.0f-5.0f, 5.0f-6.0f}
    };
    EXPECT_EQ(m1_ - m2_, expected);
}

TEST_F(TestMatrix, FloatTimesMatrix)
{
    Matrix<2,3> expected{
        Vector3{1.0f*2.0f, 2.0f*2.0f, 3.0f*2.0f},
        Vector3{3.0f*2.0f, 4.0f*2.0f, 5.0f*2.0f}
    };
    EXPECT_EQ(2.0f * m1_, expected);
}

TEST_F(TestMatrix, MatrixTimesFloat)
{
    Matrix<2,3> expected{
        Vector3{1.0f*2.0f, 2.0f*2.0f, 3.0f*2.0f},
        Vector3{3.0f*2.0f, 4.0f*2.0f, 5.0f*2.0f}
    };
    EXPECT_EQ(m1_ * 2.0f, expected);
}

TEST_F(TestMatrix, MatrixTimesVector)
{
    Vector2 expected{
        1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f,
        3.0f*1.0f + 4.0f*2.0f + 5.0f*3.0f
    };
    EXPECT_EQ(m1_ * v1_, expected);
}

TEST_F(TestMatrix, VectorTimesMatrix)
{
    Vector3 expected{
        3.0f*1.0f + 4.0f*3.0f,
        3.0f*2.0f + 4.0f*4.0f,
        3.0f*3.0f + 4.0f*5.0f
    };
    EXPECT_EQ(v2_ * m1_, expected);
}

TEST_F(TestMatrix, MatrixTimesMatrix)
{
    Matrix2 expected{
        Vector2{
            1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f,
            1.0f*2.0f + 2.0f*3.0f + 3.0f*4.0f
        },
        Vector2{
            3.0f*1.0f + 4.0f*2.0f + 5.0f*3.0f,
            3.0f*2.0f + 4.0f*3.0f + 5.0f*4.0f
        }
    };
    EXPECT_EQ(m1_ * m3_, expected);
}

TEST_F(TestMatrix, Translate)
{
    m4_ = translate(1.0f, 2.0f, 3.0f);
    Vector4 actual = m4_ * v4_;
    Vector4 expected{2.0f, 4.0f, 6.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual, expected));
}

TEST_F(TestMatrix, RotateX)
{
    m4_ = rotateXDegree(90.0f);
    Vector4 actual = m4_ * v4_;
    Vector4 expected{1.0f, -3.0f, 2.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual, expected));
}

TEST_F(TestMatrix, RotateY)
{
    m4_ = rotateYDegree(90.0f);
    Vector4 actual = m4_ * v4_;
    Vector4 expected{3.0f, 2.0f, -1.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual, expected));
}

TEST_F(TestMatrix, RotateZ)
{
    m4_ = rotateZDegree(90.0f);
    Vector4 actual = m4_ * v4_;
    Vector4 expected{-2.0f, 1.0f, 3.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual, expected));
}

/*
TEST_F(TestMatrix, Rotate)
{
    Mat4 m1 = rotateDegree(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 180.0f);
    Vec4 v1{1.0f, 0.0f, 0.0f, 1.0f};
    Vec4 actual1 = m1 * v1;
    Vec4 expected1{0.0f, 1.0f, 0.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual1, expected1));
    Mat4 m2 = rotateDegree(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 180.0f);
    Vec4 v2{0.0f, 1.0f, 0.0f, 1.0f};
    Vec4 actual2 = m2 * v2;
    Vec4 expected2{0.0f, 0.0f, 1.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual2, expected2));
    Mat4 m3 = rotateDegree(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 120.0f);
    Vec4 v3{0.0f, 0.0f, 1.0f, 1.0f};
    Vec4 actual3 = m3 * v3;
    Vec4 expected3{1.0f, 0.0f, 0.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual3, expected3));
}
*/

TEST_F(TestMatrix, LookAt)
{
    Matrix4 m = lookAt(1.0f, 0.0f, 1.0f,
                       0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f);
    std::cout << "matrix=" << m << std::endl;

    Vector4 v1{1.0f, 0.0f, 1.0f, 1.0f};
    Vector4 actual1 = m * v1;
    Vector4 expected1{0.0f, 0.0f, 0.0f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual1, expected1));

    Vector4 v2{2.0f, 0.0f, 1.0f, 1.0f};
    Vector4 actual2 = m * v2;
    std::cout << actual2 << std::endl;
    Vector4 expected2{0.70710678f, 0.0f, 0.70710678f, 1.0f};
    EXPECT_TRUE(fuzzyEqual(actual2, expected2));
}

} // end of namespace commonlib
} // end of namespace mcdane

