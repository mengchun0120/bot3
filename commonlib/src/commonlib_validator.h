#ifndef INCLUDED_COMMONLIB_VALIDATOR_H
#define INCLUDED_COMMONLIB_VALIDATOR_H

#include <string>
#include <functional>
#include <sstream>

namespace mcdane {
namespace commonlib {

class Validator {
public:
    using ValidateFunc = std::function<bool()>;
    using DescriptionFunc = std::function<std::string()>;

    Validator();

    Validator(ValidateFunc validateFunc,
              DescriptionFunc descFunc);

    bool validate() const;

    std::string description() const;

private:
    ValidateFunc validateFunc_;
    DescriptionFunc descFunc_;
};

template <typename T, typename F>
Validator eq(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return lhs == rhs;
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " == " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descFunc);
}

template <typename T, typename F>
Validator ne(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return lhs != rhs;
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " != " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descFunc);
}

template <typename T, typename F>
Validator gt(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return lhs > rhs;
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " > " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descFunc);
}

template <typename T, typename F>
Validator ge(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return lhs >= rhs;
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " >= " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descFunc);
}

template <typename T, typename F>
Validator lt(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return lhs < rhs;
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " < " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descFunc);
}

template <typename T, typename F>
Validator le(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return lhs <= rhs;
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " <= " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descFunc);
}

Validator operator&&(const Validator &lhs, const Validator &rhs);

Validator operator||(const Validator &lhs, const Validator &rhs);

Validator operator!(const Validator &v);

} // end of namespace commonlib
} // end of namespace mcdane

#endif

