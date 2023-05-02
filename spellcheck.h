/*!
@file       spellcheck.h
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 8
@date       09/11/2020
@brief      This file contains macros and function declarations.
            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#ifndef SPELLCHECK_H
#define SPELLCHECK_H

/*******************************************************************************
 * TYPE DEFINITIONS                                                            *
 ******************************************************************************/

typedef unsigned long long int WordCount;
typedef unsigned char WordLength;
typedef WordCount ErrorCode;

typedef struct DictionaryInfo
{
	// Length of the shortest word
	WordLength shortest;
	// Length of the longest word
	WordLength longest;
	// Number of words in the dictionary
	WordCount count;
} DictionaryInfo;

/*******************************************************************************
 * MACROS                                                                      *
 ******************************************************************************/

/* In macros below take note that values -1 and -2 represented on an unsigned
   data type result in very large values from the maximum end of the range. */

// The file was opened successfully.
#define FILE_OK			((ErrorCode)(-2))
// The file was not opened.
#define FILE_ERR_OPEN 	((ErrorCode)(-1))
// The word was not found in the dictionary.
#define WORD_BAD		((ErrorCode)(0))
// The word was found in the dictionary.
#define WORD_OK			((ErrorCode)(1))

// This is the longest word you need to handle
#define LONGEST_WORD	((WordLength)(50))

/*******************************************************************************
 * FUNCTION DECLARATIONS                                                       *
 ******************************************************************************/

char* str_to_upper(char* string);
WordCount words_starting_with(const char* dictionary, char letter);
ErrorCode spell_check(const char* dictionary, const char* word);
ErrorCode word_lengths(const char* dictionary, WordCount lengths[], WordLength count);
ErrorCode info(const char* dictionary, DictionaryInfo* info);

#endif // SPELLCHECK_H
