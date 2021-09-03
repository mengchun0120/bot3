#include <iostream>
#include <cassert>
#include <stdexcept>
#include <commonlib_argument.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testArgument_CreateWithValidArgsThrowNoException()
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        Argument::Ptr arg = Argument::create(name, "name", "n", "name", "Name");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(!exceptionHappened);
}

void testArgument_CreateWithEmptyNameThrowException()
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        Argument::Ptr arg = Argument::create(name, "", "n", "name", "Name");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgument_CreateWithInvalidShortOptionThrowException()
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        Argument::Ptr arg = Argument::create(name, "", "-n", "name", "Name");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgument_CreateWithInvalidLongOptThrowException()
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        Argument::Ptr arg = Argument::create(name, "", "n", "--name", "Name");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgument_EvalWithoutFailingValidationThrowsNoException()
{
    int count;

    try
    {
        Argument::Ptr arg = Argument::create(count, "count", "c", "count",
                                             "Count", true, gt(count, 0));
        arg->eval("123");
        assert(count == 123);
        assert(arg->specified());
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }
}

void testArgument_EvalWithFailingValidationThrowsException()
{
    int count;
    bool exceptionHappened = false;
    Argument::Ptr arg;

    try
    {
        arg = Argument::create(count, "count", "c", "count",
                               "Count", true, gt(count, 0));
    }
    catch (const MyException& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    try
    {
        arg->eval("0");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgument()
{
    testArgument_CreateWithValidArgsThrowNoException();
    testArgument_CreateWithEmptyNameThrowException();
    testArgument_CreateWithInvalidShortOptionThrowException();
    testArgument_CreateWithInvalidLongOptThrowException();
    testArgument_EvalWithoutFailingValidationThrowsNoException();
    testArgument_EvalWithFailingValidationThrowsException();
}

} // end of namespace commonlib
} // end of namespace mcdane

