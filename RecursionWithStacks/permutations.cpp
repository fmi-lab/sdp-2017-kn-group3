#include <vector>
#include <stack>
#include <string>
#include <iostream>

struct PermutationFrame {
    std::string currentPermutation;
    std::vector<char> unused;
    PermutationFrame(std::string perm, std::vector<char> unused)
       : currentPermutation(perm), unused(unused) {

       }
};

std::vector<std::string> permuteStack(char chars[], int n) {
    std::string permutation;
    std::vector<std::string> results;
    std::vector<char> unused(chars, chars + n);
    std::stack<PermutationFrame> st;
    PermutationFrame first(permutation, unused);

    st.push(first);
    while(!st.empty()) {
        PermutationFrame top = st.top();
        st.pop();
        if (top.unused.size() == 0) {
            results.push_back(top.currentPermutation);
        } else {
            for (unsigned int i = 0; i < top.unused.size(); i++) {
                std::vector<char> nextUnused = top.unused;
                nextUnused.erase(nextUnused.begin() + i);

                PermutationFrame next(top.currentPermutation,
                                      nextUnused);
                next.currentPermutation += top.unused[i];
                st.push(next);
            }
        }
    }
    return results;
}

/* Recursive solution */
void permuteHelper (char* currentPermutation, int currentIdx, std::vector<char> unused) {
    if (unused.size() == 0) {
        std::cout << currentPermutation << std::endl;
        return;
    }
    for (unsigned int i = 0; i < unused.size(); i++) {
        currentPermutation[currentIdx] = unused[i];
        std::vector<char> newUnused = unused;
        newUnused.erase(newUnused.begin() + i);
        permuteHelper(currentPermutation, currentIdx+1, newUnused);

    }
}

void permute(char* chars, int n) {
    char * permutation = new char[n+1];
    permutation[n] = 0;
    std::vector<char> unused(chars, chars + n);
    permuteHelper(permutation, 0, unused);
}
