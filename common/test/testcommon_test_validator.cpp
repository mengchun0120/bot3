#include <gtest/gtest.h>
#include <common_validator.h>

using namespace ::testing;

namespace mcdane {
namespace common {

TEST(TestValidator, DefaultValidatorEvaluateToTrue)
{
    Validator v;
    ASSERT_TRUE(v.validate());
}

} // end of namespace common
} // end of namespace mcdane
