#include <cassert>
#include <sstream>
#include <iostream>
#include <commonlib_matrix.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

class TestMatrix {
public:
    Matrix<2,3> m1_;
    Matrix<2,3> m2_;
    Matrix<3,2> m3_;
    Matrix4 m4_;
    Vector3 v1_;
    Vector2 v2_;
    Vector4 v4_;

    TestMatrix()
        : m1_{Vector3{1.0f, 2.0f, 3.0f}, Vector3{3.0f, 4.0f, 5.0f}}
        , m2_{Vector3{2.0f, 3.0f, 4.0f}, Vector3{4.0f, 5.0f, 6.0f}}
        , m3_{Vector2{1.0f, 2.0f}, Vector2{2.0f, 3.0f}, Vector2{3.0f, 4.0f}}
        , v1_{1.0f, 2.0f, 3.0f}
        , v2_{3.0f, 4.0f}
        , v4_{1.0f, 2.0f, 3.0f, 1.0f}
    {}
};

void testTestMatrix_MatrixPlusMatrix()
{
    TestMatrix t;

    Matrix<2,3> expected{
        Vector3{1.0f+2.0f, 2.0f+3.0f, 3.0f+4.0f},
        Vector3{3.0f+4.0f, 4.0f+5.0f, 5.0f+6.0f}
    };
    assert(t.m1_ + t.m2_ == expected);
}

void testMatrix_MatrixMinusMatrix()
{
    TestMatrix t;

    Matrix<2,3> expected{
        Vector3{1.0f-2.0f, 2.0f-3.0f, 3.0f-4.0f},
        Vector3{3.0f-4.0f, 4.0f-5.0f, 5.0f-6.0f}
    };
    assert(t.m1_ - t.m2_ == expected);
}

void testMatrix_FloatTimesMatrix()
{
    TestMatrix t;

    Matrix<2,3> expected{
        Vector3{1.0f*2.0f, 2.0f*2.0f, 3.0f*2.0f},
        Vector3{3.0f*2.0f, 4.0f*2.0f, 5.0f*2.0f}
    };
    assert(2.0f * t.m1_ == expected);
}

void testMatrix_MatrixTimesFloat()
{
    TestMatrix t;

    Matrix<2,3> expected{
        Vector3{1.0f*2.0f, 2.0f*2.0f, 3.0f*2.0f},
        Vector3{3.0f*2.0f, 4.0f*2.0f, 5.0f*2.0f}
    };
    assert(t.m1_ * 2.0f == expected);
}

void testMatrix_MatrixTimesVector()
{
    TestMatrix t;

    Vector2 expected{
        1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f,
        3.0f*1.0f + 4.0f*2.0f + 5.0f*3.0f
    };
    assert(t.m1_ * t.v1_ == expected);
}

void testMatrix_VectorTimesMatrix()
{
    TestMatrix t;

    Vector3 expected{
        3.0f*1.0f + 4.0f*3.0f,
        3.0f*2.0f + 4.0f*4.0f,
        3.0f*3.0f + 4.0f*5.0f
    };
    assert(t.v2_ * t.m1_ == expected);
}

void testMatrix_MatrixTimesMatrix()
{
    TestMatrix t;

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
    assert(t.m1_ * t.m3_ == expected);
}

void testMatrix_Translate()
{
    TestMatrix t;

    t.m4_ = translate(1.0f, 2.0f, 3.0f);
    Vector4 actual = t.m4_ * t.v4_;
    Vector4 expected{2.0f, 4.0f, 6.0f, 1.0f};
    assert(fuzzyEqual(actual, expected));
}

void testMatrix_RotateX()
{
    TestMatrix t;

    t.m4_ = rotateXDegree(90.0f);
    Vector4 actual = t.m4_ * t.v4_;
    Vector4 expected{1.0f, -3.0f, 2.0f, 1.0f};
    assert(fuzzyEqual(actual, expected));
}

void testMatrix_RotateY()
{
    TestMatrix t;

    t.m4_ = rotateYDegree(90.0f);
    Vector4 actual = t.m4_ * t.v4_;
    Vector4 expected{3.0f, 2.0f, -1.0f, 1.0f};
    assert(fuzzyEqual(actual, expected));
}

void testMatrix_RotateZ()
{
    TestMatrix t;

    t.m4_ = rotateZDegree(90.0f);
    Vector4 actual = t.m4_ * t.v4_;
    Vector4 expected{-2.0f, 1.0f, 3.0f, 1.0f};
    assert(fuzzyEqual(actual, expected));
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

void testMatrix_LookAt()
{
    Matrix4 m = lookAt(1.0f, 0.0f, 1.0f,
                       0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f);

    Vector4 v1{1.0f, 0.0f, 1.0f, 1.0f};
    Vector4 actual1 = m * v1;
    Vector4 expected1{0.0f, 0.0f, 0.0f, 1.0f};
    assert(fuzzyEqual(actual1, expected1));

    Vector4 v2{2.0f, 0.0f, 1.0f, 1.0f};
    Vector4 actual2 = m * v2;
    Vector4 expected2{0.70710678f, 0.0f, 0.70710678f, 1.0f};
    assert(fuzzyEqual(actual2, expected2));
}

void testMatrix()
{
    testMatrix_MatrixMinusMatrix();
    testMatrix_FloatTimesMatrix();
    testMatrix_MatrixTimesFloat();
    testMatrix_MatrixTimesVector();
    testMatrix_VectorTimesMatrix();
    testMatrix_MatrixTimesMatrix();
    testMatrix_Translate();
    testMatrix_RotateX();
    testMatrix_RotateY();
    testMatrix_RotateZ();
    testMatrix_LookAt();
}

} // end of namespace commonlib
} // end of namespace mcdane

