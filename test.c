#include <__text.h>
#include <__string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	string str1 = getstr("Enter a string: ", 1);
	string str2 = breakstr(&str1, str1.cursor);
	strprint(str1);printf("str1.cursor = %d\nstr1.length = %d\n", str1.cursor, str1.length);
	strprint(str2);printf("str2.cursor = %d\nstr2.length = %d\n", str2.cursor, str2.length);
	string str = concatnate(str1, str2);
	strprint(str);
	freestr(str);
}
