#include <commonlib_validator.h>

namespace mcdane {
namespace commonlib {

Validator::Validator()
{
}

Validator::Validator(ValidateFunc validate_func,
                     DescriptionFunc description_func):
    validate_func_(validate_func),
    description_func_(description_func)
{
}

bool Validator::Validate() const
{
    if (validate_func_)
    {
        return validate_func_();
    }

    return true;
}

std::string Validator::Description() const
{
    if (description_func_)
    {
        return description_func_();
    }

    return std::string();
}

Validator operator&&(const Validator &lhs, const Validator &rhs)
{
    Validator::ValidateFunc validate_func = [=]()->bool
    {
        return lhs.Validate() && rhs.Validate();
    };

    Validator::DescriptionFunc description_func = [=]()->std::string
    {
        return "(" + lhs.Description() + " && " + rhs.Description() + ")";
    };

    return Validator(validate_func, description_func);
}

Validator operator||(const Validator &lhs, const Validator &rhs)
{
    Validator::ValidateFunc validate_func = [=]()->bool
    {
        return lhs.Validate() || rhs.Validate();
    };

    Validator::DescriptionFunc description_func = [=]()->std::string
    {
        return "(" + lhs.Description() + " || " + rhs.Description() + ")";
    };

    return Validator(validate_func, description_func);
}

Validator operator!(const Validator &v)
{
    Validator::ValidateFunc validate_func = [=]()->bool
    {
        return !v.Validate();
    };

    Validator::DescriptionFunc description_func = [=]()->std::string
    {
        return "!" + v.Description();
    };

    return Validator(validate_func, description_func);

}

} // end of namespace commonlib
} // end of namespace mcdane

