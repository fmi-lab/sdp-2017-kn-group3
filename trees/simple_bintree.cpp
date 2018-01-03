#ifndef __SIMPLE_BINTREE_CPP
#define __SIMPLE_BINTREE_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(T data, Node<T>* left=nullptr, Node<T>* right=nullptr):data(data), left(left), right(right) { }
};

template <typename T>
struct IndexedNode {
    Node<T>* node;
    int layerIndex;
    int nodeIndex;
    IndexedNode(Node<T>* node, int layer, int nodeIndex):
        node(node), layerIndex(layer), nodeIndex(nodeIndex) { }
};

template <typename T>
class BTree {
    Node<T>* root;
public:
    BTree() {
        root = nullptr;
    }
    BTree(const T& data) {
        root = new Node<T>(data);
    }
    // TODO: implement proper destructor, copy constructor, operator=
    ~BTree() {
        // TODO: delete child nodes first
        delete root;
    }
    int sum() {
        return sum(root);
    }
    int height() {
        return height(root);
    }

    BTree<T>& addLeftChild(const BTree<T>& other) {
        this->root->left = other.root;
        return *this;
    }
    BTree<T>& addRightChild(const BTree<T>& other) {
        this->root->right = other.root;
        return *this;
    }
private:
    int sum(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->data +
         sum(node->left) +
         sum(node->right);
    }
    int height(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }

    bool isBalanced(Node<T>* node) {
        if (node == nullptr) {
            return true;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        int diff = leftHeight - rightHeight;
        if (diff < -1 || diff > 1) {
            return false;
        }
        return isBalanced(node->left) &&
                isBalanced(node->right);
    }

    public:
    std::vector<std::vector<int>> layers() {
        std::vector<std::vector<int>> layers;//(height(root), vector<T>);
        std::queue<IndexedNode<T>> q;
        q.push(IndexedNode<T>(root, 0, 0));
        while(!q.empty()) {
            Node<T>* currentNode = q.front().node;
            int layerIdx = q.front().layerIndex;
            int nodeIndex = q.front().nodeIndex;
            //cout << "Element " << currentNode->data <<
            //   " in layer " << layerIdx << endl;
               while (layers.size() <= layerIdx) {
                layers.push_back(std::vector<int>());
               }
            layers[layerIdx].push_back(nodeIndex);
            q.pop();
            if (currentNode->left) {
                q.push(IndexedNode<T>(
                                 currentNode->left,
                                 layerIdx+1,
                                 2*nodeIndex + 1));
            }
            if (currentNode->right) {
                q.push(IndexedNode<T>(
                                 currentNode->right,
                                 layerIdx+1,
                                 2*nodeIndex + 2));
            }
        }
        return layers;
    }

    bool isCompleteTree() {
        std::vector<std::vector<int>> layers = this->layers();
        for (int i = 0; i < layers.size(); i++) {
            if (i != layers.size() - 1) {
                std::vector<int> currentLayer = layers[i];
                if (currentLayer.size() != pow(2, i)) {
                    return false;
                }
            } else {
                // last layer
                std::vector<int> lastLayer = layers[i];
                int expectedValue = pow(2, i) - 1;
                for (int j = 0; j < lastLayer.size();
                    j++, expectedValue++) {
                    if (lastLayer[j] != expectedValue) {
                        return false;
                    }
                }
            }
        }
    }
};

#endif
