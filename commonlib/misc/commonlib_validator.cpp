#include <algorithm>
#include <commonlib_validator.h>

namespace mcdane {
namespace commonlib {

Validator<std::string> k_nonEmptyStrV = nonempty<std::string>();
Validator<std::vector<std::string>> k_nonEmptyStrVecV = nonEmptyVec<std::string>();
Validator<std::vector<int>> k_nonEmptyIntVecV = nonEmptyVec<int>();
Validator<std::vector<unsigned int>> k_nonEmptyUIntVecV = nonEmptyVec<unsigned int>();
Validator<std::vector<short>> k_nonEmptyShortVecV = nonEmptyVec<short>();
Validator<std::vector<long>> k_nonEmptyLongVecV = nonEmptyVec<long>();
Validator<std::vector<float>> k_nonEmptyFloatVecV = nonEmptyVec<float>();
Validator<std::vector<double>> k_nonEmptyDoubleVecV = nonEmptyVec<double>();

} // end of namespace commonlib
} // end of namespace mcdane

