#include <cassert>
#include <sstream>
#include <iostream>
#include <commonlib_vector.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

class TestVector {
public:
    Vector3 v1_, v2_;

    TestVector():
        v1_{1.0f, 2.0f, 3.0f},
        v2_{2.0f, 2.0f, 3.0f}
    {}
};

void testVector_VectorPlusVector()
{
    TestVector t;

    Vector3 expected{3.0f, 4.0f, 6.0f};
    assert(t.v1_ + t.v2_ == expected);
}

void testVector_VectorMinusVector()
{
    TestVector t;

    Vector3 expected{-1.0f, 0.0f, 0.0f};
    assert(t.v1_ - t.v2_ == expected);
}

void testVector_FloatTimesVector()
{
    TestVector t;

    Vector3 expected{2.0f, 4.0f, 6.0f};
    assert(2.0f * t.v1_ == expected);
}

void testVector_VectorTimesFloat()
{
    TestVector t;

    Vector3 expected{2.0f, 4.0f, 6.0f};
    assert(t.v1_ * 2.0f == expected);
}

void testVector_VectorDividedByFloat()
{
    TestVector t;

    Vector3 expected{0.5f, 1.0f, 1.5f};
    assert(t.v1_ / 2.0f == expected);
}

void testVector_VectorDotVector()
{
    TestVector t;

    assert(dot(t.v1_, t.v2_) == 1.0f*2.0f + 2.0f*2.0f + 3.0f*3.0f);
}

void testVector_VectorCrossVector()
{
    TestVector t;

    Vector3 expected{
        2.0f*3.0f - 2.0f*3.0f,
        2.0f*3.0f - 1.0f*3.0f,
        1.0f*2.0f - 2.0f*2.0f
    };
    assert(cross(t.v1_, t.v2_) == expected);
}

void testVector_Normalize()
{
    TestVector t;

    t.v1_.normalize();
    float a = static_cast<float>(sqrt(14.0));
    Vector3 expected{1.0f/a, 2.0f/a, 3.0f/a};
    assert(fuzzyEqual(t.v1_, expected));
}

void testVector_OutVector()
{
    TestVector t;

    std::ostringstream out;
    out << t.v1_;
    std::cout << out.str() << std::endl;
    assert(out.str() == "[1, 2, 3]");
}

void testVector_InVector()
{
    TestVector t;

    std::istringstream in("1.0 2.0 3.0");
    Vector3 expected{1.0f, 2.0f, 3.0f};
    in >> t.v1_;
    assert(t.v1_ == expected);
}

void testVector()
{
    testVector_VectorPlusVector();
    testVector_VectorMinusVector();
    testVector_FloatTimesVector();
    testVector_VectorTimesFloat();
    testVector_VectorDividedByFloat();
    testVector_VectorDotVector();
    testVector_VectorCrossVector();
    testVector_Normalize();
    testVector_OutVector();
    testVector_InVector();
}

} // end of namespace commonlib
} // end of namespace mcdane

