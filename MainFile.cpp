#include <iostream>
#include "Spell_check.cpp"
#include <windows.h>
#define green SetConsoleTextAttribute(h,2);
using namespace std;

int main(){
    // Trie object
    Trie dictionary;

    // Function to load dictionary file into trie
    InsertWordsFromFileToTrie("dictionary.txt", dictionary);

    // Take the path of input & output file as a string
    string input;
    cout<<"Enter file name : ";
    cin>>input;
    string output = "outputFile.txt";

    // Taking inputfile's text as a string
    string Content = readTextFile(input);

    // Callinng spell checker function
    string correctedText = spelling_check(Content, dictionary);

    // Write the corrected text into output file (Format will be same as input file)
    writeTextFile(output, correctedText);

    green cout << "\nSpell checking has been completed. Successfully!" << endl; white
    
return 0 ;
}
