#include <cassert>
#include <vector>
#include <commonlib_linked_list.h>
#include <test_commonlib.h>

namespace mcdane {
namespace commonlib {

class TestNode {
public:
    TestNode(int v);

    inline int val() const;

    inline TestNode* next();

    inline const TestNode* next() const;

    inline void setNext(TestNode* n);

private:
    int val_;
    TestNode* next_;
};

TestNode::TestNode(int v)
    : val_(v)
    , next_(nullptr)
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

void TestNode::setNext(TestNode* n)
{
    next_ = n;
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

void testLinkedList_AddRemoveClear()
{
    LinkedList<TestNode> list;
    TestNode *n1, *n2, *n3, *n4;

    n1 = new TestNode(1);
    list.add(n1);
    assert(list.first()->val() == 1);

    n2 = new TestNode(2);
    list.add(n2);
    assert(checkLinkedList(list, {2, 1}));

    list.remove(nullptr, list.first());
    assert(checkLinkedList(list, {1}));

    n3 = new TestNode(3);
    n4 = new TestNode(4);
    list.add(n3);
    list.add(n4);
    assert(checkLinkedList(list, {4, 3, 1}));

    list.remove(n4, n3);
    assert(checkLinkedList(list, {4, 1}));

    list.clear();
    assert(list.empty());
}

void testLinkedList()
{
    testLinkedList_AddRemoveClear();
}

} // end of namespace commonlib
} // end of namespace mcdane

