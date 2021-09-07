#include <algorithm>
#include <commonlib_validator.h>

namespace mcdane {
namespace commonlib {

Validator::Validator(ValidateFunc validateFunc,
                     DescriptionFunc descFunc):
    validateFunc_(validateFunc),
    descFunc_(descFunc)
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
    if (descFunc_)
    {
        return descFunc_();
    }

    return std::string();
}

Validator operator&&(const Validator& lhs, const Validator& rhs)
{
    Validator::ValidateFunc validateFunc = [=]()->bool
    {
        return lhs.validate() && rhs.validate();
    };

    Validator::DescriptionFunc descFunc = [=]()->std::string
    {
        return "(" + lhs.description() + " && " + rhs.description() + ")";
    };

    return Validator(validateFunc, descFunc);
}

Validator operator||(const Validator& lhs, const Validator& rhs)
{
    Validator::ValidateFunc validateFunc = [=]()->bool
    {
        return lhs.validate() || rhs.validate();
    };

    Validator::DescriptionFunc descFunc = [=]()->std::string
    {
        return "(" + lhs.description() + " || " + rhs.description() + ")";
    };

    return Validator(validateFunc, descFunc);
}

Validator operator!(const Validator& v)
{
    Validator::ValidateFunc validateFunc = [=]()->bool
    {
        return !v.validate();
    };

    Validator::DescriptionFunc descFunc = [=]()->std::string
    {
        return "!" + v.description();
    };

    return Validator(validateFunc, descFunc);

}

Validator check(const Color& color)
{
    Validator::ValidateFunc validateFunc = [&]()->bool
    {
        return std::all_of(color.begin(),
                           color.end(),
                           [=](float f)->bool
                           {
                                return f >= 0.0f && f <= 1.0f;
                           });
    };

    Validator::DescriptionFunc descFunc = [&]()->std::string
    {
        return "check(" + color.toString() + ")";
    };

    return Validator(validateFunc, descFunc);
}

} // end of namespace commonlib
} // end of namespace mcdane

