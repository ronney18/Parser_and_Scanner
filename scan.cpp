/* Name: Ronney Sanchez
 * Course: COMP3010 Organization of Programming Language
 * Date: 2/24/19
 * Assignment 2
 * Partner: David Bacon (second class section), Patrick Fuller (second class section)
 */
#include <iostream>
#include <string>
#include <ctype.h>
#include "scan.h"

using namespace std;

char token_image[100];

token scan() 
{
   	static int c = ' ';

    	 /* next available char; extra (int) width accommodates EOF */
    	int i = 0;              /* index into token_image */

  	  /* skip white space */
    	while (isspace(c)) {
        	c = getchar();
    	}
    	if (c == EOF)
        		return t_eof;
    		if (isalpha(c)) {
        		do {
            			token_image[i++] = c;
           	 		c = getchar();
        		} while (isalpha(c) || isdigit(c) || c == '_');
        		token_image[i] = '\0';
        		if (!strcmp(token_image, "read")) return t_read;
        		else if (!strcmp(token_image, "write")) return t_write;
        		else if(!strcmp(token_image,"do")) return t_do;
        		else if(!strcmp(token_image,"if")) return t_if;
        		else if(!strcmp(token_image,"check")) return t_check;
        		else if(!strcmp(token_image,"od")) return t_od;
        		else if(!strcmp(token_image,"fi")) return t_fi;

	 		else return t_id;
    		}
    		else if (isdigit(c)) {
        		do {
           	 	token_image[i++] = c;
            		c = getchar();
        		} while (isdigit(c));
        		token_image[i] = '\0';
        		return t_literal;
   	 	} else  switch (c) {
        		case ':':
            		if ((c = getchar()) != '=') {
              			cout<< "error\n"<<endl;
                		exit(1);
            		} else {
                		c = getchar();
                		return t_gets;
            		}
            	break;

        	case '+': c = getchar(); return t_add;
        	case '-': c = getchar(); return t_sub;
        	case '*': c = getchar(); return t_mul;
        	case '/': c = getchar(); return t_div;
        	case '(': c = getchar(); return t_lparen;
        	case ')': c = getchar(); return t_rparen;

		case '=':
            	if (std::cin.peek() == '=') {
              		std::cin.ignore(256,' ');
              		c = getchar();
             		 return t_equal;

            	} else {
              		cout << "Error t_equals!";
              	exit(1);
            	}
            	break;

       		case '>':
            		if (std::cin.peek()== '=') {
                		std::cin.ignore(256,' ');
                		c = getchar();
                		return t_greatereq;

            		} else {
              		c = getchar();
              		return t_greater;

            		}
            		break;

	    	case '<':
            	if (std::cin.peek()== '=') {
              		std::cin.ignore(256,' ');
              		c = getchar();
             		 return t_lessereq;
            	} else if (std::cin.peek()== '>')  {
                	std::cin.ignore(256,' ');
                	c = getchar();
                	return t_bracket;
            	}
              	else
                {
                 	 c = getchar();
                  	return t_lesser;
                }
             break;

      		default:
	     		cout << "ERROR IN SCANNER!" << endl;
        	break;

	}
	return t_error;
}
