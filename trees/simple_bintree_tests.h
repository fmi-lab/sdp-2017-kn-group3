#include "simple_bintree.cpp"

TEST_CASE("SimpleBinTree", SimpleBinTree_sum) {
    BTree<int> t(1);
    t.addLeftChild(BTree<int>(5).addLeftChild(BTree<int>(7)))
     .addRightChild(BTree<int>(15));

    Assert::AreEqual(t.sum(), 28);
}
