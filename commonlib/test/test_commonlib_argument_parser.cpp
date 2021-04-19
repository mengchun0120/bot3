#include <gtest/gtest.h>
#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

TEST(TestArgumentParser, ValidateNameOpt)
{
    const char * const argv[] = {"cmd"};
    ArgumentParser parser;

    EXPECT_NO_THROW(parser.Parse(1, argv));
    EXPECT_THROW(parser.Parse(0, argv), InvalidArgumentException);
}

TEST(TestArgumentParser, ParseOneArgument)
{
    std::string msg;
    ArgumentParser parser({
        Argument::Create(msg, "message", "m", "message", "message")
    });

    const char * const argv1[] = {"cmd", "-m", "hello"};
    EXPECT_NO_THROW(parser.Parse(3, argv1));
    EXPECT_EQ(msg, "hello");

    const char * const argv2[] = {"cmd", "--message", "taut"};
    EXPECT_NO_THROW(parser.Parse(3, argv2));
    EXPECT_EQ(msg, "taut");

    const char * const argv3[] = {"cmd", "-q"};
    EXPECT_THROW(parser.Parse(2, argv3), InvalidArgumentException);

    const char * const argv4[] = {"cmd", "q", "msg"};
    EXPECT_THROW(parser.Parse(3, argv4), InvalidArgumentException);
}

} // end of namespace commonlib
} // end of namespace mcdane

