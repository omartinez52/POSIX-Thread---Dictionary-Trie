/**
 * @file populatetree.cpp
 * @author Omar Martinez
 * @brief Single thread function which reads words from a file to store into a
 *        dictionary trie data structure. 
 * @dueDate 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "populatetree.h"
#include "EXEC_STATUS.h"

using namespace std; 

/**
 * PopulateTree()
 *  - Opens file for reading to populate dictionary trie.
 *  - Tokenizes words from each file and uses delimiters to extract unwanted
 *    characters from lines read from file.
 *  - Tokenzied words are stored in dictionary trie data stucture.
 * 
 * @param VoidPtr 
 * @return void* 
 */
void * PopulateTree( void * VoidPtr )
{
    // temp data structure pointer
    EXEC_STATUS *temp = (EXEC_STATUS*) VoidPtr;
    // open file for reading 
    ifstream dictStream(temp->filePath[DICTSRCFILEINDEX]);
    // delimiter string to separate words
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    // holds string read from each line of file
    string line_c;
    // read dictionary file line by line
    if(dictStream.is_open()){
        // loop through file
        while(getline(dictStream,line_c)){
            // count number of bytes from the line read from file.
            *(temp->numOfCharsProcessedFromFile[DICTSRCFILEINDEX]) += (line_c.length()+1);
            // create array of char intialized with length of line from file
            char str[line_c.length()+1];
            // copy string to char array initialized with length of string
            strcpy(str,line_c.c_str());
            // tokenize array
            char* word = strtok(str,delimiters);
            // loop through each word of the line
            while(word != nullptr){
                if(!(temp->dictRootNode->add(word))){
                    cout << "Word could not be inserted.\n";
                }
                temp->wordCountInFile[DICTSRCFILEINDEX]++;
                // read next token
                word = strtok(NULL,delimiters);
            }
        }
    }
    // close open file
    dictStream.close();
    // changing flag to true once thread function complete
    temp->taskCompleted[DICTSRCFILEINDEX] = true;
    return NULL;
}