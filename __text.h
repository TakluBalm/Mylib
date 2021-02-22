#ifndef __MY_TEXT

#include "__string.h"

#define __MY_TEXT

//      Custom structs

typedef struct line line;
typedef struct text text;

struct line{        
    string value;
    line* next;
    line* prev;
};
struct text{
    line* start;
    line* end;
    unsigned int lines;
    unsigned int current;
};

text initxt();                              // Initialises the start, end and lines fields in text datatype 
text getxt(int show);                       // Initialises and takes texxt input from the user  
text editxt(text txt, int j, int show);     // Edits the contents of an initialised text
void freetxt(text txt);                     // Frees all the allocated memory by the initxt(), getxt() and editxt() functions
void printxt(text txt);                     // Prints the contents of 'txt' on the screen

#endif
