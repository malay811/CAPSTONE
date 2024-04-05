#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std ;

// this is a helper function for spelling check function 
void spelling_check_helper( string&spelling , const Trie &dictionary , int threshold ){

    // if the spelling is wrong then this part will execute 
    if( !dictionary.search(spelling) && !dictionary.search(convert_to_Lowercase(spelling)) ){

        // store the suggested spelling usin find_suggestions function 
        vector<string> suggest_spelling = dictionary.Find_Suggestions(convert_to_Lowercase(spelling) , threshold ) ;

        // if the there exist a suggestion for a misspelled word
        if( !suggest_spelling.empty() ){

            cout << endl << "--> The word '" << spelling << "' is missplled.\nSuggestions for the misspelled word :" << endl ;

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
            cout << "\nEnter the number of correct spelling (Type 0 to skip ans -1 for more suggestion ) : ";

            // take the index of right word
            int index = 0 ;
            cin >> index ;    

            // if index is -1 then call helpere function with increased value of threshold
            if( index==-1 ){
                spelling_check_helper( spelling , dictionary , ++threshold ) ;
                index = 0 ;
            }

            // if index is wrong then ask the user for correct index
            if( index < -1 || index >suggest_spelling.size() ){
                cout << "Enter valid index : " ;
                cin >> index ;
            }

            if(index > 0  && index<=suggest_spelling.size() ){
                // Replace the word with correct word 
                spelling = suggest_spelling[index - 1] ;
            }
        }else{
            // if there is no suggestions then call heper function with increasing threshold value
            spelling_check_helper( spelling , dictionary , ++threshold ) ;
        }

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
            int threshold = 1 ;

            // if word is not present than suggest a word
            suggestion_helper( spelling , dictionary , threshold ) ;

            // add a punctuation mark at front and end 
            correct_spelling += mark_F + spelling + mark_L + white_space ;

        }
        // add the new line in corrected_text 
        correct_spelling += "\n" ;
    }

    return correct_spelling ;
}
