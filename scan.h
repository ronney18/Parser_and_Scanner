/* Definitions the scanner shares with the parser
 * Michael L. Scott, 2008-2017.
 * Name: Ronney Sanchez
 * Course: COMP3010 Organization of Programming Language
 * Date: 2/24/19
 * Assignment 2
 * Partner: David Bacon (second class section), Patrick Fuller (second class section)
 */

#ifndef scan_INCLUDE
#define scan_INCLUDE

#include<string.h>

typedef enum {t_read, t_write, t_id, t_literal, t_gets,
	      t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof,t_equal,t_bracket,t_lesser,t_greater,t_lessereq,t_greatereq,t_if,t_fi,t_do,t_od,t_check,t_epsilon, t_error} token;

extern char token_image[100];

extern token scan();

#endif
