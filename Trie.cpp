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
    
    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (TrieNode* child : node->children) {
                deleteTrie(child);
            }
        delete node;
    }

 // destructor
 ~Trie() {
        deleteTrie(root);
    }


//Function to find the suggestions for missplled word. 
vector<string> Find_Suggestions(const string& word, const Trie& trie) const{

    vector<string> suggestions;

    // "Different approches to find suggestions."

    // Insertion of all alphabets one by one at each position in input word. 
    for (int i=0; i<=word.size(); i++){
        for (char ch='a'; ch<='z'; ch++){
            string new_Word = word.substr(0,i) + ch + word.substr(i);
            if (trie.search(new_Word) || trie.search(convert_to_Lowercase(new_Word))){
                suggestions.push_back(new_Word);
            }
        }
    }

    // Substitution of each alphabet in input word with all other alphabets.
    for (int i=0; i<word.size(); i++){
        for (char ch='a'; ch<='z'; ch++){
            string new_Word = word.substr(0,i) + ch + word.substr(i+1);
            if (ch != word[i]    &&     (trie.search(new_Word) || trie.search(convert_to_Lowercase(new_Word))) ){
                suggestions.push_back(new_Word);
            }
        }
    }


    
}  

};
