/**
 * @file main.cpp
 * @author Omar Martinez
 * @brief Main .cpp file which will spawn two worker threads. One thread will
 *        will populate a dictionary trie with vocabulary, while another will
 *        search through the dictionary trie upon its completion. Shared data 
 *        structure (EXEC_STATUS) will allow threads to communicate. Main will
 *        stdout a progress of each thread via a progress bar.
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <pthread.h>
#include "dictionary.h"
#include "EXEC_STATUS.h"
#include "populatetree.h"
#include "countwords.h"

using namespace std;

// function prototype to delete dangling pointers
void DeletePointers(EXEC_STATUS *ex);

// function prototype to read commands line arguements and store results
bool CommandLineArguments(int argc, char** argv, EXEC_STATUS *ex);

// function prototype to print the progress bar
void PrintProgressBar(EXEC_STATUS *ex, int fileIndex);

int main(int argc, char **argv){
    // new, shared data structure pointer
    EXEC_STATUS *ex = new EXEC_STATUS();
    // check command line arguments before continuing program
    // exit program if errors with command line arguments
    if(!CommandLineArguments(argc, argv, ex)){
        DeletePointers(ex);
        return 1;
    }
    // initialize pointers
    ex->dictRootNode = new DictNode();
    ex->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = new long();
    ex->numOfCharsProcessedFromFile[TESTFILEINDEX] = new long();
    
    // spawining new threads
    pthread_t populatetree, countwords;
    // start thread to begin populating dicationary tree
    pthread_create(&populatetree, NULL, &PopulateTree, (void *) ex);
    // start thread to begin searching and counting words in dictionary tree
    pthread_create(&countwords, NULL, &CountWords, (void *) ex);

    // print progress bar for populating dictionary tree
    PrintProgressBar(ex, DICTSRCFILEINDEX);
    // print progress bar for counting words in the dictionary tree
    PrintProgressBar(ex, TESTFILEINDEX);
    // delete newly created pointers
    DeletePointers(ex);
    return 0;
}

/*
* DeletePointers()
*   - Deletes newly created pointers to prevent memory leaks.
*/
void DeletePointers(EXEC_STATUS *ex){
    delete(ex->numOfCharsProcessedFromFile[DICTSRCFILEINDEX]);
    delete(ex->numOfCharsProcessedFromFile[TESTFILEINDEX]);
    delete(ex->dictRootNode);
    delete(ex);
}

/*
* PrintProgressBar()
*   - Outputs a progress bar for the progress a thread makes in its work.
*   - Keeps track of the number of marks added and the number needed to be added
*     given the percent of progress done by a thread.
*   - Outputs correct number of marks given by default or command line value.
*   @param shared data structure, file index
*/
void PrintProgressBar(EXEC_STATUS *ex, int fileIndex){
    // current marks printed, marks to add to progress bar
    int currMarks = 0, marksToAdd = 0;
    // percent of bytes processed
    double curPercent;
    // print progress marks for creating dictionary tree
    do
    {
        // current progress percent of number of chars processed
        curPercent = (double) *ex->numOfCharsProcessedFromFile[fileIndex]
                    /(double)ex->totalNumOfCharsInFile[fileIndex];
        // number of marks displayed given percent
        marksToAdd = int(curPercent * ex->numOfProgressMarks);
        // number of marks needed to add to # of marks already printed
        marksToAdd = abs(marksToAdd - currMarks);
        if(currMarks != ex->numOfProgressMarks){
            while(marksToAdd > 0){
                // check if next mark needs to be a hash interval mark (#)
                if((currMarks+1) % ex->hashmarkInterval == 0){
                    cout << '#';
                }
                else{
                    cout <<'-';
                }
                cout.flush();
                marksToAdd--;
                currMarks++;
            }
        }
    }while(currMarks != ex->numOfProgressMarks || !ex->taskCompleted[fileIndex]);
    // print the total number of words read from file
    cout << "\nThere are "<<ex->wordCountInFile[fileIndex];
    cout << " words in "<<ex->filePath[fileIndex]<<".\n";
}

/*
* CommandLineArguments()
*   - Checks if mandatory command line arguments were included.
*   - File paths passed in as mandatory command line arguments stored in data 
*     structure to be shared amongst threads.
*   - Counts the number of bytes from files and stores them in data structure.
*   - Loops through optional command line arguemnts and stores given values into
*     shared data structure.
*   
*   @param: argument count, pointer to array of arguments, shared data structure
*   @return: - True if files able to be opened and if command line arguments
*              were passed appropriately.
*            - False otherwise.
*
*/
bool CommandLineArguments(int argc, char **argv, EXEC_STATUS *ex){
    // check if mandatory command line arguments were included
    if(argc < 3){
        cout<< "Program must include mandatory command line arguments\n";
        return false;
    }

    // storing file path to correct index
    ex->filePath[DICTSRCFILEINDEX] = argv[1];   // dictionary filepath
    ex->filePath[TESTFILEINDEX] = argv[2];      // test file path

    // reading number of bytes from each file and storing value
    for(int i = 1; i <= 2; i++){
        ifstream in_file(argv[i], ios::binary);
        if(in_file.is_open()){
            in_file.seekg(0, ios::end);
            ex->totalNumOfCharsInFile[i-1] = in_file.tellg();
            in_file.close();
        }
        else{
            // print error message if file could not be opened.
            cout << "Unable to open <<"<<argv[i]<<">>\n";
            return false;
        }
    }

    // initialize variables to default value
    ex->numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    ex->hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    ex->minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;

    // loop through optional command line arguments
    for(int i = 3; i < argc; i++){
        // check progress mark command line argument
        if(string(argv[i]) == "-p"){
            // check if next index is out of bounds
            if(i+1 != argc){
                // check if next argument is a digit
                if(string(argv[i+1]).find_first_not_of("0123456789") == string::npos){
                    // check if appropriate number of progress marks
                    if(stoi(string(argv[i+1])) < MIN_NUMOF_MARKS){
                        cout << "Number of progress marks must be a number and at least 10\n";
                        return false;
                    }
                    ex->numOfProgressMarks = stoi(string(argv[i+1]));
                }//if no number given, use default
            }
        }
        // check hashmark command line argument
        if(string(argv[i]) == "-h"){
            // check if next index is out of bounds
            if(i+1 != argc){
                // check if next argument is a digit
                if(string(argv[i+1]).find_first_not_of("0123456789") == string::npos){
                    int marks = stoi(string(argv[i+1]));
                    // check if appropriate number of progress marks
                    if(marks<=0 || marks > MIN_NUMOF_MARKS){
                        cout << "Hash mark interval for progress must be a number,\n"; 
                        cout << " greater than 0, and less than or equal to 10 \n";
                        return false;
                    }
                    ex->hashmarkInterval = marks;
                }//if no number given, use default
            }
        }
        // check number of words with prefix for printing command line argument
        if(string(argv[i]) == "-n"){
            // check if next index is out of bounds
            if(i+1 != argc){
                // check if next argument is a digit
                if(string(argv[i+1]).find_first_not_of("0123456789") == string::npos){
                    // check if appropriate number of progress marks
                    int words = stoi(string(argv[i+1]));
                    ex->minNumOfWordsWithAPrefixForPrinting = words;
                }//if no number given, use default
            }
        }
    }
    return true;
}