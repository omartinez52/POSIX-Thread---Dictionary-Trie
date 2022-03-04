/**
 * @file EXEC_STATUS.h
 * @author Omar Martinez
 * @brief Shared data structure among threads. Data will allow threads to
 *        communicate with each other. Data structure used for storing information
 *        on thread progress, thread completion, and also other variables
 *        necessary for threads to compete their work.
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef EXEC_STATUS_H
#define EXEC_STATUS_H

#include "dictionary.h"

/* number of files */
#define NUMOFFILES 2 
/* index for dictionary source file */
#define DICTSRCFILEINDEX 0 
/* index for testing source file */
#define TESTFILEINDEX 1 
/* index for dictionary file used for storing words in dictionary tree */
#define DICTSRCFILEINDEX 0 
/* index for testing file used for searching words in dictionary tree */
#define TESTFILEINDEX 1 
/* default number of progress marks for representing 100% progress */ 
#define DEFAULT_NUMOF_MARKS 50 
/* minimum number of progress marks for representing 100% progress */ 
#define MIN_NUMOF_MARKS 10 
/* place hash marks in the progress bar every N marks */ 
#define DEFAULT_HASHMARKINTERVAL  10 
/* default minimum number of dictionary words starting from a prefix for printing or 
writing to the output */ 
#define DEFAULT_MINNUM_OFWORDS_WITHAPREFIX  1 



/* Common data shared between threads */ 
typedef struct { 
  /** 
   * root node of the dictionary tree 
   */ 
  DictNode *dictRootNode; 

  /** 
   * parameters for printing progress bar  
   */ 
  int numOfProgressMarks; 
  
  int hashmarkInterval; 
  /** 
   * print a word and its count to the output file only if the  
   * number of dictionary words starting from the word is equal to or  
   * greater than this number  
   */ 
  int minNumOfWordsWithAPrefixForPrinting;  
   
  /** 
   * filePath[0] - file path for the dictionary vocabulary file 
   *               providing words to populate the dictionary tree 
   * filePath[1] - file path for the test source file 
   *               providing words to be used for testing  
   */ 
  const char  *filePath[NUMOFFILES]; 
   
  /** store total number of characters in files, total word count in files 
   * totalNumOfCharsInFile[DICTSRCFILEINDEX]  
   *   - number of total chars in the dictionary vocabulary file. 
   * totalNumOfCharsInFile[TESTFILEINDEX]  
   *   - number of total chars in the test file 
   */ 
  long  totalNumOfCharsInFile[NUMOFFILES]; 
 
  /** 
   * Use numOfCharsProcessedFromFile to track ongoing progress of threads.
   * numOfCharsProcessedFromFile[DICTSRCFILEINDEX]  
   *   - number of chars read in and processed from  
   *     the dictionary vocabulary file 
   * numOfCharsProcessedFromFile[TESTFILEINDEX]  
   *   - number of chars read in and processed from  
   *     the test file  
   */ 
  long  *numOfCharsProcessedFromFile[NUMOFFILES]; 
 
  /** 
   * wordCountInFile[DICTSRCFILEINDEX]  
   *   - number of total words in the dictionary vocabulary file. 
   * wordCountInFile[TESTFILEINDEX]  
   *   - number of total words in the test file 
   */  
  long  wordCountInFile[NUMOFFILES]; 
 
  /** 
   * completed flags indicate the completion of the thread logic, one 
   * for the populatetree thread, one for countwords thread 
   * 
   * taskCompleted[DICTSRCFILEINDEX]  
   *   *   - boolean flag to indicate whether the tree population  
   *     thread has completed the task: read words from the  
   *     dictionary source file and populate the tree 
   *   
   * taskCompleted[TESTFILEINDEX]  
   *   - boolean flag to indicate whether the counting words  
   *     thread has completed the task for reading and processing all words from the  
   *     test file. 
   */ 
  bool  taskCompleted[NUMOFFILES];  
} EXEC_STATUS; 

#endif