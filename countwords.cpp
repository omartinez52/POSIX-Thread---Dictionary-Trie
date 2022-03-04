/**
 * @file countwords.cpp
 * @author Omar Martinez
 * @brief Single thread function which opens a file to read words from. Checks 
 *        if word is in dictionary trie data structure. If found, count the 
 *        number of words in the trie that begin with word from file and output
 *        to file.
 * @dueDate 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "countwords.h"
#include "EXEC_STATUS.h"
#include "dictionary.h"


using namespace std; 

/**
 * CountWords() 
 *  - Opens test file used for searching dictionary trie.
 *  - Tokenizes words from each file and uses delimiters to extract unwanted
 *    characters from lines read from test file.
 *  - Tokenzied words are used for searching dictionary tree and end node is
 *    returned.
 *  - Tracks the count of words that begin with a word prefix from test file.
 *  - Outputs words and their count onto an output file.
 * @param VoidPtr 
 * @return void* 
 */
void* CountWords(void *VoidPtr){
    EXEC_STATUS *temp = (EXEC_STATUS*) VoidPtr;
    // count of words found with given prefix
    int count = 0;
    // holds string read from each line of file
    string line_c;
    // delimiter string to separate words
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    // do nothing while other thread is working
    while(!temp->taskCompleted[DICTSRCFILEINDEX]){}
    // open output file for printing output
    ofstream outStream;
    outStream.open("countwords_output.txt");
    // open input file to read from
    ifstream dictStream(temp->filePath[TESTFILEINDEX]);
    // read test file line by line
    if(dictStream.is_open()){
        // loop through file
        while(getline(dictStream,line_c)){
            // count number of bytes from the line read from file.
            *(temp->numOfCharsProcessedFromFile[TESTFILEINDEX]) += (line_c.length()+1);
            // create array of char intialized with length of line from file
            char str[line_c.length()+1];
            // copy string to char array
            strcpy(str,line_c.c_str());
            // tokenize array
            char* word = strtok(str,delimiters);
            // loop through each word of the line
            while(word != nullptr){
                DictNode* nodeFound = temp->dictRootNode->findEndingNodeOfAStr(word);
                if(nodeFound != NULL){
                    nodeFound->countWordsStartingFromANode(count);
                }
                if(count >= temp->minNumOfWordsWithAPrefixForPrinting){
                    outStream << word << " " << count << endl;
                }
                count = 0;
                temp->wordCountInFile[TESTFILEINDEX]++;
                word = strtok(NULL,delimiters);
            }
        }
    }
    // closing opened files
    dictStream.close();
    outStream.close();
    // changing flag to true once thread function complete
    temp->taskCompleted[TESTFILEINDEX] = true;
    return NULL;
}