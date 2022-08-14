/* Modified Parse.c file Parse.cpp
 * Name: Ronney Sanchez
 * Course: COMP3010 Organization of Programming Language
 * Date: 2/24/19
 * Assignment 2
 * Partner: David Bacon (second class section), Patrick Fuller (second class section)
 */

#include <iostream>
#include "scan.h"

using namespace std;
	 
const char* names[] = {"read", "write", "id", "literal", "gets", "add", "sub", "mul", "div", "lparen", "rparen", "eof","equality","doublebracket","less","greater","lesseq","greatereq","if","fi","do","od","check","epsilon"};

static token input_token;

void match(token expected) 
{ 
  	if(expected == t_epsilon)
    	{
      		//cout << "Matched: " << names[t_epsilon] << endl;
      		return;
	}
  	//cout << "Input: " << input_token << endl;
        //cout << "Expected: " << expected << endl;

    	if(input_token == expected) 
	{
        	//cout << "Matched: " << names[input_token] << endl;
        	switch(input_token)
		{
			case t_literal:
           			cout << " (num \"" << token_image << "\"))" << endl;
			break;

			case t_epsilon:
				cout << "(id \"" << token_image << "\")" << endl;
			break;

			case t_do:
				cout << "(" << token_image << endl;
			break;

			case t_od:
				cout << "]\n" << ")" << endl;
			break;

			case t_if:
				cout << "(" << token_image << endl;
			break;

			case t_fi:
				cout << "]\n" << ")" << endl;
			break;

			case t_greater:
				cout << " > (id \"" << token_image << "\")";
			break;

			case t_greatereq:
				cout << " >= (id \"" << token_image << "\")";
			break;

			case t_lesser:
				cout << " < (id \"" << token_image << "\")";
			break;

			case t_lessereq:
				cout << " <= (id \"" << token_image << "\")";
			break;

			case t_equal:
				cout << " (== (id \"" << token_image << "\")";
			break;

			case t_mul:
				cout << " * (id \"" << token_image << "\")";
			break;

			case t_add:
				cout << " + (id \"" << token_image << "\")";
			break;

			case t_div:
				cout << " / (id \"" << token_image << "\")";
			break;

			case t_eof:
				cout << "]\n)" << endl;
			break;

			default:
			break;
		}
		
        	input_token = scan();
    	}
}

void program();
void stmt_list();
void stmt();
void expr();
void term_tail();
void term();
void factor_tail();
void factor();
void add_op();
void mul_op();
void rel_op();
void relation();
void equivalence_tail();

int main()
{
	input_token = scan();
	program();
	return 0;
}

void program()
{
	try
	{
		cout << "(program" << endl;
		switch(input_token)
		{
    			case t_id:
				stmt_list();
      			break;

    			case t_write:
				stmt_list();
      			break;

    			case t_if:
      				stmt_list();
      			break;

    			case t_do:
      				stmt_list();
      			break;

    			case t_check:
      				stmt_list();

    			case t_read:
				cout << "[(" << names[input_token];
      				stmt_list();
				match(t_eof);

			case t_eof:
				match(t_eof);
			break;
      
    			default:
      				throw exception();
      			break;
    		}
	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

      		token first[] = {t_epsilon, t_id, t_read, t_write, t_if, t_do, t_check,t_eof};
       		token follow[] = {t_eof};
		int i = 0;
		token next_token = scan();

		for(i = 0; i < 7; i++)
        	{
			if(next_token == first[i])
            		{
              			cout << "ERROR HANDLING: Skipped " << token_image << " started parse at" << next_token << endl;
              			input_token = next_token;
              			program();
			}
			
			else if(i == 7)
            		{
				if(next_token == follow[0])
	        		{
              				cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              				input_token = next_token;
					return;
                		}

            		}
			else
            		{
				input_token = next_token;
              			next_token = scan();
	      			program();

            		}
            	}

	}
}

void stmt_list()
{
    	switch(input_token) 
	{
    		case t_id:
      			stmt();
      			stmt_list();
      		break;

    		case t_read:
      			stmt();
      			stmt_list();
      		break;

    		case t_write:
			cout << "[(" << names[input_token];
      			stmt();
			cout << "(id \"" << token_image << "\"))" << endl;
      			stmt_list();
      		break;

    		case t_if:
      			stmt();
      			stmt_list();
      		break;

    		case t_do:
      			stmt();
      			stmt_list();
      		break;

    		case t_check:
      			stmt();
      			stmt_list();
      		break;

    		case t_eof:
      		break;

    		default:
      			match(t_epsilon);
      		break;
    	}
}

void stmt() 
{
	try
	{
		switch(input_token)
		{
    			case t_id:
      				match(t_id);
				cout << "(:= " << token_image << "\"";
      				match(t_gets);
      				relation();
      			break;

    			case t_read:
      				match(t_read);
				cout << " \"" << token_image << "\")" << endl;
      				match(t_id);
      			break;

    			case t_write:
      				match(t_write);
      				relation();
      			break;

    			case t_if:
      				match(t_if);
      				relation();
      				stmt_list();
      				match(t_fi);
      			break;

    			case t_do:
				match(t_do);
      				stmt_list();
      				match(t_od);
      			break;

    			case t_check:
				cout << "[(" << token_image;
      				match(t_check);
      				relation();
      			break;

     			default:
       				throw exception();
			break;

    		}
	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

		token first[] = {t_id, t_read, t_write, t_if, t_do, t_check};
       		token follow[] = {t_epsilon,t_id,t_read, t_write, t_if, t_do, t_check};
      		int i = 0;
      		token next_token = scan();

		if(next_token == t_eof)
        	{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);
        	}

		for(i = 0; i < 6; i++)
		{
			if(next_token == first[i])
            		{
              			cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              			input_token = next_token;
              			stmt();
            		}
          		else if(i == 6)
            		{
              			for(i = 0; i < 7; i++)
				{
              				if(next_token == follow[i])
                			{
              					cout<<"ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              					input_token = next_token;
						return;
					}
                		}
			}
          		else
            		{
				input_token = next_token;
              			next_token = scan();
              			stmt();
            		}


        	}
	}
}

void expr()
{
	try
	{
		switch(input_token)
		{
    			case t_lparen:
      				term();
      				term_tail();
      			break;

    			case t_id:
      				term();
      				term_tail();
      			break;

   	 		case t_literal:
      				term();
      				term_tail();
      			break;

    			default:
      				throw exception();
    		}
	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

      		token first[] = {t_lparen,t_id, t_literal};
       		token follow[] = {t_epsilon, t_equal,t_bracket, t_greater, t_lesser, t_greatereq,t_rparen,t_id, t_read, t_write, t_if, t_do, t_check};

      		int i = 0;
		token next_token = scan();
		if(next_token == t_eof)
		{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);

        	}
		for(i = 0; i < 3; i++)
		{
          		if(next_token == first[i])
            		{
	      			cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              			input_token = next_token;
              			expr();
            		}
          		else if(i == 3)
            		{
              			for(i = 0; i < 13; i++)
	        		{
              				if(next_token == follow[i])
                			{
	      					cout<<"ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              					input_token = next_token;
						return;
					}
                		}

            		}
          		else
            		{
              			input_token = next_token;
              			next_token=scan();
	      			expr();
            		}
		}
	}
}

void term_tail() 
{  
	switch(input_token) 
    	{
    		case t_add:
      			add_op();
      			term();
      			term_tail();
      		break;

    		case t_sub:
      			add_op();
      			term();
      			term_tail();
      		break;

    		case t_eof:
      			match(t_eof);

    		default:
      			match(t_epsilon);
      		break;
    	}
}

void term() 
{
	try
	{
    		switch(input_token)
		{
			case t_lparen:
      				factor();
      				factor_tail();
      			break;

    			case t_id:
      				factor();
      				factor_tail();
      			break;

    			case t_literal:
      				factor();
    				factor_tail();
    			break;

    			default:
      				throw exception();
		}
    	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

		token first[] = {t_lparen,t_id,t_literal};
       		token follow[] = {t_epsilon, t_add,t_sub};

      		int i = 0;
      		token next_token = scan();

         	if(next_token == t_eof)
        	{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);
        	}
		for(i = 0; i < 3; i++)
		{
          		if(next_token == first[i])
            		{
              			cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              			input_token = next_token;
              			term();

            		}
          		else if(i == 3)
            		{
	      			if(next_token == follow[i])
				{
              				cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
					input_token = next_token;
                			return;
                		}
            		}
          		else
            		{	
	      			input_token = next_token;
	      			next_token = scan();
	      			term();
            		}
		}
	}
}

void factor_tail() 
{
    	switch(input_token)
	{
    		case t_mul:
      			mul_op();
      			factor();
      			factor_tail();
      		break;

    		case t_div:
      			mul_op();
      			factor();
      			factor_tail();

     		default:
      			match(t_epsilon);
      		break;
    	}
}

void factor() 
{
	try
      	{	      
      		switch(input_token) 
		{
    			case t_lparen:
      				match(t_lparen);
      				relation();
      				match(t_rparen);  
      			break;

    			case t_id:
      				match(t_id);
      			break;

    			case t_literal:
      				match(t_literal);
      			break;
    
			default:
      				throw exception();
		}
    	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

      		token first[] = {t_lparen, t_id,t_literal};
       		token follow[] = {t_epsilon, t_mul, t_div};

      		int i = 0;
		token next_token = scan();

         	if(next_token == t_eof)
        	{
			cout << "Reached end of file in Error Recovery. Program was exited" << endl;
			exit(1);
        	}

      		for(i = 0; i < 3; i++)
		{
          		if(next_token == first[i])
            		{
              			cout<<"ERROR HANDLING: Skipped "<< token_image << " started parse at " << next_token << endl;
              			input_token = next_token;
              			factor();
			}
          		else if(i == 3)
            		{
              			for(i = 0; i < 3; i++)
				{
              				if(next_token == follow[i])
                			{
              					cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              					input_token = next_token;
						return;
					}
				}

            		}
          		else
            		{
              			input_token = next_token;
              			next_token = scan();
              			factor();
            		}
		}
	}
}

void add_op() 
{	
	try
	{	
    		switch(input_token)
		{
    			case t_add:
      				match(t_add);
      			break;

    			case t_sub:
      				match(t_sub);
      			break;

    			default:
      				throw exception();
			break;
		}
    	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

      		token first[] = {t_add, t_sub};
       		token follow[] = {t_lparen, t_id,t_literal};

      		int i = 0;
      		token next_token = scan();
         	if(next_token == t_eof)
        	{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);
        	}
		for(i = 0; i < 2; i++)
		{
          		if(next_token == first[i])
            		{
              			cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              			input_token = next_token;
              			add_op();

            		}
          		else if(i == 2)
            		{
              			for(i = 0; i < 3; i++)
	        		{
              				if(next_token == follow[i])
                			{
              					cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              					input_token = next_token;
                				return;
                			}
                		}
            		}
			else
            		{
              			input_token = next_token;
              			next_token = scan();
              			add_op();
            		}
            	}
	}
}

void mul_op() 
{
      	try
	{	
    		switch(input_token)
		{
    			case t_mul:
      				match(t_mul);
				cout << " (id \"" << token_image << "\")))" << endl;
      			break;

    			case t_div:
      				match(t_div);
				cout << " (id \"" << token_image << "\")))" << endl;
      			break;

    			default:
      				throw exception();
		}
    	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;
      		token first[] = {t_mul,t_div};
       		token follow[] = {t_lparen,t_id,t_literal};

      		int i = 0;
      		token next_token = scan();

		if(next_token == t_eof)
        	{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);
        	}
		for(i = 0; i < 2; i++)
		{
          		if(next_token == first[i])
            		{
              			cout << "ERROR HANDLING: Skipped " << token_image <<" started parse at " << next_token << endl;
              			input_token = next_token;
              			mul_op();
            		}
          		else if(i == 2)
            		{
              			for(i = 0; i < 3; i++)
				{
					if(next_token == follow[i])
                			{
              					cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              					input_token = next_token;
						return;
					}
                		}
            		}
          		else
            		{
				input_token = next_token;
              			next_token = scan();
              			mul_op();
            		}
            	}
	}
}

void rel_op()
{	try
	{
    		switch(input_token) 
		{
    			case t_equal:
      				match(t_equal);
				cout << " (id \"" << token_image << "\")))" << endl;
      			break;

    			case t_bracket:
      				match(t_bracket);
				cout << " (id \"" << token_image << "\")))" << endl;
      			break;

    			case t_greater:
      				match(t_greater);
      			break;

   	 		case t_lesser:
      				match(t_lesser);
      			break;

    			case t_lessereq:
     				match(t_lessereq);
     			break;

    			case t_greatereq:
      				match(t_greatereq);
				cout << " (id \"" << token_image << "\")))" << endl;
      			break;

   			default:
      				throw exception();
		}
    	}
	catch(exception& e)
	{
		 cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

      		token first[] = {t_equal, t_bracket,t_lesser, t_greater, t_greatereq,t_lessereq};
      		token follow[] = {t_lparen,t_id,t_literal};

      		int i = 0;
      		token next_token = scan();

         	if(next_token == t_eof)
		{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);
        	}

      		for(i = 0; i < 6; i++)
		{
          		if(next_token == first[i])
			{
				cout << "ERROR HANDLING: Skipped " << token_image<<" started parse at " << next_token << endl;
              			input_token = next_token;
              			rel_op();

            		}
          		else if(i == 6)
          		{
		  		if(next_token == follow[i])
				{
	      				cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              				input_token = next_token;
                			return;
                		}
            		}
          		else
            		{
	      			input_token = next_token;
	      			next_token = scan();
	      			rel_op();
			}
		}
	}
    
}

void relation()
{
	try
	{
       		switch (input_token) 
       		{
			case t_lparen:
	  			expr();
	  			equivalence_tail();
	  		break;

			case t_id:
	  			expr();
	  			equivalence_tail();
	  		break;

			case t_literal:
	  			expr();
	  			equivalence_tail();
	  		break;
        
    			default:
      				throw exception();
			break;
		}
	}
	catch(exception& e)
	{
		cerr << "SYNTAX ERROR: " << token_image << " not found. INITIATING ERROR RECOVERY" << endl;

      		token first[] = {t_lparen,t_id,t_literal};
       		token follow[] = {t_rparen, t_epsilon, t_id,t_read,t_write,t_if,t_do,t_check};

      		int i = 0;
      		token next_token = scan();

         	if(next_token == t_eof)
		{
          		cout << "Reached end of file in Error Recovery. Program was exited" << endl;
          		exit(1);
        	}

      		for(i = 0; i < 3; i++)
		{
			if(next_token == first[i])
            		{
	      			cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              			input_token = next_token;
              			relation();
            		}
          		else if(i == 3)
            		{
              			for(i = 0; i < 8; i++)
	        		{
              				if(next_token == follow[i])
                			{
	      					cout << "ERROR HANDLING: Skipped " << token_image << " started parse at " << next_token << endl;
              					input_token = next_token;
                				return;
                			}
                		}

            		}
          		else
            		{
				input_token = next_token;
              			next_token = scan();
	      			relation();
            		}
		}
	}
}

void equivalence_tail()
{     
	switch(input_token) 
	{
		case t_equal:
			rel_op();
			expr();
		break;

      		case t_bracket:
			rel_op();
			expr();
		break;

      		case t_greater:
			rel_op();
			expr();
		break;

      		case t_lesser:
			rel_op();
			expr();
		break;

      		case t_lessereq:
			cout << " <= (id \"" << token_image << "\")" << endl;
			rel_op();
			cout << " (id \"" << token_image << "\")" << endl;
			expr();
		break;

      		case t_greatereq:
			rel_op();
			expr();
		break;

      		default:
			match(t_epsilon);
		break;
   	}
}
