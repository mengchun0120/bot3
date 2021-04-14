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

} // end of namespace commonlib
} // end of namespace mcdane

