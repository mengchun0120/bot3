#include <gtest/gtest.h>
#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

TEST(TestArgumentParser, InvalidArgumentForConstructor)
{
    int count, sum;
    EXPECT_THROW(ArgumentParser parser1({
                    Argument::Create(count, "count", "c", "count", "Count"),
                    Argument::Create(sum, "sum", "c", "sum", "Sum")
                 }),
                 InvalidArgumentException);

    EXPECT_THROW(ArgumentParser parser2({
                    Argument::Create(count, "count", "c", "count", "Count"),
                    Argument::Create(sum, "count", "s", "sum", "Sum")
                 }),
                 InvalidArgumentException);

    EXPECT_THROW(ArgumentParser parser3({
                    Argument::Create(count, "count", "c", "count", "Count"),
                    Argument::Create(sum, "count", "s", "count", "Sum")
                 }),
                 InvalidArgumentException);
}

TEST(TestArgumentParser, ValidOneArgument)
{
    std::string msg;
    ArgumentParser parser1({
        Argument::Create(msg, "message", "m", "message", "message")
    });

    const char * const argv1[] = {"cmd", "-m", "hello"};
    ASSERT_NO_THROW(parser1.Parse(3, argv1));
    EXPECT_EQ(msg, "hello");

    const char * const argv2[] = {"cmd", "--message", "taut"};
    ASSERT_NO_THROW(parser1.Parse(3, argv2));
    EXPECT_EQ(msg, "taut");

    int i;
    ArgumentParser parser2({
        Argument::Create(i, "count")
    });

    const char * const argv3[] = {"cmd", "123"};
    ASSERT_NO_THROW(parser2.Parse(2, argv3));
    EXPECT_EQ(i, 123);

    double d;
    ArgumentParser parser3({
        Argument::Create(d, "rate", "r")
    });

    const char * const argv4[] = {"cmd", "-r", "1.0"};
    ASSERT_NO_THROW(parser3.Parse(3, argv4));
    EXPECT_EQ(d, 1.0);
}

TEST(TestArgumentParser, ValidMultipleArguments)
{
    int count;
    std::string mode, name, file;
    float price;

    ArgumentParser parser1({
        Argument::Create(mode, "mode"),
        Argument::Create(count, "count", "c", "count", "Number of articles"),
        Argument::Create(name, "name", "n", "name", "Name of brand"),
        Argument::Create(price, "price", "p", "price", "Price of article"),
        Argument::Create(file, "file")
    });

    const char * const argv1[] = {"cmd", "add", "-n", "Dell", "--count", "100",
                                  "-p", "500.0", "output.csv"};
    ASSERT_NO_THROW(parser1.Parse(9, argv1));
    EXPECT_EQ(mode, "add");
    EXPECT_EQ(name, "Dell");
    EXPECT_EQ(count, 100);
    EXPECT_EQ(price, 500.0f);
    EXPECT_EQ(file, "output.csv");
}

TEST(TestArgumentParser, InvalidArgumentThrowException)
{
    std::string name;
    ArgumentParser parser1({
        Argument::Create(name, "name", "n", "name", "Name")
    });

    const char * const argv1[] = {"cmd", "-q"};
    EXPECT_THROW(parser1.Parse(0, argv1), InvalidArgumentException);
    EXPECT_THROW(parser1.Parse(2, argv1), InvalidArgumentException);

    const char * const argv2[] = {"cmd", "q", "msg"};
    EXPECT_THROW(parser1.Parse(3, argv2), InvalidArgumentException);

    std::string title;
    int id;
    ArgumentParser parser2({
        Argument::Create(title, "title", "t", "title", "Title of the book"),
        Argument::Create(id, "id", "i", "id", "ID of the book")
    });

    const char * const argv3[] = {"cmd", "--title", "Haven", "-t", "Zero"};
    EXPECT_THROW(parser2.Parse(5, argv3), InvalidArgumentException);

    const char * const argv4[] = {"cmd", "-q", "123456", "-t", "Jane"};
    EXPECT_THROW(parser2.Parse(5, argv4), InvalidArgumentException);
}

} // end of namespace commonlib
} // end of namespace mcdane

