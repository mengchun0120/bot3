#include <test_commonlib.h>

int main(int argc, char *argv[])
{
    using namespace mcdane::commonlib;

    testArgument();
    testArgumentParser();
    testMyException();
    testFixedQueue();
    testJsonParam();
    testLog();
    testMatrix();
    testObjectPool();
    testValidator();
    testVector();
    testNamedMap();
    testLinkedList();
}
