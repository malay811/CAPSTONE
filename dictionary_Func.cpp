#include <iostream>
#include<fstream>// for file-handling
#include<string>// for string
using namespace std;
//function that read words from file and insert into trie.
void insertWordsFromFileToTrie(const string &filename, Trie &dictionary)//Use const keyword for not changing file name and  this '&' for avoid duplication.(Pass by Reference)
{
    ifstream file(filename);
    // open the file with the name provided in the filename parameter for reading.
     //Before proceeding, the code checks if the file was successfully opened. 
    if(file.is_open())
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


//function to write content back into the file
void WriteInToFile(const string &filename, const string &content)
// This funcation take 2 parameter first is filename and second is the content writing to the filename's file
{
    ofstream file(filename);// This line create output file stream named file,and open filename's file to writing
    
    if(file.is_open())//check file is open or not
    {
        file<<content;//write content into the file
        file.close();//close the file
    }
    else{
        cout<<"Error to writing the content to file "<<filename <<endl; //error message for not opening file
    }
}

// Function to read the content of a text file
string readFile(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening text file: " << filename << endl;
        return "";
    }

    string content;
    string line;
    while (getline(file, line))
    {
        content += line + "\n";
    }
    file.close();
    return content;
}
