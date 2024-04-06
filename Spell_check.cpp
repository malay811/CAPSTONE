#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<cstring>
#include<windows.h>

#include "Trie.cpp"
#include "file_handling.cpp"

HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
#define red SetConsoleTextAttribute(h,4);
#define white SetConsoleTextAttribute(h,7);
#define yellow SetConsoleTextAttribute(h,6);
#define blue SetConsoleTextAttribute(h,1);
#define green SetConsoleTextAttribute(h,2);
#define cyan SetConsoleTextAttribute(h,11);

using namespace std ;

// this is a helper function for spelling check function 
void spelling_check_helper( string&spelling , const Trie &dictionary , int change ){

    // store the suggested spelling using Find_Suggestions function 
    vector<string> suggest_spelling = dictionary.Find_Suggestions(convert_to_Lowercase(spelling) , change ) ;

    // if there exist suggestions for the misspelled word
    if( !suggest_spelling.empty() ){

        cout << endl ;
        red cout << "--> The word '" << spelling << "' is missplled." << endl ; 
        yellow cout << "Suggestions for the misspelled word :" << endl ; white

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
            cout << "(" << i + 1 << ") " << suggest_spelling[i] << endl;
        }
    }

    // if there is a suggestions for misspelled word
    if( !suggest_spelling.empty() ){
        blue cout << "\nEnter the number correspond to correct spelling " ;
        cyan cout << "(Type 0 to skip and -1 for more suggestion) : "; white

        // take the index of right word
        int index ;
        cin >> index ;    

        // if index is -1 then call helpere function with increased value of threshold
        if( index==-1 ){
            spelling_check_helper( spelling , dictionary , ++change ) ;
            index = 0 ;
        }

        if(index > 0  && index<=suggest_spelling.size() ){
            // Replace the word with correct word 
            spelling = suggest_spelling[index - 1] ;
        }
    }else{
        // if there is no suggestions then call heper function with increasing threshold value
        spelling_check_helper( spelling , dictionary , change++ ) ;
    }
}

// spelling check function to take input and give suggestion and changes according to input 
string spelling_check(const string &text_file, const Trie &dictionary){

    string correct_spelling ;
    stringstream temp_file(text_file) ;
    string line ;

    // extract the line one by one untill end 
    while( (getline(temp_file, line)) ){
        string spelling ;
        stringstream ss(line) ;

        // store the whitespaces present in the starting of line 
        bool flag1 = 0 ;
        for( char ch : line ){
            if( ch=='\n' ){
                flag1 = 1 ;
            }            
            if( !isspace(ch) )break ;
            else correct_spelling += ch ;
        }

        // if line only containes whitespaces then moves towards next line ;
        if( flag1 ) continue ;

        // extract the words one by one from line 
        while( ss >> spelling ){

            string white_space ;

            // store the whitespace untill next word 
            char ch;
            while (ss.get(ch) && isspace(ch)) {
                white_space += ch;
            }

            if( ch=='\n' ){
                correct_spelling += white_space ;
                continue ;
            }
            
            // Move the stringstream back one character 
            ss.seekg(-1, ios_base::cur);

            // stores first and last punctuatin marks 
            string mark_L,mark_F ;
            
            for( int j=0 ; j<spelling.length() ; j++ ){
                if( !ispunct(spelling[j]) ) break ;
                mark_F += spelling[j] ;
            }

            for( int j=spelling.length()-1 ; j>=0 ; j-- ){
                if( !ispunct(spelling[j]) ) break ;
                mark_L += spelling[j] ;
            }

            reverse( mark_L.begin() , mark_L.end() ) ;

            // if words contains only puctuation marks then move to next word
            if( mark_F==spelling ){
                correct_spelling += spelling + white_space ; 
                continue ;
            }

            // remove the punctuation marks before performing operations on string 
            spelling.erase(0,mark_F.length()) ;
            spelling.erase(spelling.length()-mark_L.length()) ;

            // start the threshold value from 1
            int change = 1 ;

            // if the spelling is wrong then this part will execute 
            if( !dictionary.search(spelling) && !dictionary.search(convert_to_Lowercase(spelling)) ){

                // if word is not present than suggest a word
                spelling_check_helper( spelling , dictionary , change ) ;

            }

            // add a punctuation mark at front and end 
            correct_spelling += mark_F + spelling + mark_L + white_space ;

        }
        // add the new line in corrected_text 
        correct_spelling += "\n" ;
    }

    return correct_spelling ;
}
