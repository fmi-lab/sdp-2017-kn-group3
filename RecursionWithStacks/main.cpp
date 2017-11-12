#include <iostream>
#include <vector>
#include <string>

int fibStack(int);
std::vector<std::string> permuteStack(char[], int);

int main()
{
    std::cout << fibStack(8) << std::endl;
    char chars[5] = {'a', 'b', 'c', 'd', 'e'};
    std::vector<std::string> permutations = permuteStack(chars, 5);
    for (auto it = permutations.begin(); it != permutations.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}
