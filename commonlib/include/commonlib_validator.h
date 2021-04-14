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

    Validator(ValidateFunc validate_func,
              DescriptionFunc description_func);

    bool Validate() const;

    std::string Description() const;

private:
    ValidateFunc validate_func_;
    DescriptionFunc description_func_;
};

template <typename T, typename F>
Validator Eq(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validate_func = [&]()->bool
    {
        return lhs == rhs;
    };

    Validator::DescriptionFunc description_func = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " == " << rhs << ")";
        return oss.str();
    };

    return Validator(validate_func, description_func);
}

template <typename T, typename F>
Validator Ne(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validate_func = [&]()->bool
    {
        return lhs != rhs;
    };

    Validator::DescriptionFunc description_func = [&]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " != " << rhs << ")";
        return oss.str();
    };

    return Validator(validate_func, description_func);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

