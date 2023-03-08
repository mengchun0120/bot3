#include <iostream>
#include <test_commonlib.h>

int main(int argc, char *argv[])
{
    using namespace mcdane::commonlib;

    testArgument();
    testArgumentParser();
    testMyException();
    testFileUtils();
    testFixedQueue();
    testJsonParam();
    testLog();
    testMatrix();
    testObjectPool();
    testValidator();
    testVector();
    testNamedMap();
    testLinkedList();
    testCollide();
    testRegion();

    std::cout << "Test successful" << std::endl;
}
