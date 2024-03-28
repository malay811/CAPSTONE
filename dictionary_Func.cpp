#include <iostream>
#include<fstream>
using namespace std;

//funcation that read words from file and insert into trie.
void readWordsFromFileToTrie(string filename, Trie &dictionary)
{
    ifstream file(filename);
    // open the file with the name provided in the filename parameter for reading.
    if(file.is_open())
    //Before proceeding, the code checks if the file was successfully opened. 
    {
        string word;
        while(getline(file,word))
        {
            dictionary.insert(word);
        }
        //while loop read the file till the end of file,and inserting it by word variable into trie .
        
        file.close();//file close
    }
    else{
        cout << "Unable to open dictionary file: " << filename << ". Please ensure you have the necessary permissions to read the file." << endl;
    }
}
