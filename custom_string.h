/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Diviš Jan	    xdivis12
 *          Kopáček Jiří	xkopac06
 *          Pojsl Jakub	    xpojsl00
 *          Sasín Jonáš	    xsasin05
 *
 *      File: custom_string.h
 */


//library for work with a string structure


#include <stdlib.h>
#include <string.h>

#define STRINGLEN 8 //shortest lenght of string (size of char)

typedef struct
{
	char *str; //pointer on the beginning of string 
	int length; /// number of chars in string including '\0'
	int size; /// number of alocated chars 
} string;

/**
 * @brief initialization of string, alocation
 * @param s pointer to string
 * @return 0 if init was successfull, 1 otherwise 
*/
int string_init(string *s);

/**
 * @brief clears the string
 * @param s pointer to string 
 */
void string_clear(string *s);

/**
 * @brief dealocates the string
 * @param s pointer to string
 * 
 */
void string_free(string *s);

/**
 * @brief concatenate two strings 
 * @param s1 source string to be appended after second string
 * @param s2 destination string 
 * @return 0 if successful, 1 otherwise
 */
int string_concat(string *s, string* s2);

/**
 * @brief appends char by the end of the string
 * @param s pointer to string
 * @param c char to be appended
 */
int string_append_char(string *s, char c);