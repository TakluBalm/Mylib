#include <__text.h>
#include <__string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	string s;
	s = to_string("This was initially char * but now it is string");
	char* del = to_char(s);
	freestr(s);
	printf("%s\n", del);
	free(del);
	del = to_char(getstr("Type a string here: ", 1));
	printf("%s\n", del);
	free(del);
}
