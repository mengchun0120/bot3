#include <cassert>
#include <commonlib_validator.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testValidator_TestDefaultValidator()
{
    Validator v;
    std::string desc = v.description();

    assert(v.validate());
    assert(desc == "");
}

void testValidator_TestEq()
{
    int i = 1, j = 1;
    Validator v = eq(i, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "(1 == 1)");

    j = 3;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "(1 == 3)");
}

void testValidator_TestNe()
{
    int i = 1, j = 2;
    Validator v = ne(i, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "(1 != 2)");

    j = 1;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "(1 != 1)");
}

void testValidator_TestGt()
{
    int i = 3, j = 2;
    Validator v = gt(i, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "(3 > 2)");

    j = 4;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "(3 > 4)");
}

void testValidator_TestGe()
{
    int i = 2, j = 1;
    Validator v = ge(i, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "(2 >= 1)");

    j = 4;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "(2 >= 4)");
}

void testValidator_TestLt()
{
    int i = 1, j = 2;
    Validator v = lt(i, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "(1 < 2)");

    j = -1;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "(1 < -1)");
}

void testValidator_TestLe()
{
    int i = 1, j = 2;
    Validator v = le(i, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "(1 <= 2)");

    j = -1;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "(1 <= -1)");
}

void testValidator_TestAnd()
{
    int i = 1, j = 2, k = 3;
    Validator v = le(i, j) && gt(k, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "((1 <= 2) && (3 > 2))");

    i = 3;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "((3 <= 2) && (3 > 2))");
}

void testValidator_TestOr()
{
    int i = 1, j = 2, k = 3;
    Validator v = lt(i, j) || eq(k, j);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "((1 < 2) || (3 == 2))");

    i = 3;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "((3 < 2) || (3 == 2))");
}

void testValidator_TestNot()
{
    int i = 1, j = 2;
    Validator v = !lt(j, i);
    std::string desc1 = v.description();

    assert(v.validate());
    assert(desc1 == "!(2 < 1)");

    j = 0;
    std::string desc2 = v.description();

    assert(!v.validate());
    assert(desc2 == "!(0 < 1)");
}

void testValidator_TestComplexValidator()
{
    Validator v = le(1, 2) && (ge(3, 2) || lt(1, 2));
    std::string desc = v.description();

    assert(v.validate());
    assert(desc == "((1 <= 2) && ((3 >= 2) || (1 < 2)))");
}

void testValidator_TestNonempty()
{
    Validator v = nonempty(std::string("hello"));
    std::string desc = v.description();

    assert(v.validate());
    assert(desc == "Non-empty");
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

