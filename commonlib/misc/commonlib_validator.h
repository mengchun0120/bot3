#ifndef INCLUDED_COMMONLIB_VALIDATOR_H
#define INCLUDED_COMMONLIB_VALIDATOR_H

#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <iostream>
#include <commonlib_color.h>

namespace mcdane {
namespace commonlib {

template <typename T>
class Validator {
public:
    using ValidateFunc = std::function<bool(const T&)>;
    using DescriptionFunc = std::function<std::string(const T&)>;

    Validator() = default;

    Validator(const Validator &other) = default;

    Validator(ValidateFunc validateFunc,
              DescriptionFunc descFunc);

    bool validate(const T &v) const;

    std::string description(const T &v) const;

private:
    ValidateFunc validateFunc_;
    DescriptionFunc descFunc_;
};

extern Validator<std::string> k_nonEmptyStrV;
extern Validator<std::vector<std::string>> k_nonEmptyStrVecV;
extern Validator<std::vector<int>> k_nonEmptyIntVecV;
extern Validator<std::vector<unsigned int>> k_nonEmptyUIntVecV;
extern Validator<std::vector<short>> k_nonEmptyShortVecV;
extern Validator<std::vector<long>> k_nonEmptyLongVecV;
extern Validator<std::vector<float>> k_nonEmptyFloatVecV;
extern Validator<std::vector<double>> k_nonEmptyDoubleVecV;
extern Validator<Color> k_colorV;

template <typename T>
Validator<T>::Validator(ValidateFunc validateFunc,
                        DescriptionFunc descFunc)
    : validateFunc_(validateFunc)
    , descFunc_(descFunc)
{
}

template <typename T>
bool Validator<T>::validate(const T &v) const
{
    if (validateFunc_)
    {
        return validateFunc_(v);
    }

    return true;
}

template <typename T>
std::string Validator<T>::description(const T &v) const
{
    if (descFunc_)
    {
        return descFunc_(v);
    }

    return "";
}

template <typename T>
Validator<T> eq(const T &rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &lhs)->bool
    {
        return lhs == rhs;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &lhs)->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " == " << rhs << ")";
        return oss.str();
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> ne(const T &rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &lhs)->bool
    {
        return lhs != rhs;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &lhs)->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " != " << rhs << ")";
        return oss.str();
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> gt(const T &rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &lhs)->bool
    {
        return lhs > rhs;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &lhs)->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " > " << rhs << ")";
        return oss.str();
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> ge(const T &rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &lhs)->bool
    {
        return lhs >= rhs;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &lhs)->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " >= " << rhs << ")";
        return oss.str();
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> lt(const T &rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &lhs)->bool
    {
        return lhs < rhs;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &lhs)->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " < " << rhs << ")";
        return oss.str();
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> le(const T &rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &lhs)->bool
    {
        return lhs <= rhs;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &lhs)->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " <= " << rhs << ")";
        return oss.str();
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> nonempty()
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &t)->bool
    {
        return t.size() > 0;
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &t)->std::string
    {
        return "Non-empty";
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<std::vector<T>> nonEmptyVec()
{
    return nonempty<std::vector<T>>();
}

template <typename T>
Validator<T> operator&&(const Validator<T> &lhs, const Validator<T>& rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &t)->bool
    {
        return lhs.validate(t) && rhs.validate(t);
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &t)->std::string
    {
        return "(" + lhs.description(t) + " && " + rhs.description(t) + ")";
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> operator||(const Validator<T> &lhs, const Validator<T>& rhs)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &t)->bool
    {
        return lhs.validate(t) || rhs.validate(t);
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &t)->std::string
    {
        return "(" + lhs.description(t) + " || " + rhs.description(t) + ")";
    };

    return Validator<T>(validateFunc, descFunc);
}

template <typename T>
Validator<T> operator!(const Validator<T> &v)
{
    typename Validator<T>::ValidateFunc validateFunc = [=](const T &t)->bool
    {
        return !v.validate(t);
    };

    typename Validator<T>::DescriptionFunc descFunc = [=](const T &t)->std::string
    {
        return "!" + v.description(t);
    };

    return Validator<T>(validateFunc, descFunc);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

