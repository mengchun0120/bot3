#include <cassert>
#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_object_pool.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testObjectPool_InvalidSizeThrowException()
{
    bool exceptionHappened = false;

    try
    {
        ObjectPool<int> pool(0);
    }
    catch (const InvalidArgumentException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testObjectPool_FreeCountDecreaseAfterAlloc()
{
    ObjectPool<int> pool(2);
    assert(2 == pool.freeCount());

    int* p1 = pool.alloc();
    assert(1 == pool.freeCount());

    pool.free(p1);
    assert(2 == pool.freeCount());
}

void testObjectPool_FreeCountRemainZeroWhenPoolIsEmpty()
{
    ObjectPool<int> pool(2);

    int* p1 = pool.alloc();
    int* p2 = pool.alloc();

    assert(0 == pool.freeCount());

    int* p3 = pool.alloc();
    assert(0 == pool.freeCount());

    pool.free(p3);
    assert(0 == pool.freeCount());

    pool.free(p1);
    pool.free(p2);

    assert(2 == pool.freeCount());
}

void testObjectPool()
{
    testObjectPool_InvalidSizeThrowException();
    testObjectPool_FreeCountDecreaseAfterAlloc();
    testObjectPool_FreeCountRemainZeroWhenPoolIsEmpty();
}

} // end of namespace commonlib
} // end of namespace mcdane

