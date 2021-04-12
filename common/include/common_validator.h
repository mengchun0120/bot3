#ifndef INCLUDED_COMMON_VALIDATOR_H
#define INCLUDED_COMMON_VALIDATOR_H

#include <string>

namespace mcdane {
namespace common {

class Validator {
public:
    Validator();

    bool validate() const;

    std::string description() const;
};

} // end of namespace common
} // end of namespace mcdane

#endif

