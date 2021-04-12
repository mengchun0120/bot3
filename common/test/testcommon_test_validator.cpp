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

TEST(TestValidator, DefaultDescriptionIsEmpty)
{
    Validator v;
    ASSERT_EQ(v.description(), "");
}

} // end of namespace common
} // end of namespace mcdane
