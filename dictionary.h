#ifndef DICTIONARY_H
#define DICTIONARY_H
 /**
 *  Disassembler.h
 *  - Instantiates all  variables to be initialized during execution
 *    of dictionary.cpp.
 *  - Instantiates all class function prototypes for execution of 
 *    dictionary.cpp. 
 *  @course: [CS480-01 : (Professor: B. Shen)]
 *  @authors:
 *      - [Omar Martinez(REDID:818749029)]
 */
#define NUMOfCHARS 27 /* a-z plus ' */ 
using namespace std;
class DictNode{
    public:
        bool isWord;
        char character;
        DictNode* next[NUMOfCHARS];
        int add(const char* remainingChars, const char* wordBeingInserted = nullptr);
        DictNode* findEndingNodeOfAStr(const char* remainingStr, const char* strBeingSearched = nullptr);
        void countWordsStartingFromANode(int &count);
        bool search(const char* remainingStr);
        //DictNode newNode(char character);
        DictNode();
};
#endif