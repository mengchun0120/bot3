#include <regex>
#include <commonlib_exception.h>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

bool Argument::validateName(const std::string &name)
{
    return validateName(name.c_str());
}

bool Argument::validateName(const char *name)
{
    static std::regex r("^\\w+$");
    return std::regex_match(name, r);
}

bool Argument::validateOpt(const std::string &opt)
{
    return validateOpt(opt.c_str());
}

bool Argument::validateOpt(const char *opt)
{
    static std::regex r("^\\w*$");
    return std::regex_match(opt, r);
}

Argument::Argument(const std::string &name,
                   const std::string &shortOpt,
                   const std::string &longOpt,
                   const std::string &description,
                   bool optional)
    : name_(name)
    , shortOpt_(shortOpt)
    , longOpt_(longOpt)
    , description_(description)
    , optional_(optional)
    , specified_(false)
{
    if (!validateName(name_))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid name");
    }

    if (!validateOpt(shortOpt_))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid shortOpt");
    }

    if (!validateOpt(longOpt_))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid longOpt");
    }

    if (isPosArg() && optional_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Position argument cannot be optional");
    }
}

void Argument::setSpecified(bool v) noexcept
{
    specified_ = v;
}

} // end of namespace commonlib
} // end of namespace mcdane

