//Input: text file containing the book
//output: text file  in sorted order

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <stdlib.h>


#include "skiplist.hpp"


using namespace std;

// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
    for( string::iterator it = line.begin(); it != line.end(); ++it ) {
        if( !isalpha(*it) ) {
            if( (*it != '-' && *it != '\'') ||
               it == line.begin() || it+1 == line.end() ||
               !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
                *it = ' ';
            }
        } else {
            *it = tolower(*it);
        }
    }
}

void print(ostream & output, string & word) {
    output << word << endl;
}

int main(int argc, char *argv[]) {
    if( argc != 3 ) {
        cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
        exit(1);
    }
    
    ifstream fin;
    fin.open(argv[1]);
    if( !fin.is_open() ) {
        cerr << "Unable to open " << argv[1] << endl;
        exit(2);
    }
    
    ofstream fout;
    fout.open(argv[2]);
    if( !fout.is_open() ) {
        cerr << "Unable to open " << argv[2] << endl;
        exit(3);
    }
    fout.close();
    
    //Successfully load the txt file
    string line, word;
    //Trace the Line number,set to 0 initially
    int lineNum = 1;
    //Construct a SkipList to store all the antry
    SkipList MySkipList;
    
    while( !fin.eof() ) {
        
        getline(fin,line);
        lowercaseWords(line);
        istringstream iss(line, istringstream::in);
        
        //get a word
        while( iss >> word ) {
            
            int page = 1+lineNum/40 ;
            //see if this word is in the ordered array,if it is in the array then add one to the speficific occurences
            int found = MySkipList.Find(word, page);
            if(!found){
                MySkipList.Insert(word, page);
            }
            
        }
        
        lineNum++;
    }
    
     MySkipList.PrintInOrder(argv[2]);
    
    
}


