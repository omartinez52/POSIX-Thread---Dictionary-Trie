/**
 * @file countwords.h
 * @author Omar Martinez
 * @brief Single thread function which opens a file to read words from. Checks 
 *        if word is in dictionary trie data structure. If found, count the 
 *        number of words in the trie that begin with word from file and output
 *        to file.
 * @version 0.1
 * @dueDate 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef COUNTWORDS_H
#define COUNTWORDS_H

void * CountWords( void * VoidPtr );

#endif