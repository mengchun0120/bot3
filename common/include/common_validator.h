#ifndef INCLUDED_COMMON_VALIDATOR_H
#define INCLUDED_COMMON_VALIDATOR_H

namespace mcdane {
namespace common {

class Validator {
public:
    Validator();

    bool validate() const;
};

} // end of namespace common
} // end of namespace mcdane

#endif

