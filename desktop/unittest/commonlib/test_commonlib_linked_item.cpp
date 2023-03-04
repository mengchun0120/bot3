#include <cassert>
#include <iostream>
#include <commonlib_linked_item.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

struct TestStruct {
    TestStruct(int i=0, int j=0)
        : i_(i)
        , j_(j)
    {}

    int i_, j_;
};


void testLinkedItem_testConstructors()
{
    LinkedItem<TestStruct> t1;
    assert(t1.prev() == nullptr && t1.next() == nullptr &&
           t1.item().i_ == 0 && t1.item().j_ == 0);

    LinkedItem<TestStruct> t2(1, 2);
    assert(t2.prev() == nullptr && t2.next() == nullptr &&
           t2.item().i_ == 1 && t2.item().j_ == 2);
}

void testLinkedItem_setPrevNext()
{
    LinkedItem<TestStruct> t1, t2, t3;
    t2.setPrev(&t1);
    t2.setNext(&t3);
    assert(t2.prev() == &t1 && t2.next() == &t3);
}

void testLinkedItem_setItem()
{
    LinkedItem<TestStruct> t;
    t.setItem(1, 2);
    assert(t.item().i_ == 1 && t.item().j_ == 2);
}

void testLinkedItem()
{
    testLinkedItem_testConstructors();
    testLinkedItem_setPrevNext();
    testLinkedItem_setItem();
}

} // end of namespace commonlib
} // end of namespace mcdane
