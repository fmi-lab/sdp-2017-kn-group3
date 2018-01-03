
#ifndef __BINTREE_CPP
#define __BINTREE_CPP

#include <iostream>
#include <vector>

/**
 * Builds on the Binary Tree implementation from lectures that can be found at
 * https://github.com/triffon/sdp-2017-18/blob/master/trees/bintree.cpp
 * Added methods for inorder, preorder and postorder traversals
 */
template <typename T>
struct BinTreeNode {
  T data;
  BinTreeNode *left, *right;

  BinTreeNode(T const& _data = T(),
              BinTreeNode *_left = nullptr,
              BinTreeNode *_right = nullptr) :
    data(_data),
    left(_left),
    right(_right) {}
};

template <typename T>
class BinTree;

template <typename T>
class BinTreePosition {
private:
  friend class BinTree<T>;
  using BTN = BinTreeNode<T>;

  BTN** ptr;

  BinTreePosition(BTN*& node) : ptr(&node) {}
public:

  BinTreePosition() : ptr(nullptr) {}

  BinTreePosition(BinTree<T>& bt) : ptr(&bt.rootptr) {}

  BinTreePosition(BinTree<T>&& bt) : ptr(&bt.rootptr) {}

  bool valid() const {
    return ptr != nullptr && *ptr != nullptr;
  }

  T& get() const {
    return (*ptr)->data;
  }

  BinTreePosition left() const {
    return BinTreePosition((*ptr)->left);
  }

  BinTreePosition right() const {
    return BinTreePosition((*ptr)->right);
  }

  // ����������� �����

  operator bool() const {
    return valid();
  }

  T& operator*() const {
    return get();
  }

  BinTreePosition operator-() const {
    return left();
  }

  BinTreePosition operator+() const {
    return right();
  }

  BinTreePosition& operator--() {
    return (*this = left());
  }

  BinTreePosition& operator++() {
    return (*this = right());
  }

  BinTreePosition operator--(int) {
    BinTreePosition save = *this;
    --(*this);
    return save;
  }

  BinTreePosition operator++(int) {
    BinTreePosition save = *this;
    ++(*this);
    return save;
  }

};

template <typename T>
class BinTree {
public:
  friend class BinTreePosition<T>;
  using P = BinTreePosition<T>;

protected:

  using BTN = BinTreeNode<T>;

  BTN* rootptr;

  int countNodes(BTN* node) const {
    if (node == nullptr)
      return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
  }

  BTN* copyNode(BTN* node) const {
    if (node == nullptr)
      return nullptr;
    // std::clog << "Creating copy of node " << node->data << "\n";
    return new BTN(node->data,
                   copyNode(node->left),
                   copyNode(node->right));
  }

  void eraseNode(BTN* node) {
    if (node != nullptr) {
      eraseNode(node->left);
      eraseNode(node->right);
      //      std::clog << "Erasing node " << node->data << "\n";
      delete node;
    }
  }

  void printNodeDOT(BTN* node, std::ostream& os = std::cout) {
    if (node != nullptr) {
      if (node->left != nullptr) {
        os << node->data << " -> " << node->left->data << "\n";
        printNodeDOT(node->left, os);
      }
      if (node->right != nullptr) {
        os << node->data << " -> " << node->right->data << "\n";
        printNodeDOT(node->right, os);
      }
    }
  }

public:
  BinTree() : rootptr(nullptr) {}

  BinTree(BinTree const& bt) {
    rootptr = copyNode(bt.rootptr);
  }

  BinTree& operator=(BinTree const& bt) {
    if (this != &bt) {
      eraseNode(rootptr);
      rootptr = copyNode(bt.rootptr);
    }
    return *this;
  }

  ~BinTree() {
    eraseNode(rootptr);
  }

  // ��������� ��� ������
  P rootpos() {
    return P(*this);
  }

  // ��������� ����� �� ����� �����
  void assignFrom(BTN*& to, BTN*& from) {
    // ��������� ������� �������� �� to
    eraseNode(to);
    // ����������� �� �������� ��������
    to = from;
    // � �� ��������, �� �� �� �� ��������� ����
    from = nullptr;
  }

  void assignFrom(P to, P from) {
    assignFrom(*to.ptr, *from.ptr);
  }

  // O(n) �� ����� � �� �����
  // �����������, ����� ����� �� lvalues
  BinTree(T const& data,
          BinTree& lt,
          BinTree& rt) {
    rootptr = new BTN(data);
    assignFrom(rootptr->left, lt.rootptr);
    assignFrom(rootptr->right, rt.rootptr);
  }

  // O(1) �� ����� � �� �����
  // �����������, ����� ����� �� rvalues
  BinTree(T const& data,
          BinTree&& lt = BinTree(),
          BinTree&& rt = BinTree()) {
    rootptr = new BTN(data);
    assignFrom(rootptr->left, lt.rootptr);
    assignFrom(rootptr->right, rt.rootptr);
  }

  // O(1) �� ����� � �� �����
  // �����������, ����� ������
  BinTree(T const& data,
          BinTree const& lt,
          BinTree const& rt) {
    rootptr = new BTN(data,
                      copyNode(lt.rootptr),
                      copyNode(rt.rootptr));
  }


  bool empty() const {
    return rootptr == nullptr;
  }

  T root() const {
    return rootptr->data;
  }

  int count() const {
    return countNodes(rootptr);
  }

  void printDOT(std::ostream& os = std::cout) {
    os << "digraph bintree {\n";
    // ��������� �� ������, � ������, �� ��� ������������ ������ �����
    os << root() << ";\n";
    printNodeDOT(rootptr, os);
    os << "}\n";
  }
    void rootLeftRight(BTN* node, std::vector<T> result) {
      if (node == nullptr) {
        return;
      }
      result.push_back(node->data);
      rootLeftRight(node->left, result);
      rootLeftRight(node->right, result);
  }

  std::vector<T> rootLeftRight() {
      std::vector<T> result;
      rootLeftRight(rootptr, result);
      return result;
  }
};

template <typename T>
bool equalTrees(BinTreePosition<T> p1, BinTreePosition<T> p2) {
  return !p1 && !p2 ||
    p1 && p2 && *p1 == *p2 &&
    equalTrees(-p1, -p2) &&
    equalTrees(+p1, +p2);
}

template <typename T>
bool operator==(BinTree<T>& t1, BinTree<T>& t2) {
  return equalTrees(BinTreePosition<T>(t1), BinTreePosition<T>(t2));
}

template <typename T>
bool operator==(BinTree<T>&& t1, BinTree<T>&& t2) {
  return equalTrees(BinTreePosition<T>(t1), BinTreePosition<T>(t2));
}

template <typename T>
int depth(BinTreePosition<T> p) {
  if (!p)
    return 0;
  return 1 + std::max(depth(-p), depth(+p));
}


#endif
