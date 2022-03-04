/**
 *  dictionary.cpp
 *  - Constructor initializes instance variables to false and null.
 *  - Adds words, read from dictionary file, into a dictionary Trie.
 *  - Searches for words, from test file, in dictionary trie.
 *  - Counts the # of words that begin with string passed in parameters.
 *  @course: [CS480-01 : (Professor: B. Shen)]
 *  @authors:
 *      - [Omar Martinez(REDID:818749029)]
 */
#include <iostream>
#include <cstring>
#include "dictionary.h"

using namespace std;
#define NUMOfCHARS 27 /* a-z plus ' */ 
/**
*   DictNode::DictNode()
*       - Default constructor.
*       - Initializes isWord to false.
*       - Initializes next array to null values.
*/
DictNode::DictNode(){
    isWord = false;
    for(int i = 0; i < NUMOfCHARS; i++){
        next[i] = NULL;
    }
}
/**
*   DictNode::add()
*       - Iterates through characters of string passed in parameters.
*       - Characters in string dictate which index to store new node into.
*       - If Node already exists or if one is created, move temp pointer to that node.
*       - After iterating through string, set final node->isWord to true;
*       @param: string to insert, string for testing/debuggin
*       @return: true if word was inserted, false otherwise.
*/
int DictNode::add(const char* remainingChars, const char* wordBeingInserted){
    // temporary pointer to root node.
    DictNode* temp = this;
    int index;
    for(int i = 0; i < strlen(remainingChars); i++){
        // checks if characters is uppercase
        if(remainingChars[i] >= 65 && remainingChars[i] <= 90)
            index = remainingChars[i] - 65;
        // checks if character is lowercase
        else if(remainingChars[i] >= 97 && remainingChars[i] <= 122)
            index = remainingChars[i] - 97;
        // checks if character is an apostrophe
        else if(remainingChars[i] == 39)
            index = 26;
        // character not found, return false;
        else
            return false;
        // if index is null, insert new node into array
        if(temp->next[index] == NULL){
            DictNode* node = new DictNode();
            temp->next[index] = node;
        }
        // move pointer to next node.
        temp = temp->next[index];
    }
    temp->isWord = true;
    return true;
}
// bool DictNode::search(const char* remainingStr){
//     DictNode* temp = this;
//     int index;
//     for(int i = 0; i < strlen(remainingStr); i++){
//         if(remainingStr[i] >= 65 && remainingStr[i] <= 90)
//             index = remainingStr[i] - 65;
//         else if(remainingStr[i] >= 97 && remainingStr[i] <= 122)
//             index = remainingStr[i] - 97;
//         else if(remainingStr[i] == 39)
//             index = 26;
//         // character not found, return false;
//         else
//             return false;
//         if(temp->next[index] == NULL)
//             return false;
//         else
//             temp = temp->next[index];
//     }
//     return temp->isWord;
// }
/**
*   DictNode::findEndingNodeOfStr()
*       - Iterates through characters of string passed in parameters.
*       - Characters in string dictate which index to move pointer to.
*       - Iterate through all nodes dictated by string character.
*       @param: string to insert, string for testing/debuggin
*       @return: node if word was found, null otherwise.
*/
DictNode* DictNode::findEndingNodeOfAStr(const char* remainingStr, const char* strBeingSearched){
    // temporary pointer to root node
    DictNode* temp = this;
    int index;
    // iterate through characters of string
    for(int i = 0; i < strlen(remainingStr); i++){
        // checks if character is uppercase
        if(remainingStr[i] >= 65 && remainingStr[i] <= 90)
            index = remainingStr[i] - 65;
        // checks if character is lowercase
        else if(remainingStr[i] >= 97 && remainingStr[i] <= 122)
            index = remainingStr[i] - 97;
        // checks if character is an apostrophe
        else if(remainingStr[i] == 39)
            index = 26;
        // character not found, return null pointer;
        else
            return NULL;
        // return null of character is not a child of parent node
        if(temp->next[index] == NULL)
            return NULL;
        // point to node at index dictated by current character in string
        else
            temp = temp->next[index];
    }
    // return pointer to last node
    return temp;
}
/**
*   DictNode::countWordsStartingFromANode()
*       - Recursively iterate through all non-null indices of node array.
*       - Increment count for every node where isWord is true.
*       @param: integer that stores # of words found.
*/
void DictNode::countWordsStartingFromANode(int &count){
    // increment count if node is the end of a word
    if(this->isWord)
        count++;
    // loop through each index of nodes children
    for(int i = 0; i < NUMOfCHARS; i++){
        // recursively loop through all non-null children in list
        if(this->next[i]){
            this->next[i]->countWordsStartingFromANode(count);
        }
    }
}