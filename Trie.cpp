#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cctype>
using namespace std;

// TrieNode Structure
struct TrieNode {
    char character;
    bool isWord;
    vector<TrieNode*> children;

    TrieNode(char ch) : character(ch), isWord(false), children(26, nullptr) {}
};

string convert_to_Lowercase(const string &str)
{
    string lowerStr=str;
    transform(lowerStr.begin(),lowerStr.end(),lowerStr.begin(),::tolower);//included "algorithm" file for using this function
    //converts uppercase letters to lowercase
    return lowerStr;
}

string convert_to_Uppercase(const string &str)
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
    void insert(const string &word)
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
    bool search(const string &word)const
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


// Function to calculate the levenshtein distance(changes needed to convert one word into another word) between two words
int Levenshtein_Distance(const string &Spell1, const string &Spell2) const{
    int p = Spell1.length();
    int q = Spell2.length();

    vector<vector<int>> matrix (p+1, vector<int>(q+1,0));

    // Algorithm which make the 2D-array to find the distance
    for (int i=0; i<=p; i++){
        for (int j=0; j<=q; j++){
            if (i==0){
                matrix[i][j] = j;
            } 
            else if (j==0){
                matrix[i][j] = i;
            } 
            else if (Spell1[i-1] == Spell2[j-1]){
                matrix[i][j] = matrix[i-1][j-1];
            } 
            else{
                matrix[i][j] = 1 + min({matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1]});
            }
        }
    }
    return matrix[p][q]; // last element of the matrix will be distance
}


// Function to find the suggestions for misspelled word
vector<string> Find_Suggestions(const string &spell, int change) const{
        vector<string> suggestions;

        // calling Find_Suggestions_Helper function to get the all suggestions for misspelled word
        Find_Suggestions_Helper(root, "", spell, change, suggestions);
        return suggestions;
    }


// Helper function for finding suggestion recursively
void Find_Suggestions_Helper(TrieNode *node, const string &dicWord, const string &spell, int change, vector<string> &suggestions) const{
        
        // will return when reach to the end of a branch in trie
        if (node==nullptr){
            return;
            }

        //size of the dictionary word should be less then or euqal to (input word + change), if not then return
        if (dicWord.size() > spell.size()+change){
            return;
        }

        if (node->isWord && dicWord.size() <= spell.size()+change){
            // calling Levenshtein_Distance function to find the distance beetween input word and dictionary word
            int distance = Levenshtein_Distance(dicWord, spell);
            
            // make dictionary word as suggestion if it met with the required change
            if (distance == change){
                suggestions.push_back(dicWord);
            }
        }

        // Recursively calls itself for each child node of the current node, appending the corresponding character to dicWord.
        // The recursion continues until all branches of the trie are traversed or until the length constraint is met.
        for (char ch='a'; ch<='z'; ch++){
            Find_Suggestions_Helper(node->children[ch-'a'], dicWord+ch, spell, change, suggestions);
        }
    }  

};
