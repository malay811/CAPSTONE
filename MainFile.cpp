int main(){
    // Trie object
    Trie dictionary;

    // Function to load dictionary file into trie
    InsertWordsFromFileToTrie("dictionary.txt", dictionary);

    // Take the path of input & output file as a string
    string input = "inputFile.txt";
    string output = "outputFile.txt";

    // Taking inputfile's text as a string
    string Content = readTextFile(input);

    // Callinng spell checker function
    string correctedText = spelling_check(Content, dictionary);

    // Write the corrected text into output file (Format will be same as input file)
    writeTextFile(output, correctedText);

    cout << "Spell checking has been completed. Su" << endl;
return 0 ;
}
