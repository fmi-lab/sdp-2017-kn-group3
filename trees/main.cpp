#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "../StringEditor/UnitTestFramework.h"
#include "bintree.cpp"

template <typename T>
class Tree {
    T data;
    std::vector<Tree<T>> children;

public:
    Tree(const T& data): data(data) { }

    Tree& addChild(const Tree<T>& child) {
        children.push_back(child);
        return *this;
    }

    int findDFS(const T& x) {
        if (data == x) {
            return 0;
        }
        for (auto it = children.begin(); it != children.end(); ++it) {
            int distInChild = (*it).findDFS(x);
            if (distInChild != -1) {
                return distInChild + 1;
            }
        }
        return -1;

    }

    int findDFSStack(const T& x) {
        std::stack<std::pair<Tree<T>*, int>> st;
        st.push(std::make_pair(this, 0));

        while(!st.empty()) {
            Tree<T>* currentNode = st.top().first;
            int currentDepth = st.top().second;
            st.pop();
            if (currentNode->data == x) {
                return currentDepth;
            }
            for (auto it = currentNode->children.rbegin();
                 it != currentNode->children.rend(); ++it) {
                     st.push(std::make_pair(&(*it), currentDepth + 1));
                 }
        }
        return -1;
    }


    int findBFS(const T& x) {
        std::queue<std::pair<Tree<T>*, int>> q;
        q.push(std::make_pair(this, 0));

        while(!q.empty()) {
            Tree<T>* currentNode = q.front().first;
            int currentDepth = q.front().second;
            q.pop();
            if (currentNode->data == x) {
                return currentDepth;
            }
            for (auto it = currentNode->children.rbegin();
                 it != currentNode->children.rend(); ++it) {
                     q.push(std::make_pair(&(*it), currentDepth + 1));
                 }
        }
        return -1;
    }
};

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

TEST_CASE("BinTree", BinTree_isBST) {
    BinTree<std::string> tree("garden");
    tree.insertWithPos("block", "L");
    tree.insertWithPos("alpha", "LL");
    tree.insertWithPos("cinema", "LR");
    tree.insertWithPos("cat", "LRL");
    tree.insertWithPos("dog", "LRR");
    tree.insertWithPos("lambda", "R");
    tree.insertWithPos("lamb", "RL");
    tree.insertWithPos("sheep", "RR");
    Assert::IsTrue(tree.isBST(tree.rootpos()));
}

template <typename T>
int findIndex (const std::vector<T>& vec, const T& el) {
    int idx = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it == el) {
            return idx;
        }
        ++idx;
    }
    return -1;
}
template <typename T>
// kld - корен - ляво -дясно
// по зададено обхождане ЛКД и КЛД, да се възстанови дървото
BinTree<T> reconstructTree(std::vector<T> lkd,
                            std::vector<T> kld)
{
    if (lkd.size() == 0) {
        // empty tree
        return BinTree<T>();
    } else if (lkd.size() == 1) {
        // leaf
        return BinTree<T>(lkd[0]);
    }
    T root = kld[0];
    int rootIdx = findIndex(lkd, root);
    std::vector<T> leftLKD(lkd.begin(), lkd.begin() + rootIdx);
    std::vector<T> leftKLD(kld.begin() + 1, kld.begin() + leftLKD.size() + 1);

    std::vector<T> rightLKD(lkd.begin() + rootIdx + 1, lkd.end());
    std::vector<T> rightKLD(kld.begin() + leftLKD.size() + 1, kld.end());

    return BinTree<T>(root,
                       reconstructTree(leftLKD, leftKLD),
                       reconstructTree(rightLKD, rightKLD));

}

int main()
{
    RunTests();
    std::vector<int> kld;
    kld.push_back(1);
    kld.push_back(2);
    kld.push_back(3);
    kld.push_back(5);
    kld.push_back(13);
    kld.push_back(5);
    kld.push_back(8);
    kld.push_back(10);

    std::vector<int> lkd;
    lkd.push_back(5);
    lkd.push_back(3);
    lkd.push_back(13);
    lkd.push_back(2);
    lkd.push_back(1);
    lkd.push_back(8);
    lkd.push_back(5);
    lkd.push_back(10);

    BinTree<int> t = reconstructTree(lkd, kld);
    t.printDOT();
    return 0;
}
