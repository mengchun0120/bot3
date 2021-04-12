#include <common_validator.h>

namespace mcdane {
namespace common {

Validator::Validator()
{
}

Validator::Validator(ValidateFunc validateFunc,
                     DescriptionFunc descriptionFunc):
    validateFunc_(validateFunc),
    descriptionFunc_(descriptionFunc)
{
}

bool Validator::validate() const
{
    if (validateFunc_)
    {
        return validateFunc_();
    }

    return true;
}

std::string Validator::description() const
{
    if (descriptionFunc_)
    {
        return descriptionFunc_();
    }

    return std::string();
}

} // end of namespace common
} // end of namespace mcdane

