## Operating SystemsnAssignment: Dictionary Trie - POSIX Thread Implementation

---

#### Summary:

In this assignment, separate POSIX threads used to accomplish similar flow of
operations of building and searching a Dictionary Trie, with added functions for using
optional command line arguments and displaying task progress.

Program starts from the main thread, which reads and processes command line
arguments, creates and initializes a shared data structure to be shared between the main
thread and worker threads, then spawns two worker threads to carry out the following
sequence of logic in that order:

1. populatetree thread for reading words from the dictionary source file and populating a dictionary tree, and
2. countwords thread for reading words from a test file, and for every word read in from the test file:

- search and count the number of words in the dictionary tree that start with this word,
- if the count is equal to or greater than the number specified by an optional command line argument (default is 1 if not specified), print this word and the count (separated by a space) to a file named countwords_output.txt, ONE line per word, in the exact format as:
  - hour 10
  - ‘hour 10’ here means for the ‘hour’ read from test file, there are 10 words in the dictionary tree that start with ‘hour’.

The dictionary tree is a tree storing a set of words (or strings), with each word stored along a
tree path. Starting from the child nodes of the root node, each tree node represents a single
character or letter of the word. Each node contains a collection of child nodes representing the
next set of possible characters to continue the word from the current node. A dictionary tree
constructed this way supports very efficient search and insert operations, in O(K) time with K
being the length of the word searched or inserted.
For this implementation, valid word characters are:

- alphabet characters from a to z (note: big case letters A to Z would be equivalent to
  a to z, all operations should be case-insensitive, as well as the autograding part)
- the apostrophe ' character.

## Table of Contents

1. [General Info](#general-info)
2. [Specification](#specifications)
3. [Preparation](#preparation)
4. [Collaboration](#collaboration)

### General Info

---

The main thread will spawn the populatetree and countwords threads at the same time,
then let the two worker threads coordinate with each other to ensure the order of
execution.

While the worker threads carry out their respective task, the main thread monitors and
displays the execution progress of each worker thread.

Note all communication, coordination / synchronization among the threads is
accomplished by using the shared data structure EXEC_STATUS.

## Specification

---

- Compilation and execution
  -Create Makefile for compiling your source code.
  - The make file must create the executable with a name as dicttest.
  - Your code must compile and run correctly on edoras.sdsu.edu, regardless of where you wrote, compiled, and tested your program.
- User Interface

  - The executable requires two mandatory command line arguments and accepts a few optional arguments.
    Optional arguments:
    -p N : N progress marks (either hyphen or #) for displaying 100% progress of a thread execution, default is 50 if not specified. Minimal number is 10. If a number less than 10 is specified, program should output error message and exit gracefully.

  -h N : place a hash mark “#” in the progress bar every N characters, default is 10 if not specified. If an out-of-range number (<=0 or > 10) is specified, program should print error message to the standard output and exit gracefully.
  -n N : print word and its count to an output file (countwords_output.txt) only if the number of dictionary words starting with the word is equal to or greater than N, default is 1 if not specified.
  Mandatory arguments:

  - The first argument specifies the file path to the source vocabulary text file that provides the words for building the dictionary tree.
  - Use dictionarysource.txt file as the source vocabulary text file for testing.
  - Appropriate error handling should be present if the file is not existent or cannot be opened.
  - The second argument specifies the file path to the text file that provides the words to be searched in the dictionary tree.
  - testfile1.txt is given for your testing.
  - Auto-grading on gradescope will use all or part of testfile1.txt.
  - Appropriate error handling should be present if the file is not existent or cannot be opened.
  - Program hs minimal error checking on whether the mandatory command line arguments are provided from execution, fail gracefully when there is a wrong number of arguments.

- Output file countwords_output.txt
  - Command line argument "/dicttest dictionarysource.txt testfile1.txt -p 40 -h 5 -n 3 " should print to standard output 40 progress bars. Every 5th progress bar is a '#' character. Print to file words starting with the word is equal to or greater than 3.
- Shared data structure among threads
  -The shared data structure among the three threads is used for:
  1. the worker threads to update ongoing execution progress of their logic: use the number of characters read from the file and processed by the worker thread as the progress indicator,
  2. the main thread to read and display the progress of worker thread executions,
  3. ensuring the precedence constraint of thread logic executions, i.e., populatetree thread logic must happen before the countwords thread logic, and
  4. ensuring the proper exit of the threads.
- Display of the progress bar

  - The main thread monitors and displays the progress of each thread execution. For displaying the progress bar along each thread execution, uses a loop to compute the percentage characters processed from files divided by total characters in files and add to a progress bar representing the amount of progress that has been made. Most characters are hyphens (-), but every Nth progress mark should be displayed as a number sign (#).
  - A sample session should appear as follows; you start the execution of dicttest
    program from the console prompt:
    ./dicttest dictionarysource.txt testfile1.txt -p 40 -h 5 -n 3

  The output format of your program to the standard output should be EXACTLY the
  same as below:

  ----#----#----#----#----#----#----#----#
  There are 116687 words in dictionarysource.txt.
  ----#----#----#----#----#----#----#----#
  There are 125322 words in testfile1.txt.

- Code structure
  - Separate the logic of main thread, populatetree thread, and countwords thread to separate code files.

## Preparation

---

- Effectively process mandatory and optional command line arguments are store all data into shared data structure used amongst threads.
- Seperate Dictionary Trie implementation logic amongst each thread.
- Spawn two worker threads: populatetree and countwords.
- Populate tree thread will open dictinary source file and begin populating Dictionary Trie while countwords thread waits for its completion.
- Count words thread will open test file and begin search dictionary trie and counting words then ouput word and count to file.
- Effective coordination amongst threads to populate tree, count words and output a progress bar.

## Collaboration

---

Solo collaboration to properly develop a POSIX Thread implementation of a dictionary trie that passes
all test cases when reading records.

Omar Martinez (REDID:818749029) - Contribution:
