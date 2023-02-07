/*
 * This file works as the header file to Wordle.c, acting behind the scenes and initializing
 * functions for multi file use
 */

#ifndef WORDLE_H
#define WORDLE_H

/* Reads in the dictionary file /usr/share/dict/words and returns the number of 5-character
words. All valid 5-character words should be written to the passed-in c-string array.*/
int loadDictionary(char *[]);

/*Prompts the user to enter in the Wordle clue as requested in the sample output and returns the
provided characters without spaces.*/
char *promptUser();

/*Processes the word list of size num5 based on the 5 characters provided.*/
void processGuess(char *[], int num5, char, char, char, char, char);

/* Prints out the list of viable words without duplicates only if there is more than one known letter.*/
void printResults(char *[], int);

/*Starts the process of the Wordle assistant. This should be the only function call in your provided
main method and should handle all expected functionality. */
void helpMe();

#endif