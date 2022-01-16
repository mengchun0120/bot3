#include <cassert>
#include <vector>
#include <iostream>
#include <sstream>
#include <commonlib_linked_list.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

class TestNode: public Object {
public:
    TestNode(int v);

    inline int val() const;

    inline TestNode* next();

    inline const TestNode* next() const;

    inline TestNode* prev();

    inline const TestNode* prev() const;

    inline void setNext(TestNode* n);

    inline void setPrev(TestNode* n);

    std::string toString() const override;

private:
    int val_;
    TestNode* next_;
    TestNode* prev_;
};

TestNode::TestNode(int v)
    : val_(v)
    , next_(nullptr)
    , prev_(nullptr)
{
}

int TestNode::val() const
{
    return val_;
}

TestNode* TestNode::next()
{
    return next_;
}

const TestNode* TestNode::next() const
{
    return next_;
}

TestNode* TestNode::prev()
{
    return prev_;
}

const TestNode* TestNode::prev() const
{
    return prev_;
}

void TestNode::setNext(TestNode* n)
{
    next_ = n;
}

void TestNode::setPrev(TestNode* n)
{
    prev_ = n;
}

std::string TestNode::toString() const
{
    std::ostringstream oss;

    oss << "TestNode(val=" << val_
        << ", prev=" << prev_
        << ", next=" << next_
        << ", Base=" << Object::toString()
        << ")";

    return oss.str();
}

bool checkLinkedList(const LinkedList<TestNode>& list,
                     const std::vector<int>& values)
{
    const TestNode *t;
    auto it = values.cbegin();

    for (t = list.first(); t && it != values.cend(); t = t->next(), ++it)
    {
        if (t->val() != *it)
        {
            return false;
        }
    }

    return t == nullptr && it == values.cend();
}

void testLinkedList_PushFrontNullCauseException()
{
    bool exceptionHappened = false;

    try
    {
        LinkedList<TestNode> list;
        list.pushFront(nullptr);
    }
    catch(const InvalidArgumentException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testLinkedList_PushBackNullCauseException()
{
    bool exceptionHappened = false;

    try
    {
        LinkedList<TestNode> list;
        list.pushBack(nullptr);
    }
    catch(const InvalidArgumentException& e)
    {
        std::cerr << e.what() << std::endl;
        exceptionHappened = true;
    }

    assert(exceptionHappened);
}

void testLinkedList_PushWorks()
{
    LinkedList<TestNode> list;
    TestNode* n1 = new TestNode(1);
    TestNode* n2 = new TestNode(2);
    TestNode* n3 = new TestNode(3);
    TestNode* n4 = new TestNode(4);

    list.pushFront(n1);
    assert(list.first()->val() == 1);

    list.pushBack(n2);
    assert(checkLinkedList(list, {1, 2}));

    list.pushFront(n3);
    assert(checkLinkedList(list, {3, 1, 2}));

    list.pushBack(n4);
    assert(checkLinkedList(list, {3, 1, 2, 4}));
}

void testLinkedList_InsertWorks()
{
    LinkedList<TestNode> list;
    TestNode* n1 = new TestNode(1);
    TestNode* n2 = new TestNode(2);
    TestNode* n3 = new TestNode(3);
    TestNode* n4 = new TestNode(4);
    TestNode* n5 = new TestNode(5);

    list.insertAfter(nullptr, n1);
    assert(checkLinkedList(list, {1}) && list.size() == 1);

    list.insertBefore(nullptr, n2);
    assert(checkLinkedList(list, {2, 1}) && list.size() == 2);

    list.insertAfter(n1, n3);
    assert(checkLinkedList(list, {2, 1, 3}) && list.last() == n3 &&
           list.size() == 3);

    list.insertBefore(n1, n4);
    assert(checkLinkedList(list, {2, 4, 1, 3}));

    list.insertBefore(n2, n5);
    assert(checkLinkedList(list, {5, 2, 4, 1, 3}) && list.first() == n5);
}

void testLinkedList_UnlinkWorks()
{
    LinkedList<TestNode> list;
    TestNode n1(1), n2(2), n3(3), n4(4);

    list.pushFront(&n1);
    list.pushFront(&n2);
    list.pushFront(&n3);
    list.pushFront(&n4);

    TestNode* n = list.unlinkFront();
    assert(n == &n4 && checkLinkedList(list, {3, 2, 1}));

    list.unlink(&n2);
    assert(checkLinkedList(list, {3, 1}));

    n = list.unlinkBack();
    assert(n == &n1 && checkLinkedList(list, {3}));
}

void testLinkedList_RemoveWorks()
{
    LinkedList<TestNode> list;
    TestNode* n1 = new TestNode(1);
    TestNode* n2 = new TestNode(2);
    TestNode* n3 = new TestNode(3);
    TestNode* n4 = new TestNode(4);

    list.pushFront(n1);
    list.pushFront(n2);
    list.pushFront(n3);
    list.pushFront(n4);

    list.removeFront();
    assert(checkLinkedList(list, {3, 2, 1}));

    list.removeBack();
    assert(checkLinkedList(list, {3, 2}));

    list.remove(n3);
    assert(checkLinkedList(list, {2}));
}

void testLinkedList()
{
    testLinkedList_PushFrontNullCauseException();
    testLinkedList_PushBackNullCauseException();
    testLinkedList_PushWorks();
    testLinkedList_InsertWorks();
    testLinkedList_UnlinkWorks();
    testLinkedList_RemoveWorks();
}

} // end of namespace commonlib
} // end of namespace mcdane

