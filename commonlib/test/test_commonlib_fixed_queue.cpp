#include <gtest/gtest.h>
#include <commonlib_fixed_queue.h>

using namespace mcdane::commonlib;

TEST(TestQueue, InvalidCapacityThrowException)
{
    ASSERT_THROW(FixedQueue<int> q(0), InvalidArgumentException);
}

TEST(TestQueue, TestEnqueue)
{
    FixedQueue<int> q(2);
    int t;

    ASSERT_TRUE(q.empty());
    ASSERT_TRUE(q.enqueue(1));
    ASSERT_TRUE(q.peek(t) && t == 1);
    ASSERT_EQ(q.size(), 1);
    ASSERT_TRUE(q.enqueue(2));
    ASSERT_EQ(q.size(), 2);
    ASSERT_FALSE(q.enqueue(3));
}

TEST(TestQueue, TestDequeue)
{
    FixedQueue<int> q(2);
    int t;

    q.enqueue(1);
    q.enqueue(2);
    ASSERT_TRUE(q.dequeue(t) && t == 1);
    ASSERT_TRUE(q.dequeue(t) && t == 2);
    ASSERT_TRUE(q.empty());
    ASSERT_FALSE(q.dequeue(t));
}
