/*!
@file       spellcheck.c
@author     Timothy Lee (timothykexin.lee@digipen.edu.sg)
@course     RSE 1201
@section    Tutorial 9
@Tutorial   Strings, arrays, pointers, structures and file I/O 
@date       12/11/2021
@brief      This file contains definitions of the functions str_to_upper, 
            words_starting_with, spell_check, word_lengths, and info. These functions 
            coupled with the declarations and definitions in qdriver.c and spellcheck.h 
            enables the executable file to perform rudimentary spell checks, word and 
            word length count. Through these functions, the checks would be not be case
            sensitive.
*//*______________________________________________________________________________________*/


#include <string.h>		// strcpy, strcmp, strlen                                   
#include <stdio.h>		// printf, fopen, fclose
#include "spellcheck.h"
#define MAX 100

/*!
@brief  This function converts all lowercase letters to uppercase and returns a pointer to 
        the first character of the string. The function works in-place, which means it 
        modifies the array that was passed in as a function parameter, without allocating a
        new array; the return object is the same value that was passed into the function, 
        similarly to strcpy and strcat. If the character in the string isn't a latin 
        lowercase letter, it does not convert it.

@param  i is declared as data type int
		string is a function parameter of a pointer to char
@return string 
*//*_______________________________________________________________________________________*/
char* str_to_upper(char* string) {
    //Loops to checks through the string array for latin lowercase to convert to uppercase.
    //It stops looping when the NULL character is detected
    for(int i = 0; string[i] != '\0'; i++){
        //checks for lowercase
        string[i] = string[i] >= 'a' && string[i] <= 'z' ? (char) (string[i]-'a'+'A') : string[i];
    }
    return string;   
}

/*!
@brief  This function counts the number of words that start with a given letter according to
        the file name of a dictionary text file. If the text file is unable to be opened
        this function returns FILE_ERR_OPEN. Otherwise, since the comparison of letter and relevant
        text in the dictionary text file is case sensitive, the function str_to_upper will 
        be called for proper comparison. 

@param  dictionary is a function parameter of a pointer to a const char
        letter is a function parameter of type char
        wordfile is declared as type FILE
        ch, counter is declared as data type int
        wordcnt is declared as data type unsigned long long int 
        line is an array of type char

@return FILE_ERR_OPEN if unable to open file
        wordcnt if file is accessable
*//*_______________________________________________________________________________________*/
WordCount words_starting_with(const char* dictionary, char letter) {
    FILE *wordfile = fopen(dictionary, "r");                                    //read only
    if (wordfile == NULL)                                                       //unable to open
        return FILE_ERR_OPEN;
    
    int ch, counter = 0; 
    unsigned long long int wordcnt = 0;                                         //same data type as WordCount
    char line[MAX];                                                             //'ambiguous' size enough to contain the length of a word in the line
    str_to_upper(&letter);                                                      //converts letter to uppercase

    while((ch = fgetc(wordfile)) != EOF) {
        //checks every single line of text as a word
        if(ch == '\n') {                                                        //detects newline then checks contents of array
            str_to_upper(line);                                                 //converts content to uppercase
            if(line[0] == letter)                                               //checks if first letter == letter
                wordcnt++;                                                      //increments wordcount if true
            counter = 0;                                                        //resets counter to 0
        }
        else
            line[counter++] = (char)ch;                                         //copies the chars into the array in ascending order
    }
    fclose(wordfile);                                                           //closes text file
    return wordcnt;                                                             //returns word count
}

/*!
@brief  This function accesses a dictionary text file and a word, and looks up the word 
        in the text file. The function returns, FILE_ERR_OPEN, if the file cannot be 
        opened, and WORD_BAD if the word was not found, otherwise, WORD_OK. It also 
        matches characters in a case-insensitive way by calling the function str_to_upper.

@param  dictionary, word is a function parameter of a pointer to a const char
        wordfile is declared as type FILE
        check_this_word, line is declared as an array of type char
        ch, counter is declared as data type int

@return FILE_ERR_OPEN if unable to open file
        WORD_OK if the word can be found in the text file
        WORD_BAD if unable to find the word in the text file
*//*_______________________________________________________________________________________*/
ErrorCode spell_check(const char* dictionary, const char* word) {
    FILE *wordfile = fopen(dictionary, "r");                                    //read only
    if (wordfile == NULL)                                                       //unable to open
        return FILE_ERR_OPEN;
    
    char check_this_word[MAX];
    memset(check_this_word, 0, MAX);                                            //initializes every element with 0 for the MAX number of bytes 
    strcpy(check_this_word, word);                                              //copies the string pointed to by word to check_this_word
    str_to_upper(check_this_word);                                              //can't rewrite due to const
    
    int ch, counter = 0;
    char line[MAX];                                                             //'ambiguous' size enough to contain the length of a word in the line
    memset(line, 0, MAX);                                                       //initializes every element with 0 for the MAX number of bytes 
    while((ch = fgetc(wordfile)) != EOF) {
        //checks every single line of text as a word
        if(ch == '\n') {                                                        //detects newline then checks contents of array
            str_to_upper(line);                                                 //converts content to uppercase
            if(strcmp(line, check_this_word) == 0) {                            //string compare, returns 0 if true
                fclose(wordfile);                                               //closes text file before exiting function
                return WORD_OK;
            }
            counter = 0;                                                        //resets counter to 0
            memset(line, 0, MAX);                                               //More important to reinitialize the array here as word vary is size
        }
        else
            line[counter++] = (char)ch;                                         //copies the chars into the array in ascending order
    }
    
    fclose(wordfile);                                                           //closes text file
    return WORD_BAD;                                                            //unable to find word
}

/*!
@brief  This function accesses a dictionary text file and counts the number of words of 
        each length between 1 and count (inclusive) and stores this result in an array 
        lengths at the position corresponding to the length. This function returns 
        FILE_ERR_OPEN if the file cannot be opened, otherwise, FILE_OK.

@param  dictionary is a function parameter of a pointer to a const char
        lengths is a function parameter to an array of type unsigned long long int
        count is a function parameter of type unsigned long long int
        wordfile is declared as type FILE
        ch, length is declared as data type int

@return FILE_ERR_OPEN if unable to open file
        FILE_OK if the function is executed till the end of code
*//*_______________________________________________________________________________________*/
ErrorCode word_lengths(const char* dictionary, 
                        WordCount lengths[], WordLength count) {
    FILE *wordfile = fopen(dictionary, "r");                                    //read only
    if(wordfile == NULL)                                                        //unable to open
        return FILE_ERR_OPEN;
    
    //loops till end of text file, after each iteration, length increments
    for(int ch = 0, length = ch; 
        (ch = fgetc(wordfile)) != EOF; length++) {
        if(ch == '\n') {                                                        //end of line detected
            if(length <= count)                                                 //check within range of count
                lengths[length]++;                                              //incrments the corresponding length value element
            length = -1;                                                        //not = 0 as length is incremented before iteration 
        }                                                                       //in a for loop
    }
    fclose(wordfile);                                                           //closes text file
    return FILE_OK;
}

/*!
@brief  This function accesses a dictionary text file and returns its description (the 
        length of the shortest and the longest words, and the count of all words) using 
        the DictionaryInfo structure. This function returns FILE_ERR_OPEN if the file 
        cannot be opened, otherwise, FILE_OK.

@param  dictionary is a function parameter of a pointer to a const char
        info is a function parameter to a DictionaryInfo struct
        wordfile is declared as type FILE
        wordcount is delcared as a type WordCount or unsigned long long int
        shortest, longest, length is declared as size_t or unsigned int
        word is declared as an array of data type char


@return FILE_ERR_OPEN if unable to open file
        FILE_OK if the function is executed till the end of code
*//*_______________________________________________________________________________________*/
ErrorCode info(const char* dictionary, DictionaryInfo* info) {
    FILE *wordfile = fopen(dictionary, "r");                                    //read only
    if(wordfile == NULL)                                                        //unable to open    
        return FILE_ERR_OPEN;

    WordCount wordcount = 0;                                                    //unsigned long long int
    size_t shortest = 0, longest = 0, length = 0;                               //unsigned int of at least 4 bytes

    char word[MAX]; 
    memset(word, 0, MAX);                                                       //initializes every element with 0 for the MAX number of bytes 
    while( fgets(word, MAX, wordfile) != NULL) {                                //gets string (including '\n') from wordfile stream, and copies into word for limit of MAX
        //to remove the '\n' copied and initialize the word array 
        //previously assigned char in the elements
        for(int counter = 0; word[counter] != '\0'; counter++)                  
            word[counter] = word[counter] == '\n' ? '\0': word[counter];
        length = strlen(word);                                                  //gets length of string and stops when '\0' is detected

        if(shortest == 0 && longest == 0)                                       //to assign length to initialized shortest n longest
            shortest = longest = length;
        else if (length < shortest)                                             //reassign shortest if length is shorter
            shortest = length;
        else if (length > longest)                                              //reassign longest if length is longer
            longest = length;

        wordcount++;
    } 

    fclose(wordfile);                                                           //closes text file

    info->shortest = (unsigned char) shortest;                                  //casts to unsigned char
    info->longest = (unsigned char) longest;                                    //casts to unsigned char
    info->count = wordcount;

    return FILE_OK;
}


