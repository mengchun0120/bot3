#include <regex>
#include <commonlib_exception.h>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

bool Argument::ValidateName(const std::string &name)
{
    static std::regex r("^\\w+$");
    return std::regex_match(name, r);
}

bool Argument::ValidateOpt(const std::string &opt)
{
    static std::regex r("^\\w*$");
    return std::regex_match(opt, r);
}

Argument::Argument(const std::string &name,
                   const std::string &short_opt,
                   const std::string &long_opt,
                   const std::string &description):
    name_(name),
    short_opt_(short_opt),
    long_opt_(long_opt),
    description_(description)
{
    if (!ValidateName(name_))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid name");
    }

    if (!ValidateOpt(short_opt_))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid short_opt");
    }

    if (!ValidateOpt(long_opt_))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid long_opt");
    }
}

} // end of namespace commonlib
} // end of namespace mcdane

