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
              DescriptionFunc descriptionFunc);

    bool validate() const;

    std::string description() const;

private:
    ValidateFunc validateFunc_;
    DescriptionFunc descriptionFunc_;
};

template <typename T, typename F>
Validator eq(const T &lhs, const F &rhs)
{
    Validator::ValidateFunc validateFunc = [=]()->bool
    {
        return lhs == rhs;
    };

    Validator::DescriptionFunc descriptionFunc = [=]()->std::string
    {
        std::ostringstream oss;
        oss << "(" << lhs << " == " << rhs << ")";
        return oss.str();
    };

    return Validator(validateFunc, descriptionFunc);
}

} // end of namespace commonlib
} // end of namespace mcdane

#endif

