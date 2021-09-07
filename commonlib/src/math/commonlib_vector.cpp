#include <commonlib_vector.h>

namespace mcdane {
namespace commonlib {

Vector3 cross(const Vector3 &lhs,
              const Vector3 &rhs)
{
    Vector3 v;
    v[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    v[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    v[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return v;
}

bool validate(const Color& c)
{
    for (int i = 0; i < 4; ++i)
    {
        if (c[i] < 0.0f || c[i] > 1.0f)
        {
            return false;
        }
    }

    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane

