#include <gtest/gtest.h>
#include <commonlib_exception.h>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

class TestArgument: public testing::Test {
public:
    Argument::Ptr arg_;
};

TEST_F(TestArgument, CreateWithValidArgsThrowNoException)
{
    std::string name;
    EXPECT_NO_THROW(arg_ = Argument::create(name, "name", "n", "name", "Name"));
}

TEST_F(TestArgument, CreateWithEmptyNameThrowException)
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        arg_ = Argument::create(name, "", "n", "name", "Name");
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgument, CreateWithInvalidShortOptionThrowException)
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        arg_ = Argument::create(name, "", "-n", "name", "Name");
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgument, CreateWithInvalidLongOptThrowException)
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        arg_ = Argument::create(name, "", "n", "--name", "Name");
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgument, EvalWithoutFailingValidationThrowsNoException)
{
    int count;

    ASSERT_NO_THROW(arg_ = Argument::create(count, "count", "c", "count",
                                            "Count", true, gt(count, 0)));
    ASSERT_NO_THROW(arg_->eval("123"));
    EXPECT_EQ(count, 123);
    EXPECT_TRUE(arg_->specified());
}

TEST_F(TestArgument, EvalWithFailingValidationThrowsException)
{
    int count;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(arg_ = Argument::create(count, "count", "c", "count",
                                            "Count", true, gt(count, 0)));

    try
    {
        arg_->eval("0");
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

} // end of namespace commonlib
} // end of namespace mcdane

