#include<iostream>
#include<string>
#include<vector>
#include<sstream>


using namespace std ;

// this function will take the word one by one and input correct word in new file
string spelling_check(const string &text_file, const Trie &dictionary){

    string correct_spelling ;
    stringstream temp_file(text_file) ;
    string line ;

     while( (getline(temp_file, line)) ){
        string spelling ;
        stringstream ss(line) ;

        // append the whitespaces which presented before first of line
        bool flag1 = 0 ;

        for( char ch : line ){
            // if line only contained with whitespaces
            if( ch=='\n' ){
                flag1 = 1 ;
            }            
            if( !isspace(ch) )break ;
            else correct_spelling += ch ;
        }
        
        if( flag1 ) break ;

        // traverse through each word of the line stringstream 
        while( ss >> spelling ){

            string white_space ;

            // traverse till the next word and store whitespaces
            char ch;
            while (ss.get(ch) && isspace(ch)) {
                white_space += ch;
            }

            // if last char is new line then continue and take another line
            if( ch=='\n' ){
                correct_spelling += white_space ;
                continue ;
            }
            
            // Move the stringstream back one character because of previous loop to store whitespace
            ss.seekg(-1, ios_base::cur);
    
            // if the last character and/or first character is punctuation mark than removes it befire checking 
            char last_char = spelling.back() ;
            char first_char = spelling.front() ; 
            
            string mark_L,mark_F ;
            
            if(ispunct(last_char)){
                mark_L = string(1, last_char) ;
                spelling.pop_back() ;
            }
    
            if(ispunct(first_char)){
                mark_F = string(1, first_char) ;
                spelling.erase(0,1) ;
            }
    
            // if word is not present than suggest a word
            if( !dictionary.search(spelling) && !dictionary.search(convert_to_Lowercase(spelling)) ){
    
                vector<string> suggest_spelling = dictionary.Find_Suggestions(convert_to_Lowercase(spelling), dictionary) ;
    
                // if there is a suggestion for some wrong spelling
                if( !suggest_spelling.empty() ){
    
                    cout << endl << "--> The word '" << mark_F <<spelling << mark_L << "' is missplled.\nSuggestions for the misspelled word :" << endl ;
    
                    for(int i = 0; i < suggest_spelling.size(); i++){
    
                        bool condition = 1 ; 
                        for(int j = 0; j < spelling.length(); j++){
                            if (!isupper(spelling[j]))
                                condition = 0;
                        }
    
                        // format the word according to the wrong word 
                        if(condition){
                            suggest_spelling[i]=convert_to_Uppercase(suggest_spelling[i]);
                        }
                        else if(isupper(spelling[0])){
                            (suggest_spelling[i])[0]=toupper((suggest_spelling[i])[0]);
                        }
                        else{
                            suggest_spelling[i]=convert_to_Lowercase(suggest_spelling[i]);
                        }
                        cout << "(" << i + 1 << ") " << mark_F << suggest_spelling[i] << mark_L << endl;
                    }
                }
                
                if( !suggest_spelling.empty() ){
                    cout << "\nEnter the number of correct spelling (Type 0 to skip) : ";
    
                    // take the index of right word
                    int index;
                    while( !suggest_spelling.empty() ){
                        cin >> index;
    
                        if(index < 0 || index > suggest_spelling.size()){
                            cout << endl << "Please enter a valid index : " ;
                        }
                        else{
                            break;
                        }
                    }
    
                    if(index > 0){
                        // Replace it with correct word 
                        spelling = suggest_spelling[index - 1];
                    }
                }else{
                    if( !dictionary.search(spelling) && !dictionary.search(convert_to_Lowercase(spelling)) ){
                        cout << endl << "--> The word '" << mark_F <<spelling << mark_L << "' may be misspelled." << endl << endl ;
                    }
                }
                
            }
    
            // add a punctuation mark at front and end and also add whitespaces 
            correct_spelling += mark_F + spelling + mark_L + white_space ;
        }
         // add a new line before taking another line as a input 
         correct_spelling += "\n" ;
    }
    return correct_spelling ;
}
