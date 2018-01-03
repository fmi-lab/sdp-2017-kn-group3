#include "bintree.cpp"

TEST_CASE("BinTree", BinTreeTraversal_RootLeftRight) {
    BinTree<int> t(1,
                   BinTree<int>(2,
                                BinTree<int>(3,
                                             BinTree<int>(5),
                                             BinTree<int>(13))),
                   BinTree<int>(5,
                                BinTree<int>(8),
                                BinTree<int>(10))
                   );
    std::vector<int> expected;
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    expected.push_back(5);
    expected.push_back(13);
    expected.push_back(5);
    expected.push_back(8);
    expected.push_back(10);
    std::vector<int> actual = t.rootLeftRight();

    std::vector<int>::iterator expectedIt = expected.begin();
    auto actualIt = actual.begin();
    for (; expectedIt != expected.end() && actualIt != actual.end();
        ++expectedIt, ++actualIt) {
        Assert::AreEqual(*expectedIt, *actualIt);
    }
}
