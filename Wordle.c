#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Wordle.h"
/*
 * This file holds the bulk of the program, outputs the menu options, reads through the dictionary and
 * outputs the results of the program
 */


/* Reads in the dictionary file /usr/share/dict/words and returns the number of 5-character
words. All valid 5-character words should be written to the passed-in c-string array.*/
int loadDictionary(char *[]){
    // temp array for use creating dictionary array
    char temp[100];
    // dictionary consisting of up to 10,000 words up to 5 characters long;
    char dictionaryArray[100000][6];
    // creating pointer to open dictionary
    FILE *dictptr;
    dictptr = fopen("/usr/share/dict/words", "r");
    // checking if file is opened correctly
    if (NULL == dictptr) {
        printf("File did not open\n");
    }
    // copying all 5 letter words, without ' in the 4th position to dictionary
    // array counter to check how many words found
    int wordNum = 0;
    for (int i = 0; i < 102401; i++) {
        fscanf(dictptr, "%s", temp);
        if (strlen(temp) == 5 && temp[3] != '\'') {
            *dictionaryArray[wordNum] = *(char *) malloc(sizeof(temp));
            memcpy(dictionaryArray[wordNum], temp, 5);
            wordNum++;
        }
    }
    // closing stream
    fclose(dictptr);

    return wordNum;
}


/*Prompts the user to enter in the Wordle clue as requested in the sample output and returns the
provided characters without spaces.*/
char * promptUser(){
    static char user_input[1000];

    printf("Enter your query now: ");
    fgets(user_input, 20, stdin);
    user_input[strlen(user_input) - 1] = '\0';
    int length = strlen(user_input);
    int k, j;
    char *output = user_input;
    for (k = 0, j = 0; k < length; k++, j++) {
        if (user_input[k] != ' ')
            output[j] = user_input[k];
        else
            j--;
    }
    output[j] = 0;
    length = strlen(user_input);
    int maxLength = 5;

    if (length > maxLength) {
        printf("toooo many characters, only going to use the first 5;\n");
    }

return user_input;
}

/*Processes the word list of size num5 based on the 5 characters provided.*/
void processGuess(char *[], int num5, char, char, char, char, char);


/* Prints out the list of viable words without duplicates only if there is more than one known letter.*/
void printResults(char *[], int){
    static char user_input[1000];
    char dictionaryArray[100000][6] = {"hello"};
    int wordNum = 0;
    if (isupper(user_input[0])) {
        int counter = 0;
        for (int i = 0; i < wordNum; i++) {
            if (dictionaryArray[i][0] == user_input[0]) {
                counter++;

            } else if (dictionaryArray[i][0] == tolower(user_input[0])) {
                counter++;

            }
        }
        printf("Found %d words starting with %c", counter, user_input[0]);
    }
    for (int k = 1; k < 5; k++) {
        if (isupper(user_input[k])) {
            int counter = 0;
            for (int i = 0; i < wordNum; i++) {
                if (dictionaryArray[i][k] == user_input[k]) {
                    counter++;
                } else if (dictionaryArray[i][k] == tolower(user_input[k])) {
                    counter++;

                }
            }
            printf("\nFound %d words with %c in position %d", counter, user_input[k], k + 1);
        }
    }


}

/*Starts the process of the Wordle assistant. This should be the only function call in your provided
main method and should handle all expected functionality. */
void helpMe(){
    char user_input[1000];
    char temp[100];
    char dictionaryArray[100000][6];
    FILE *dictptr;
    dictptr = fopen("/usr/share/dict/words", "r");
    if (NULL == dictptr) {
        printf("file can't be opened \n");
    }
    printf("5 letter words are: \n");

    int wordNum = 0;

    for (int d = 0; d < 102401; d++) {
        fscanf(dictptr, "%s", temp);
        if (strlen(temp) == 5 && temp[3] != '\'') {
            *dictionaryArray[wordNum] = *(char *) malloc(sizeof(temp));
            memcpy(dictionaryArray[wordNum], temp, 5);
            wordNum++;
        }
    }
    fclose(dictptr);
    printf("\nWelcome to the Wordle Assistant!\n");
    printf("Processing Dictionary\n");
    printf("%d out of 102401 words in the dictionary are 5 characters!\n\n", wordNum);
    printf("Enter the Wordle clues using the following scheme:\n");
    printf("         A-Z for a known letter in the right position\n");
    printf("         a-z for a letter that is correct in the wrong position\n");
    printf("         * for unknown letter\n");
    printf("         Separate each with a space (e.g., T * G i R)\n");
    printf("Enter your query now: ");
    fgets(user_input, 20, stdin);
    user_input[strlen(user_input) - 1] = '\0';
    int length = strlen(user_input);
    int k, j;
    char *output = user_input;
    for (k = 0, j = 0; k < length; k++, j++) {
        if (user_input[k] != ' ')
            output[j] = user_input[k];
        else
            j--;
    }
    output[j] = 0;
    length = strlen(user_input);
    int maxLength = 5;

    if (length > maxLength) {
        printf("toooo many characters, only going to use the first 5;\n");
    }


    if (isupper(user_input[0])) {
        int counter = 0;
        for (int i = 0; i < wordNum; i++) {
            if (dictionaryArray[i][0] == user_input[0]) {
                counter++;

            } else if (dictionaryArray[i][0] == tolower(user_input[0])) {
                counter++;

            }
        }
        printf("Found %d words starting with %c", counter, user_input[0]);
    }
    for (int k = 1; k < 5; k++) {
        if (isupper(user_input[k])) {
            int counter = 0;
            for (int i = 0; i < wordNum; i++) {
                if (dictionaryArray[i][k] == user_input[k]) {
                    counter++;
                } else if (dictionaryArray[i][k] == tolower(user_input[k])) {
                    counter++;

                }
            }
            printf("\nFound %d words with %c in position %d", counter, user_input[k], k + 1);
        }
    }
    char testMatch[6];
    int numOpt = 0;
    int length2 = strlen(testMatch);
    int numCapitals = 0;
    int numLowerLetters=0;
    for (int i = 0; i <= length2; i++) {
        if (user_input[i] >= 'A' && user_input[i] <= 'Z') {
            numCapitals++;
        }
    }
    for (int i = 0; i <= length2; i++) {
        if (user_input[i] >= 'a' && user_input[i] <= 'z') {
            numLowerLetters++;
        }
    }
    int totallettersMatchNeeded = numCapitals + numLowerLetters;
    if ( totallettersMatchNeeded > 1) {
        printf("\nViable Options:\n");
    }

    int numMatch;
    for (int j = 0; j < wordNum; j++) {

        numMatch = 0;
        memcpy(testMatch, dictionaryArray[j], 6);


        for (int k = 0; k < 5; k++) {
            if (isupper(user_input[k])) {
                if (testMatch[k] == tolower(user_input[k])) {
                    numMatch++;

                }
            }
        }

        if ((numMatch == numCapitals)&&(numMatch > 1)) {
            printf("        %d: %s\n", numOpt, testMatch );
            numOpt++;
        }
    }
    if (totallettersMatchNeeded < 2) {
        printf("\nThere are too many possibilities! ");
    }
    printf("\n");


}
