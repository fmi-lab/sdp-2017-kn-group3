#ifndef __TREE_CPP
#define __TREE_CPP

#include <vector>
#include <stack>
#include <queue>

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

#endif // __TREE_CPP
