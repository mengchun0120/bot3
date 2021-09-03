#include <iostream>
#include <cassert>
#include <stdexcept>
#include <commonlib_argument_parser.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

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
    ArgumentParser parser;

    try
    {
        parser.init({
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

void testArgumentParser_ParseValidMultipleNonOptionalArgsThrowsNoException()
{
    int count;
    std::string mode, name, file;
    float price;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(mode, "mode"),
            Argument::create(count, "count", "c", "count", ""),
            Argument::create(name, "name", "n", "name", ""),
            Argument::create(price, "price", "p", "price", ""),
            Argument::create(file, "file")
        });

        const char * const argv[] = {"cmd", "add", "-n", "Dell",
                                      "--count", "100",
                                      "-p", "500.0", "output.csv"};

        parser.parse(9, argv);

        assert(mode == "add");
        assert(name == "Dell");
        assert(count == 100);
        assert(price == 500.0f);
        assert(file == "output.csv");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgumentParser_ParseWithoutOptionalArgThrowsNoException()
{
    int count;
    double price;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(count, "count", "c", "count", "Count", true),
            Argument::create(price, "price", "p", "price", "Price")
        });

        const char * const argv[] = {"cmd", "-p", "12.0"};

        parser.parse(3, argv);
        assert(price == 12.0);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgumentParser_ParseWithoutOptionalArgLeavesReferenceUnchanged()
{
    std::string name;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(name, "name", "n", "name", "Name", true)
        });

        const char * const argv[] = {"cmd"};

        parser.parse(1, argv);

        assert(name == "");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgumentParser_ParseWithZeroArgcThrowsException()
{
    std::string name;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(name, "name", "n", "name", "Name")
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        const char * const argv[] = {"cmd"};
        parser.parse(0, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgumentParser_ParseWithUnknownShortOptThrowsException()
{
    std::string name;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(name, "name", "n", "name", "Name")
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        const char * const argv[] = {"cmd", "-q", "Jack"};
        parser.parse(3, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgumentParser_ParseWithUnknownLongOptThrowsException()
{
    std::string name;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(name, "name", "n", "name", "Name")
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        const char * const argv[] = {"cmd", "--manager", "Jack"};
        parser.parse(3, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgumentParser_ParseWithDuplicateOptThrowsException()
{
    std::string title;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(title, "title", "t", "title", "Title of the book"),
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        const char * const argv[] = {"cmd", "--title", "Haven", "-t", "Zero"};
        parser.parse(5, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgumentParser_ParseWithoutNonOptionalArgThrowsException()
{
    std::string title, author;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(title, "title", "t", "title", "Title"),
            Argument::create(author, "author", "a", "author", "Author", true)
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        const char * const argv[] = {"cmd", "-a", "Jane"};
        parser.parse(3, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgumentParser_ParseWithoutFailingValidationThrowsNoException()
{
    int count;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(count, "count", "c", "count", "Count",
                             true, gt(count, 0)),
        });

        const char * const argv[] = {"cmd", "-c", "100"};

        parser.parse(3, argv);
        assert(count == 100);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgumentParser_ParseWithFailingValidationThrowsException()
{
    int count;
    double price;
    bool exceptionHappened = false;
    ArgumentParser parser;

    try
    {
        parser.init({
            Argument::create(count, "count", "c", "count", "Count",
                             true, gt(count, 0)),
            Argument::create(price, "price", "p", "price", "Price",
                             true, gt(price, 0.0))
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        const char * const argv[] = {"cmd", "-c", "0"};
        parser.parse(3, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgumentParser()
{
    testArgumentParser_ValidInitThrowNoException();
    testArgumentParser_InitWithDuplicateShortOptionThrowsException();
    testArgumentParser_InitWithDuplicateNameThrowsException();
    testArgumentParser_InitWithDuplicateLongOptionThrowsException();
    testArgumentParser_ParseValidShortLongOptionThrowsNoException();
    testArgumentParser_ParseValidPositionArgThrowsNoException();
    testArgumentParser_ParseValidMultipleNonOptionalArgsThrowsNoException();
    testArgumentParser_ParseWithoutOptionalArgThrowsNoException();
    testArgumentParser_ParseWithoutOptionalArgLeavesReferenceUnchanged();
    testArgumentParser_ParseWithZeroArgcThrowsException();
    testArgumentParser_ParseWithUnknownShortOptThrowsException();
    testArgumentParser_ParseWithUnknownLongOptThrowsException();
    testArgumentParser_ParseWithDuplicateOptThrowsException();
    testArgumentParser_ParseWithoutNonOptionalArgThrowsException();
    testArgumentParser_ParseWithoutFailingValidationThrowsNoException();
    testArgumentParser_ParseWithFailingValidationThrowsException();
}

} // end of namespace commonlib
} // end of namespace mcdane

