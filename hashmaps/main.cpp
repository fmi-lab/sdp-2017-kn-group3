#include <iostream>
#include "HashMap.h"
#include <string>
using namespace std;

unsigned int constHash(const string& key) {
    return 5;
}

unsigned int asciiHash(const string& key) {
    unsigned int result = 0;
    for (auto c: key) {
        result += c;
    }
    return result;
}

unsigned int primeHash(const string& key) {
    unsigned int result = 0;
    unsigned int prime = 37;
    for (auto c: key) {
        result *= prime;
        result += c;
    }
    return result;
}



int main()
{
    HashMap<string, string> map1(constHash);
    HashMap<string, string> map2(asciiHash);
    HashMap<string, string> map3(primeHash);

    string words[] = {
       "garden",
       "dog",
       "castle",
       "test",
       "garden1",
       "dog1",
       "castle1",
       "test1",
       "1garden",
       "1dog",
       "1castle",
       "1test",
       "gar1den",
       "do1g",
       "cas1tle",
       "te1st"
    };
    map1.ensureCapacity(106);
    for (int i = 0; i < 16; i++) {
        string word = words[i];
        map1.add(word, "val");
        map2.add(word, "val");
        map3.add(word, "val");
        cout << "added " << word << endl;
    }
    cout << "map1 efficiency: " << map1.efficiency() << endl;
    cout << "map2 efficiency: " << map2.efficiency() << endl;
    cout << "map3 efficiency: " << map3.efficiency() << endl;

    for (auto& entry: map1) {
        map1[entry.key()] = "val2";
        cout << entry.key() << " " << entry.value() << endl;
    }
    return 0;
}
