#ifndef __MY_TEXT

#include "__string.h"

#define __MY_TEXT

//      Custom structs

typedef struct line{        
    string value;
    struct line* next;
    struct line* prev;
}line;
typedef struct text{
    line* start;
    line* end;
    unsigned int lines;
    unsigned int current;
}text;

text initxt();                              // Initialises the start, end and lines fields in text datatype 
text getxt(int show);                       // Initialises and takes texxt input from the user  
text editxt(text txt, int j, int show);     // Edits the contents of an initialised text
void freetxt(text txt);                     // Frees all the allocated memory by the initxt(), getxt() and editxt() functions
void printxt(text txt);                     // Prints the contents of 'txt' on the screen

char* txt_to_char(text txt);
text char_to_txt(string str);

#endif
