#include <gtest/gtest.h>
#include <commonlib_object_pool.h>

using namespace mcdane::commonlib;

TEST(TestObjectPool, InvalidSizeThrowException)
{
    ASSERT_THROW(ObjectPool<int> pool(0), InvalidArgumentException);
}

TEST(TestObjectPool, FreeCountDecreaseAfterAlloc)
{
    ObjectPool<int> pool(2);
    ASSERT_EQ(2, pool.freeCount());

    int* p1 = pool.alloc();
    ASSERT_EQ(1, pool.freeCount());

    pool.free(p1);
    ASSERT_EQ(2, pool.freeCount());
}

TEST(TestObjectPool, FreeCountRemainZeroWhenPoolIsEmpty)
{
    ObjectPool<int> pool(2);

    int* p1 = pool.alloc();
    int* p2 = pool.alloc();

    ASSERT_EQ(0, pool.freeCount());

    int* p3 = pool.alloc();
    ASSERT_EQ(0, pool.freeCount());

    pool.free(p3);
    ASSERT_EQ(0, pool.freeCount());

    pool.free(p1);
    pool.free(p2);

    ASSERT_EQ(2, pool.freeCount());
}

