#include <common_validator.h>

namespace mcdane {
namespace common {

Validator::Validator()
{
}

bool Validator::validate() const
{
    return true;
}

std::string Validator::description() const
{
    return std::string();
}

} // end of namespace common
} // end of namespace mcdane

