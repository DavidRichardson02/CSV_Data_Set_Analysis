//  StringUtilities.h
//  CSV_File_Data_Set_Analysis_05
/**
 * StringUtilities code: provides a comprehensive suite of utilities for string manipulation and analysis, primarily designed for data
 * parsing and preprocessing in the context of data integration and analysis. This collection of functions is particularly useful
 * in any contexts where string data must be examined, transformed, or formatted before being used in computations or visualizations.
 *
 * NOTE: Focuses on C-style strings, namely: char, char*, char*[], and char**
 **/


#ifndef StringUtilities_h
#define StringUtilities_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>




// ------------------ Global Constants -------------------
// \{
static const size_t MAX_STRING_SIZE = 1000; // Maximum string size.
// \}






// ------------- Helper Functions for Determining Properties of Strings in c, namely: char c, char* characterString, char** stringArray -------------
/// \{
bool char_is_whitespace(char c); // Checks if a character is whitespace.
bool char_is_punctuation(char c); // Checks if a character is punctuation.
bool char_is_underscore(char c); // Checks if a character is an underscore.
bool char_is_sign(char c); // Checks if a character is a sign (+, -, etc.).
bool char_is_delimiter(char c); // Checks if a character is a delimiter (non-alphanumeric and non-space)


bool string_is_numeric(const char *characterString); // Checks if a string represents a numeric value.
bool string_is_hyphen_else_is_minus_sign(char *characterString); // Differentiates between hyphens and minus signs.
int *string_is_date_time(const char *characterString, const char *delimiter, const int fieldCount); // Analyzes a string for date/time formats.
bool string_array_contains_date_time(char **stringArray, int stringCount, const char *delimiter);
/// \}






// ------------- Helper Functions for Counting Elements and Identifying Characteristics of Strings -------------
/// \{
int count_character_occurrences(const char *characterString, char c); // Counts occurrences of a character in a string
char find_most_common_non_alphanumeric_character(const char *characterString); // Finds the most common non-alphanumeric character in a string
char *find_potential_delimiters(const char *characterString, int *delimiterCount); // Finds potential delimiters in a string
char *identify_delimiter(char** stringArray, int stringCount); // Identify the most common delimiter in a string
char *identify_delimiter_recursive(char** stringArray, int stringCount, char **primaryDelimiters, int *primaryDelimiterCount); // Pass in primary delimiters(and count) by reference


const char *determine_string_representation_type(const char* token); // Determines if a string is numeric or non-numeric.
char *determine_most_common_string(char **stringArray, int stringCount); // Determines the most common string in an array of strings.

int count_string_characters(const char* characterString); // Counts characters in a string.
int count_array_strings(char **stringArray); // Counts strings in an array.
/// \}






// ------------- Helper Functions for Printing Various Representations of String and Arrays for Debugging -------------
/// \{
void print_string(char* string); // Prints a single string.
void print_string_array(char** stringArray, int stringCount, char* label); // Prints an array of strings.
void print_string_array_array(char*** stringArrayArray, int stringArraysCount, int stringSubArraysCount, char* label); // NOTE: assumes the dimension of all sub-arrays is the same
void print_array(int n, double *data, char* label); // Prints an array of doubles.
void print_array_array(double **data, int rows, int columns, char* label); // Prints a 2D array of doubles.
void print_char_ptr_array(char *charPtrArr[], int stringCount, char* label); // Prints an array of char pointers.
/// \}






// ------------- Helper Functions for Combining and/or Concatenating Representations of strings in plain c -------------
/// \{
char **split_string_tokens(const char* characterString, const char* delimiter, int divisions); // Splits a string into an array of strings based on a given delimiter,i.e., assigns each tokenized field to an element in an array.
char *combine_char_ptr(const char *characterString1, const char *characterString2);  // Combines two strings.
char **combine_char_ptr_ptr(const char **stringArray1, int stringCountArray1, const char **stringArray2, int stringCountArray2); // Combines two arrays of strings.
char *combine_char_ptr_arr(const char *characterString1, const char *characterStringArray[], int numArrayStrings); // Combines a string with each string in an array.
char *concatenate_string_array(const char** stringArray, int stringCount, const char *delimiter); // Concatenates an array of strings into a single string with fields seperated by the delimiter
/// \}






// ------------- Helper Functions for Trimming and Pruning Strings -------------
/// \{
char *replace_date_time_with_unix(char* characterString, const char *delimiter, const int fieldCount); // Replaces date/time with Unix time.

char *trim_string_whitespaces(char* untrimmedString); // Trims whitespace from a string.
char *prune_string_whitespaces(char *unprunedString); // Removes all whitespaces from a string.
char *prune_repeated_delimiters_from_string(char *unprunedString, const char *delimiter);  // Handles repeated delimiters.
char *prune_and_trim_problematic_characters_from_string(char *originalString, const char *delimiter, const int fieldCount);  // Prunes and trims problematic characters.
/// \}






#endif /* StringUtilities_h */
