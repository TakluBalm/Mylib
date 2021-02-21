#ifndef __MY_STRING

#define __MY_STRING

//      Custom structs

typedef struct node{
    struct node *next;
    struct node *prev;
    int value;
}node;
typedef struct string{
    node *start;
    node *end;
    unsigned int length;
    unsigned int cursor;
}string;

string initstr();                           	    	// Initialises the start, end, length and cursor fields of string datatype and returns the initialised string
string getstr(char *msg, int show);         		    // Initialises the string and stores the input from the user
string concatnate(string str1, string str2);    		// Takes two strings and merges them to a single one. The initial two strings lose their meanings
string editstr(string str, int j, int show);	    	// Edits the contents of an initialised string 
string breakstr(string* str, int j);        		    // Takes the string and breaks it into two. Returns the right broken string while the left one stays in the original 
void freestr(string str);                       		// Frees all the heap memory allocated by the above functions 
void strprint(string str);                      		// Prints the content of a string to the screen
int stringcmp(string s1, string s2);          	        // Checks the strings for equality
void insert(string str, int show, int i, int j);    	// To support visual insertion of characters in the string

char* to_char(string str);                              // Covert string to  char* data type for storage
string to_string(char *str);                            // Convert char* to string data type for manual input                 

#endif
