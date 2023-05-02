/*!
@file       qdriver.c
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 8
@date       09/11/2020
@brief      This file contains the test driver code.
            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#include <stdio.h>		// printf()
#include <string.h>     // strcpy

#include "spellcheck.h"

void test1(void)
{
	printf("Test1--------------------------------------------------------\n");
	const char* const words[] = {
		"Four", "score", "and", "seven", "years", "ago", "our",
		"fathers", "brought", "forth", "on", "this",
		"continent", "a", "new", "NATION", "fast123",
		"123  abc", "Hello!!", "", "*&^%$#8UPPERlower"
	};
	const size_t num_words = sizeof(words) / sizeof(*words);
	char buffer[LONGEST_WORD + 1];
	for (size_t i = 0; i < num_words; ++i)
	{
		strcpy(buffer, words[i]);
		str_to_upper(buffer);
		printf("Word: %s (%s)\n", words[i], buffer);
	}
}

void test2(const char* dictionary)
{
	DictionaryInfo dictionary_info;

	printf("\nTest2--------------------------------------------------------\n");
	ErrorCode error = info(dictionary, &dictionary_info);
	if (error == FILE_ERR_OPEN)
	{
		printf("Cannot open \"%s\".\n", dictionary);
		return;
	}

	printf(
		"Dictionary:     \t%s\n"
		"Number of words:\t%llu\n"
		"Shortest word:  \t%u letters\n"
		"Longest word:   \t%u letters\n",
		dictionary,
		dictionary_info.count,
		dictionary_info.shortest,
		dictionary_info.longest
	);
}

void test3(const char* dictionary, char letter)
{
	printf("\nTest3--------------------------------------------------------\n");
	WordCount error = words_starting_with(dictionary, letter);
	if (error == FILE_ERR_OPEN)
	{
		printf("Cannot open \"%s\".\n", dictionary);
		return;
	}

	printf(
		"Dictionary:\t%s\n"
		"Number of words starting with %c:\t%llu\n",
		dictionary,
		letter,
		error
	);
}

void test4(const char* dictionary, const char* word)
{
	printf("\nTest4--------------------------------------------------------\n");
	ErrorCode error = spell_check(dictionary, word);
	if (error == FILE_ERR_OPEN)
	{
		printf("Cannot open \"%s\".\n", dictionary);
		return;
	}

	if (error == WORD_OK)
	{
		printf("The word \"%s\" is spelled correctly.\n", word);
	}
	else
	{
		printf("The word \"%s\" is misspelled.\n", word);
	}
}

void test5(void)
{
	printf("\nTest5--------------------------------------------------------\n");
	const char* const words[] = {
		"Four", "score", "and", "seven", "years", "ago", "our",
		"fathers", "brought", "forth", "on", "this", "continent",
		"a", "new", "nation"
	};
	const size_t num_words = sizeof(words) / sizeof(*words);
	const char* const dictionary = "allwords.txt";
	WordCount num_misspelled = 0;

	printf("Misspelled words: ");
	for (size_t i = 0; i < num_words; i++)
	{
		ErrorCode error = spell_check(dictionary, words[i]);
		if (error == FILE_ERR_OPEN)
		{
			printf("Cannot open \"%s\".\n", dictionary);
			return;
		}
		if (error == WORD_BAD)
		{
			if (num_misspelled > 0)
			{
				printf(", ");
			}
			printf("%s", words[i]);
			++num_misspelled;
		}
	}
	if (!num_misspelled)
	{
		printf("*** None ***");
	}
	printf("\n");
}

void test6(void)
{
	printf("\nTest6--------------------------------------------------------\n");
	const char* const words[] = {
		"Four", "SCORE", "and", "sevn", "years", "ago", "ar",
		"fawthers", "brought", "foarth", "on", "this", "contnent",
		"a", "gnu", "nashun"
	};
	const size_t num_words = sizeof(words) / sizeof(*words);
	const char* const dictionary = "allwords.txt";
	WordCount num_misspelled = 0;

	printf("Misspelled words: ");
	for (size_t i = 0; i < num_words; i++)
	{
		ErrorCode error = spell_check(dictionary, words[i]);
		if (error == FILE_ERR_OPEN)
		{
			printf("Cannot open \"%s\".\n", dictionary);
			return;
		}
		if (error == WORD_BAD)
		{
			if (num_misspelled > 0)
			{
				printf(", ");
			}
			printf("%s", words[i]);
			++num_misspelled;
		}
	}
	if (!num_misspelled)
	{
		printf("*** None ***");
	}
	printf("\n");
}

void test7(WordLength max_length)
{
	printf("\nTest7--------------------------------------------------------\n");
	WordCount total = 0;
	WordCount lengths[max_length + 1];
	for (WordLength i = 0; i <= max_length; ++i)
	{
		lengths[i] = 0;
	}
	const char* const dictionary = "allwords.txt";
	printf("Dictionary: %s\n", dictionary);
	ErrorCode error = word_lengths(dictionary, lengths, max_length);
	if (error == FILE_ERR_OPEN)
	{
		printf("Can't open %s\n", dictionary);
		return;
	}
	for (WordLength length = 1; length <= max_length; length++)
	{
		printf(
			"Number of words of length %2u: \t%6llu.\n",
			length,
			lengths[length]
		);
		total += lengths[length];
	}
	printf("Total number of words counted:\t%6llu.\n", total);
}

int main(void)
{
	test1();

	test2("lexicon.txt");
	test2("small.txt");
	test2("allwords.txt");
	
	test3("lexicon.txt", 'a');
	test3("lexicon.txt", 'A');
	test3("lexicon.txt", 'l');
	test3("lexicon.txt", '$');
	test3("lexicon.txt", 'e');

	test3("allwords.txt", 'M');
	test3("allwords.txt", 'q');
	test3("allwords.txt", '5');

	test4("lexicon.txt", "APPLE");
	test4("lexicon.txt", "Apple");
	test4("lexicon.txt", "apple");
	test4("lexicon.txt", "appl");
	test4("small.txt", "abalone");
	test4("allwords.txt", "interdigitation");
	test4("allwords.txt", "interdigalizing");

	test5();
	
	test6();

	test7(5);

	return 0;
}
