#include <iostream>
#include <cassert>
#include <stdexcept>
#include <commonlib_argument_parser.h>

namespace mcdane {
namespace commonlib {

void testArgumentParser_ValidInitThrowNoException();
void testArgumentParser_InitWithDuplicateShortOptionThrowsException();
void testArgumentParser_InitWithDuplicateNameThrowsException();
void testArgumentParser_InitWithDuplicateLongOptionThrowsException();
void testArgumentParser_ParseValidShortLongOptionThrowsNoException();
void testArgumentParser_ParseValidPositionArgThrowsNoException();

void testArgumentParser_ValidInitThrowNoException()
{
    std::string title, author;
    int count;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(count, "count", "", "", "Count"),
            Argument::create(title, "title", "t", "title", "Title"),
            Argument::create(author, "author", "a", "author", "Author", true)
        });
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgumentParser_InitWithDuplicateShortOptionThrowsException()
{
    int count, sum;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(count, "count", "c", "count", "Count"),
            Argument::create(sum, "sum", "c", "sum", "Sum")
        });
    }
    catch (const std::exception& e)
    {
        exceptionHappened = true;
        std::cerr << e.what() << std::endl;
    }

    assert(exceptionHappened);
}

void testArgumentParser_InitWithDuplicateNameThrowsException()
{
    int count, sum;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(count, "count", "c", "count", "Count"),
            Argument::create(sum, "count", "s", "sum", "Sum")
        });
    }
    catch (const std::exception& e)
    {
        exceptionHappened = true;
        std::cerr << e.what() << std::endl;
    }

    assert(exceptionHappened);
}


void testArgumentParser_InitWithDuplicateLongOptionThrowsException()
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
    catch (const std::exception& e)
    {
        exceptionHappened = true;
        std::cerr << e.what() << std::endl;
    }

    assert(exceptionHappened);
}

void testArgumentParser_ParseValidShortLongOptionThrowsNoException()
{
    std::string msg;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(msg, "message", "m", "message", "message")
        });

        const char * const argv1[] = {"cmd", "-m", "hello"};
        parser.parse(3, argv1);
        assert(msg == "hello");

        const char * const argv2[] = {"cmd", "--message", "taut"};
        parser.parse(3, argv2);
        assert(msg == "taut");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgumentParser_ParseValidPositionArgThrowsNoException()
{
    int i;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(i, "count")
        });

        const char * const argv[] = {"cmd", "123"};
        parser.parse(2, argv);
        assert(i == 123);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
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

