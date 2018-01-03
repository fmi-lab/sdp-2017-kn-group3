#include "tree.cpp"

TEST_CASE("Tree", Tree_findDFS) {
    Tree<int> t = Tree<int>(1)
       .addChild(Tree<int>(2)
                    .addChild(Tree<int>(3)
                                 .addChild(Tree<int>(5))))
        .addChild(Tree<int>(5)
                     .addChild(Tree<int>(8))
                     .addChild(Tree<int>(10)))
        .addChild(Tree<int>(7)
                     .addChild(Tree<int>(4))
                     .addChild(Tree<int>(6))
                     .addChild(Tree<int>(15)));
    Assert::AreEqual(t.findDFS(5), 3);
}

TEST_CASE("Tree", Tree_findDFSStack) {
    Tree<int> t = Tree<int>(1)
       .addChild(Tree<int>(2)
                    .addChild(Tree<int>(3)
                                 .addChild(Tree<int>(5))))
        .addChild(Tree<int>(5)
                     .addChild(Tree<int>(8))
                     .addChild(Tree<int>(10)))
        .addChild(Tree<int>(7)
                     .addChild(Tree<int>(4))
                     .addChild(Tree<int>(6))
                     .addChild(Tree<int>(15)));
    Assert::AreEqual(t.findDFSStack(5), 3);
}


TEST_CASE("Tree", Tree_findBFS) {
    Tree<int> t = Tree<int>(1)
       .addChild(Tree<int>(2)
                    .addChild(Tree<int>(3)
                                 .addChild(Tree<int>(5))))
        .addChild(Tree<int>(5)
                     .addChild(Tree<int>(8))
                     .addChild(Tree<int>(10)))
        .addChild(Tree<int>(7)
                     .addChild(Tree<int>(4))
                     .addChild(Tree<int>(6))
                     .addChild(Tree<int>(15)));
    Assert::AreEqual(t.findBFS(5), 1);
}

