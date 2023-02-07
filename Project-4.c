
#include "Wordle.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This program is designed to accept 5 user inputs, characters including uppercase, lowercase, and astrisks.
 * When a user inputs a set of 5 characters, the program searchs a dictionary library for words matching
 * the pattern. If the user Inputs a capital letter, it acts a green block, and the program searches words with
 * the character in the matching position. Lowercase inputs act as yellow blocks, meaning the letter is
 * in the word, but the user is unsure of its location. Finally the astrisk (*) is for any other unknown
 * character value. This file acts as a driver for the program
 */

int main() {

    // array accepting user input up to 1000 chars
    char user_input[1000];
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

    // outputting menu
    printf("\nWelcome to the Wordle Assistant!\n");
    printf("Processing Dictionary\n");
    printf("%d out of 102401 words in the dictionary are 5 characters!\n\n",
           wordNum);
    printf("Enter the Wordle clues using the following scheme:\n");
    printf("         A-Z for a known letter in the right position\n");
    printf("         a-z for a letter that is correct in the wrong position\n");
    printf("         * for unknown letter\n");
    printf("         Separate each with a space (e.g., T * G i R)\n");
    printf("Enter your query now: ");

    // receive up to 20 user inputs
    fgets(user_input, 20, stdin);
    user_input[strlen(user_input) - 1] = '\0';
    int length = strlen(user_input);
    int i, k;
    char *tempPtr = user_input;
    // removing the whitespace between chars
    for (k = 0, i = 0; k < length; k++, i++) {
        if (user_input[k] != ' ')
            tempPtr[i] = user_input[k];
        else
            i--;
    }
    tempPtr[i] = 0;
    length = strlen(user_input);

    // ensuring that they did not enter more than 5 possible chars
    int maxLength = 5;
    if (length > maxLength) {
        printf("too many character... I will use the first 5 anyways\n");
    }

    // checking through dict for how many words match positions
    // checking starting position
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
    // checking positions 2-5
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
            printf("\nFound %d words with %c in position %d", counter, user_input[k],
                   k + 1);
        }
    }

    //declaring more variables
    char testMatch[6];
    int numOpt = 0;
    length = strlen(testMatch);
    int numCapitals = 0;
    int numLowerLetters = 0;

    // testing to see the number of user entered uppercase/lowercase chars
    for (int i = 0; i <= length; i++) {
        if (user_input[i] >= 'A' && user_input[i] <= 'Z') {
            numCapitals++;
        } else if (user_input[i] >= 'a' && user_input[i] <= 'z') {
            numLowerLetters++;
        }
    }
    // combining lower + uppercase chars in user input
    int totallettersMatchNeeded = numCapitals + numLowerLetters;
    printf("\nTotal letter matches need is %d", totallettersMatchNeeded);
    // printing options
    if (totallettersMatchNeeded > 1) {
        printf("\nViable Options:\n");
    }
    // counts number of letter matches found per word
    int matchCounter;
    // used to enable extra credit allowing check of lower case letters
    int fakebool;

    for (int i = 0; i < wordNum; i++) {
        matchCounter = 0;
        fakebool = 0;

        // copying word to a test array for matching
        memcpy(testMatch, dictionaryArray[i], 6);

        // looping through uppercase letters, testing if positions match
        for (int k = 0; k < 5; k++) {
            if (isupper(user_input[k])) {
                if (testMatch[k] == tolower(user_input[k])) {
                    matchCounter++;
                    fakebool++;
                }
            }
        }
        // extra credit
        // looping through lower case
        // loop through 5 positions in a word
        for (int k = 0; k < 5; k++) {
            // check to make sure that all of the capital letters matched
            if (fakebool == numCapitals) {
                // loop through the lowercase use rinputs
                for (int j = 0; j < 5; j++) {
                    if (islower(user_input[k])) {
                        if (testMatch[j] == user_input[k]) {
                            matchCounter++;
                            break;
                        }
                    }
                }
            }
        }

        // if there is over 1 char inputted, and the number of matches is equal to
        // the number of total chars print the output
        if ((matchCounter == totallettersMatchNeeded) &&
            (totallettersMatchNeeded > 1)) {
            printf("        %d: %s\n", numOpt, testMatch);
            numOpt++;
        }
    }

    // if there is less than 2 chars given, output error message
    if (totallettersMatchNeeded < 2) {
        printf("\nThere are too many possibilities!\n");
    }
    printf("\n");

    return 0;
}
