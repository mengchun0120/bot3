#include <cassert>
#include <commonlib_exception.h>
#include <commonlib_fixed_queue.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

void testFixedQueue_InvalidCapacityThrowException()
{
    bool exceptionHappened = false;

    try
    {
        FixedQueue<int> q(0);
    }
    catch (const InvalidArgumentException& e)
    {
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testFixedQueue_TestEnqueue()
{
    FixedQueue<int> q(2);
    int t;

    assert(q.empty());
    assert(q.enqueue(1));
    assert(q.peek(t) && t == 1);
    assert(q.size() == 1);
    assert(q.enqueue(2));
    assert(q.size() == 2);
    assert(!q.enqueue(3));
}

void testFixedQueue_TestDequeue()
{
    FixedQueue<int> q(2);
    int t;

    q.enqueue(1);
    q.enqueue(2);
    assert(q.dequeue(t) && t == 1);
    assert(q.dequeue(t) && t == 2);
    assert(q.empty());
    assert(!q.dequeue(t));
}

void testFixedQueue()
{
    testFixedQueue_InvalidCapacityThrowException();
    testFixedQueue_TestEnqueue();
    testFixedQueue_TestDequeue();
}

} // end of namespace commonlib
} // end of namespace mcdane

