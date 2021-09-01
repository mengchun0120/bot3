#include <cassert>
#include <commonlib_exception.h>
#include <commonlib_argument.h>

namespace mcdane {
namespace commonlib {

void testArgument_CreateWithValidArgsThrowNoException()
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        Argument arg = Argument::create(name, "name", "n", "name", "Name");
    }
    catch (const MyException& e)
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
        arg_ = Argument::create(name, "", "n", "name", "Name");
    }
    catch (const MyArgumentException &e)
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
        arg_ = Argument::create(name, "", "-n", "name", "Name");
    }
    catch (const MyException &e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testArgument, CreateWithInvalidLongOptThrowException()
{
    std::string name;
    bool exceptionHappened = false;

    try
    {
        Argument::Ptr arg = Argument::create(name, "", "n", "--name", "Name");
    }
    catch (const MyException& e)
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
        Arugment::Ptr arg = Argument::create(count, "count", "c", "count",
                                        "Count", true, gt(count, 0));
        arg->eval("123");
    }
    catch (const MyException& e)
    {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    assert(!exceptionHappened);
    assert(count == 123);
    assert(arg->specified());
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

