#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "../oop-unit-test-framework/UnitTestFramework.h"
#include "bintree.cpp"
#include "bintree_tests.h"
#include "tree_tests.h"
#include "simple_bintree_tests.h"


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
