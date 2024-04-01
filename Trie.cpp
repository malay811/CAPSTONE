#include <bits/stdc++.h>
using namespace std;

// TrieNode Structure
struct TrieNode {
    char character;
    bool isWord;
    vector<TrieNode*> children;

    TrieNode(char ch) : character(ch), isWord(false), children(26, nullptr) {}
};

string toLowerCase(string str)
{
    string lowerStr=str;
    transform(lowerStr.begin(),lowerStr.end(),lowerStr.begin(),::tolower);//included "algorithm" file for using this function
    //converts uppercase letters to lowercase
    return lowerStr;
}

string toUpperCase(string str)
{
    string upperStr=str;
    transform(upperStr.begin(),upperStr.end(),upperStr.begin(),::toupper);//included "algorithm" file for using this function
    //converts uppercase letters to lowercase
    return upperStr;
}
    
// Trie class
class Trie {
    private:
        TrieNode* root;
    
    public:
        Trie() {
            root = new TrieNode('\0');
        }

    //inserting a word
    void insert(string word)
    {
        TrieNode* node=root;
        for(char ch : word)// It iterates over each character 'ch' in the input word.
        {
            int index=tolower(ch)-'a';
            // to get an index in the range 0 to 25, representing the position of the character in the children array of the current node.
            if(node->children[index]==nullptr)//charactor is not present
            {
                node->children[index]=new TrieNode(ch);//making a new node for the charactor
            }
            node=node->children[index];//element is present then updating the pointer
        }
        node->isWord=true;//making last charactor of the input string as a Terminal node
    }

    //searching a word
    bool search(string word)
    {
        TrieNode* node=root;
        for(char ch : word)
        {
            int index=tolower(ch)-'a';
            if(node->children[index]==nullptr)//charactor is not present
            {
                return false;
            }
            node=node->children[index];//element is present
        }
        return node->isWord;//returning terminal node
        //If node->isWord is true, it means that the entire word was found in the trie, and if it's false, 
        //it means that the sequence of characters is part of a longer word but not a complete word itself.
        //if trie have abcd word and input string is abc then it will return false.
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

    // Deletion of each alphabet one by one in input word.
    for (int i=0; i<word.size(); i++){
        string new_Word = word.substr(0,i) + word.substr(i+1);
        if (trie.search(new_Word) || trie.search(convert_to_Lowercase(new_Word))){
            suggestions.push_back(new_Word);
        }
    }
    
    // Swapping of adjacent alphabets in input word.
    for (int i=0; i<word.size()-1; i++) {
        string new_Word = word.substr(0,i) + word[i+1] + word[i] + word.substr(i+2);
        if (trie.search(new_Word) || trie.search(convert_to_Lowercase(new_Word))){
            suggestions.push_back(new_Word);
        }
    }

    return suggestions;
}  

};
