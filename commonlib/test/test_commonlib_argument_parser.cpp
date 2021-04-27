#include <iostream>
#include <gtest/gtest.h>
#include <commonlib_exception.h>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

class TestArgumentParser: public ::testing::Test {
public:
    ArgumentParser parser_;
};

TEST_F(TestArgumentParser, ValidInitThrowNoException)
{
    std::string title, author;
    int count;

    EXPECT_NO_THROW(parser_.init({
        Argument::create(count, "count", "", "", "Count"),
        Argument::create(title, "title", "t", "title", "Title"),
        Argument::create(author, "author", "a", "author", "Author", true)
    }));
}

TEST_F(TestArgumentParser, InitWithDuplicateShortOptionThrowsException)
{
    int count, sum;
    bool exceptionHappened = false;

    try
    {
        parser_.init({
            Argument::create(count, "count", "c", "count", "Count"),
            Argument::create(sum, "sum", "c", "sum", "Sum")
        });
    }
    catch (const InvalidArgumentException &e)
    {
        exceptionHappened = true;
        std::cerr << e.what() << std::endl;
    }

    EXPECT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, InitWithDuplicateNameThrowsException)
{
    int count, sum;
    bool exceptionHappened = false;

    try
    {
        parser_.init({
            Argument::create(count, "count", "c", "count", "Count"),
            Argument::create(sum, "count", "s", "sum", "Sum")
        });
    }
    catch (const InvalidArgumentException &e)
    {
        exceptionHappened = true;
        std::cerr << e.what() << std::endl;
    }

    EXPECT_TRUE(exceptionHappened);
}


TEST_F(TestArgumentParser, InitWithDuplicateLongOptionThrowsException)
{
    int count, sum;
    bool exceptionHappened = false;

    try
    {
        parser_.init({
            Argument::create(count, "count", "c", "count", "Count"),
            Argument::create(sum, "count", "s", "count", "Sum")
        });
    }
    catch (const InvalidArgumentException &e)
    {
        exceptionHappened = true;
        std::cerr << e.what() << std::endl;
    }

    EXPECT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, ParseValidShortLongOptionThrowsNoException)
{
    std::string msg;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(msg, "message", "m", "message", "message")
    }));

    const char * const argv1[] = {"cmd", "-m", "hello"};
    EXPECT_NO_THROW(parser_.parse(3, argv1));
    EXPECT_EQ(msg, "hello");

    const char * const argv2[] = {"cmd", "--message", "taut"};
    EXPECT_NO_THROW(parser_.parse(3, argv2));
    EXPECT_EQ(msg, "taut");
}

TEST_F(TestArgumentParser, ParseValidPositionArgThrowsNoException)
{
    int i;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(i, "count")
    }));

    const char * const argv[] = {"cmd", "123"};
    ASSERT_NO_THROW(parser_.parse(2, argv));
    EXPECT_EQ(i, 123);
}

TEST_F(TestArgumentParser, ParseValidMultipleNonOptionalArgsThrowsNoException)
{
    int count;
    std::string mode, name, file;
    float price;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(mode, "mode"),
        Argument::create(count, "count", "c", "count", ""),
        Argument::create(name, "name", "n", "name", ""),
        Argument::create(price, "price", "p", "price", ""),
        Argument::create(file, "file")
    }));

    const char * const argv[] = {"cmd", "add", "-n", "Dell",
                                  "--count", "100",
                                  "-p", "500.0", "output.csv"};

    ASSERT_NO_THROW(parser_.parse(9, argv));
    EXPECT_EQ(mode, "add");
    EXPECT_EQ(name, "Dell");
    EXPECT_EQ(count, 100);
    EXPECT_EQ(price, 500.0f);
    EXPECT_EQ(file, "output.csv");
}

TEST_F(TestArgumentParser, ParseWithoutOptionalArgThrowsNoException)
{
    int count;
    double price;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(count, "count", "c", "count", "Count", true),
        Argument::create(price, "price", "p", "price", "Price")
    }));

    const char * const argv[] = {"cmd", "-p", "12.0"};
    ASSERT_NO_THROW(parser_.parse(3, argv));
    ASSERT_EQ(price, 12.0);
}

TEST_F(TestArgumentParser, ParseWithoutOptionalArgLeavesReferenceUnchanged)
{
    std::string name;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(name, "name", "n", "name", "Name", true)
    }));

    const char * const argv[] = {"cmd"};
    ASSERT_NO_THROW(parser_.parse(1, argv));
    EXPECT_EQ(name, "");
}

TEST_F(TestArgumentParser, ParseWithZeroArgcThrowsException)
{
    std::string name;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(name, "name", "n", "name", "Name")
    }));

    try
    {
        const char * const argv[] = {"cmd"};
        parser_.parse(0, argv);
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, ParseWithUnknownShortOptThrowsException)
{
    std::string name;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(name, "name", "n", "name", "Name")
    }));

    try
    {
        const char * const argv[] = {"cmd", "-q", "Jack"};
        parser_.parse(3, argv);
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, ParseWithUnknownLongOptThrowsException)
{
    std::string name;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(name, "name", "n", "name", "Name")
    }));

    try
    {
        const char * const argv[] = {"cmd", "--manager", "Jack"};
        parser_.parse(3, argv);
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, ParseWithDuplicateOptThrowsException)
{
    std::string title;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(title, "title", "t", "title", "Title of the book"),
    }));

    try
    {
        const char * const argv[] = {"cmd", "--title", "Haven", "-t", "Zero"};
        parser_.parse(5, argv);
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, ParseWithoutNonOptionalArgThrowsException)
{
    std::string title, author;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(title, "title", "t", "title", "Title"),
        Argument::create(author, "author", "a", "author", "Author", true)
    }));

    try
    {
        const char * const argv[] = {"cmd", "-a", "Jane"};
        parser_.parse(3, argv);
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    ASSERT_TRUE(exceptionHappened);
}

TEST_F(TestArgumentParser, ParseWithoutFailingValidationThrowsNoException)
{
    int count;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(count, "count", "c", "count", "Count",
                         true, gt(count, 0)),
    }));

    const char * const argv[] = {"cmd", "-c", "100"};

    ASSERT_NO_THROW(parser_.parse(3, argv));
    EXPECT_EQ(count, 100);
}

TEST_F(TestArgumentParser, ParseWithFailingValidationThrowsException)
{
    int count;
    double price;
    bool exceptionHappened = false;

    ASSERT_NO_THROW(parser_.init({
        Argument::create(count, "count", "c", "count", "Count",
                         true, gt(count, 0)),
        Argument::create(price, "price", "p", "price", "Price",
                         true, gt(price, 0.0))
    }));

    try
    {
        const char * const argv[] = {"cmd", "-c", "0"};
        parser_.parse(3, argv);
    }
    catch (const InvalidArgumentException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    EXPECT_TRUE(exceptionHappened);
}

} // end of namespace commonlib
} // end of namespace mcdane

