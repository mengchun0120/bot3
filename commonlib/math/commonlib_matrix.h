#ifndef INCLUDED_COMMONLIB_MATRIX_H
#define INCLUDED_COMMONLIB_MATRIX_H

#include <commonlib_vector.h>

namespace mcdane {
namespace commonlib {

template <std::size_t M, std::size_t N>
struct Matrix: public std::array<Vector<N>, M> {
    Matrix() = default;

    Matrix(const Matrix &other) = default;

    Matrix(std::initializer_list<Vector<N>> l) noexcept;

    Matrix &negate() noexcept;

    Matrix &fill(float f) noexcept;

    Matrix<N, M> transpose() const noexcept;

    Matrix &operator+=(const Matrix &m) noexcept;

    Matrix &operator-=(const Matrix &m) noexcept;

    Matrix &operator*=(float f) noexcept;

    Matrix &operator/=(float f) noexcept;
};

using Matrix2 = Matrix<2, 2>;
using Matrix3 = Matrix<3, 3>;
using Matrix4 = Matrix<4, 4>;

template <std::size_t M, std::size_t N>
Matrix<M, N>::Matrix(std::initializer_list<Vector<N>> l) noexcept
{
    auto it = this->begin();
    for (auto i = l.begin(); it != this->end() && i != l.end(); ++it, ++i)
    {
        *it = *i;
    }
}

template <std::size_t M, std::size_t N>
Matrix<M, N> &Matrix<M, N>::negate() noexcept
{
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        it->negate();
    }
    return *this;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> &Matrix<M, N>::fill(float f) noexcept
{
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        it->fill(f);
    }
    return *this;
}

template <std::size_t M, std::size_t N>
Matrix<N, M> Matrix<M, N>::transpose() const noexcept
{
    Matrix<N, M> r;
    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = 0; j < M; ++j)
        {
            r[i][j] = (*this)[j][i];
        }
    }
    return r;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> &Matrix<M, N>::operator+=(const Matrix &m) noexcept
{
    auto it = this->begin();
    for (auto i = m.cbegin(); it != this->end() && i != m.cend(); ++it, ++i)
    {
        *it += *i;
    }
    return *this;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> &Matrix<M, N>::operator-=(const Matrix &m) noexcept
{
    auto it = this->begin();
    for (auto i = m.cbegin(); it != this->end() && i != m.cend(); ++it, ++i)
    {
        *it -= *i;
    }
    return *this;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> &Matrix<M, N>::operator*=(float f) noexcept
{
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        *it *= f;
    }
    return *this;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> &Matrix<M, N>::operator/=(float f) noexcept
{
    return (*this) *= (1.0f / f);
}

template <std::size_t M>
Matrix<M, M> identityMatrix()
{
    Matrix<M, M> r;
    r.fill(0.0f);
    for (std::size_t i = 0; i < M; ++i)
    {
        r[i][i] = 1.0f;
    }
    return r;
}


template <std::size_t M, std::size_t N>
bool fuzzyEqual(const Matrix<M, N> &m1,
                const Matrix<M, N> &m2,
                float threshold=1e-6f)
{
    for (std::size_t i = 0; i < M; ++i)
    {
        if (!fuzzyEqual(m1[i], m2[i], threshold))
        {
            return false;
        }
    }

    return true;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> operator+(const Matrix<M, N> &lhs,
                       const Matrix<M, N> &rhs)
{
    Matrix<M, N> m;
    for (std::size_t i = 0; i < M; ++i)
    {
        m[i] = lhs[i] + rhs[i];
    }
    return m;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> operator-(const Matrix<M, N> &lhs,
                       const Matrix<M, N> &rhs)
{
    Matrix<M, N> m;
    for (std::size_t i = 0; i < M; ++i)
    {
        m[i] = lhs[i] - rhs[i];
    }
    return m;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> operator*(const Matrix<M, N> &lhs,
                       float rhs)
{
    Matrix<M, N> m;
    for (std::size_t i = 0; i < M; ++i)
    {
        m[i] = lhs[i] * rhs;
    }
    return m;
}

template <std::size_t M, std::size_t N>
Matrix<M, N> operator*(float f,
                       const Matrix<M, N> &rhs)
{
    return rhs * f;
}

template <std::size_t M, std::size_t N>
Vector<M> operator*(const Matrix<M, N> &lhs,
                    const Vector<N> &rhs)
{
    Vector<M> v;
    for (std::size_t i = 0; i < M; ++i)
    {
        float s = 0.0f;
        for (std::size_t j = 0; j < N; ++j)
        {
            s += lhs[i][j] * rhs[j];
        }
        v[i] = s;
    }
    return v;
}

template <std::size_t M, std::size_t N>
Vector<N> operator*(const Vector<M> &lhs,
                    const Matrix<M, N> &rhs)
{
    Vector<N> v;
    for (std::size_t i = 0; i < N; ++i)
    {
        float s = 0.0f;
        for (std::size_t j = 0; j < M; ++j)
        {
            s += lhs[j] * rhs[j][i];
        }
        v[i] = s;
    }
    return v;
}

template <std::size_t M, std::size_t N, std::size_t P>
Matrix<M, P> operator*(const Matrix<M, N> &lhs,
                       const Matrix<N, P> &rhs)
{
    Matrix<M, P> m;
    for (std::size_t i = 0; i < M; ++i)
    {
        m[i] = lhs[i] * rhs;
    }
    return m;
}

Matrix4 translate(float dx,
                  float dy,
                  float dz);

Matrix4 rotateXCosSin(float cosTheta,
                      float sinTheta);

Matrix4 rotateXRad(float theta);

Matrix4 rotateXDegree(float degree);

Matrix4 rotateYCosSin(float cosTheta,
                      float sinTheta);

Matrix4 rotateYRad(float theta);

Matrix4 rotateYDegree(float degree);

Matrix4 rotateZCosSin(float cosTheta,
                      float sinTheta);

Matrix4 rotateZRad(float theta);

Matrix4 rotateZDegree(float degree);

Matrix4 rotateCosSin(float x,
                     float y,
                     float z,
                     float dx,
                     float dy,
                     float dz,
                     float cosTheta,
                     float sinTheta);

Matrix4 rotateTheta(float x,
                    float y,
                    float z,
                    float dx,
                    float dy,
                    float dz,
                    float theta);

Matrix4 rotateDegree(float x,
                     float y,
                     float z,
                     float dx,
                     float dy,
                     float dz,
                     float degree);

Matrix4 scale(float sx,
              float sy,
              float sz);

Matrix4 lookAt(const Vector3 &eye,
               const Vector3 &at,
               const Vector3 &up);

Matrix4 lookAt(float eyex,
               float eyey,
               float eyez,
               float atx,
               float aty,
               float atz,
               float upx,
               float upy,
               float upz);

Matrix4 ortho(float left,
              float right,
              float bottom,
              float top,
              float near,
              float far);

Matrix4 frustum(float left,
                float right,
                float bottom,
                float top,
                float near,
                float far);

} // end of namespace commonlib
} // end of namespace mcdnae

namespace std {

template <std::size_t M, std::size_t N>
std::ostream &operator<<(std::ostream& out,
                         const mcdane::commonlib::Matrix<M, N> &m)
{
    out << '[';
    if (M > 0)
    {
        out << m[0];
        for (std::size_t i = 1; i < M; ++i)
        {
            out << ", " << m[i];
        }
    }
    out << ']';

    return out;
}

template <std::size_t M, std::size_t N>
std::istream &operator>>(std::istream& in,
                         mcdane::commonlib::Matrix<M, N> &m)
{
    for (std::size_t i = 0; in.good() && i < M; ++i)
    {
        in >> m[i];
    }
    return in;
}

} // end of namespace std

#endif
