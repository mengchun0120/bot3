#include <cassert>
#include <commonlib_validator.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testValidator_TestDefaultValidator()
{
    Validator<int> v;
    assert(v.validate(0));
    assert(v.description(0) == "");
}

void testValidator_TestEq()
{
    auto v = eq(1);

    assert(v.validate(1));
    assert(!v.validate(2));
    assert(v.description(1) == "(1 == 1)");
}

void testValidator_TestNe()
{
    auto v = ne(1);

    assert(v.validate(2));
    assert(!v.validate(1));
    assert(v.description(2) == "(2 != 1)");
}

void testValidator_TestGt()
{
    auto v = gt(0);

    assert(v.validate(3));
    assert(!v.validate(0));
    assert(v.description(3) == "(3 > 0)");
}

void testValidator_TestGe()
{
    auto v = ge(0);

    assert(v.validate(0));
    assert(v.validate(1));
    assert(!v.validate(-1));
    assert(v.description(2) == "(2 >= 0)");
}

void testValidator_TestLt()
{
    auto v = lt(2);

    assert(v.validate(1));
    assert(!v.validate(2));
    assert(v.description(1) == "(1 < 2)");
}

void testValidator_TestLe()
{
    auto v = le(2);

    assert(v.validate(2));
    assert(!v.validate(3));
    assert(v.description(1) == "(1 <= 2)");
}

void testValidator_TestAnd()
{
    auto v = le(2) && gt(0);

    assert(v.validate(1));
    assert(!v.validate(3));
    assert(v.description(1) == "((1 <= 2) && (1 > 0))");
}

void testValidator_TestOr()
{
    auto v = lt(1) || eq(2);

    assert(v.validate(2));
    assert(v.validate(0));
    assert(!v.validate(3));
    assert(v.description(1) == "((1 < 1) || (1 == 2))");
}

void testValidator_TestNot()
{
    auto v = !lt(1);

    assert(v.validate(1));
    assert(!v.validate(0));
    assert(v.description(2) == "!(2 < 1)");
}

void testValidator_TestComplexValidator()
{
    auto v = ge(0) && (eq(2) || lt(1));

    assert(v.validate(0));
    assert(v.validate(2));
    assert(!v.validate(4));
    assert(v.description(0) == "((0 >= 0) && ((0 == 2) || (0 < 1)))");
}

void testValidator_TestNonempty()
{
    auto v = nonempty<std::string>();

    assert(v.validate("hello"));
    assert(v.description("") == "Non-empty");
}

void testValidator()
{
    testValidator_TestDefaultValidator();
    testValidator_TestEq();
    testValidator_TestNe();
    testValidator_TestGt();
    testValidator_TestGe();
    testValidator_TestLt();
    testValidator_TestLe();
    testValidator_TestAnd();
    testValidator_TestOr();
    testValidator_TestNot();
    testValidator_TestComplexValidator();
    testValidator_TestNonempty();
}

} // end of namespace commonlib
} // end of namespace mcdane

