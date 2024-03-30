#include<iostream>
#include<string>
#include<vector>
#include<sstream>


using namespace std ;

string spelling_check(const string& text_file, const Trie& dictionary){
    string correct_spelling;
    stringstream temp_file(text_file);
    string spelling ;

    while( temp_file >> spelling ){

        // if the last character is not alphabet than remove it 
        char last_char = spelling[spelling.length() - 1] ;

        string mark ;
        if( ispunct(last_char) ){
            mark = string(1,last_char) ;
            spelling.pop_back() ;
        }

        string lowercase_spelling = toLowerCase(spelling) ;
        
        // if word is not present than suggest a word 
        if( !dictionary.search(spelling) && !dictionary.search(lowercase_spelling) ){
            vector<string> suggest_spelling = dictionary.suggestCorrections(spelling, dictionary);

            // if there is a suggestion for some wrong spelling 
            if( !suggest_spelling.empty() ){
                cout << "Spelling for this word : '" << spelling << mark << "' is wrong. Suggestions :" << endl;

                for( int i=0 ; i<suggest_spelling.size() ; i++ ){
                    
                    // If first character is capital than also make suggested spelling's first char capital
                    if( spelling[0] <= 'Z' && spelling[0] >= 'A' ){
                        suggest_spelling[i] = (suggest_spelling[i])[0] + 32 ;
                    }
                    
                    cout << "(" << i+1 << ") " << suggest_spelling[i] << mark << endl ;
                }

                cout << "Enter the number of correct spelling or type 0 to skip ";
                int index ;

                while( 1 ){
                    cin >> index ;

                    if( index < 0 || index > suggest_spelling.size() ){
                        cout << endl << "Please enter valid index " << endl ;
                    }else{
                        break;
                    }
                }

                if( index > 0 ){
                    // Replace word 
                    spelling = suggest_spelling[index-1] ;
                }
            }
        }
        // add punctuation mark at the end 
        correct_spelling += spelling + mark + " " ;
    }
    return correct_spelling ;
}

