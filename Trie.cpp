#include <bits/stdc++.h>
using namespace std;

// TrieNode Structure
struct TrieNode {
    char character;
    bool isWord;
    vector<TrieNode*> children;

    TrieNode(char ch) : character(ch), isWord(false), children(26, nullptr) {}
};

// Trie class
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode('\0');
    }
};
