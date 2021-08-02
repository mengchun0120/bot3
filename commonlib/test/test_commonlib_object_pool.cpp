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

    std::shared_ptr<int> p1 = pool.alloc();
    ASSERT_EQ(1, pool.freeCount());
}

TEST(TestObjectPool, FreeCountIncreaseAfterReset)
{
    ObjectPool<int> pool(2);

    std::shared_ptr<int> p1 = pool.alloc();
    std::shared_ptr<int> p2 = p1;

    ASSERT_EQ(1, pool.freeCount());

    p1.reset();
    ASSERT_EQ(1, pool.freeCount());

    p2.reset();
    ASSERT_EQ(2, pool.freeCount());
}

TEST(TestObjectPool, FreeCountRemainZeroWhenPoolIsEmpty)
{
    ObjectPool<int> pool(2);

    std::shared_ptr<int> p1 = pool.alloc();
    std::shared_ptr<int> p2 = pool.alloc();

    ASSERT_EQ(0, pool.freeCount());

    std::shared_ptr<int> p3 = pool.alloc();
    ASSERT_EQ(0, pool.freeCount());
}

