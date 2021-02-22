#include "__string.h"
#include "__io.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//           --------------------------editstr()-----------------------

string editstr(string str, int j, int show){
    int i = str.length;
    if (j > i) j = i;
    node *mediator = NULL, *current = str.start; 
    for (int k = 0; k < j; k++) current = current->next;
    insert(str, show, i, j);
    while(1){
        int temp = getch();
        switch(temp){

            // Processing the read character
            
            case ('\n'):{if (show != 2) printf("\n"); str.start->value = 'N'; goto end;}
            case (EOF):{str.start->value = 'L'; goto end;}
            case (127):{                             		// ASCII for Backspace
                if (current == str.start) {str.start->value = 'R'; goto end;}
                current->next->prev = current->prev;
                current->prev->next = current->next;
                mediator = current; current = current->prev; 
                free(mediator);
                i--;j--;
                insert(str, show, i, j);
                break;
            }
            case (27):{		                               // 27 is ASCII for ESC character
                temp = getch();
                if (temp == 91){       	                       // 91 is ASCII for [ character
                    switch(temp = getch()){
                        case (67):{
                            if (current->next == str.end) continue;
                            else current = current->next;
                            j++;
                            insert(str, 1, i , j);
                            continue;
                        }
                        case (68):{
                            if (current == str.start) continue;
                            else current = current->prev;
                            j--;
                            insert(str, 1, i , j);
                            continue;
                        }
                        case (65):
                        case (66):{
                            str.start->value = (temp == 65)?'U':'D';
                            goto end;
                        }
                        case(51):{
                            temp = getch();
                            if (temp == 126){
                                current = current->next; printf("\033[C\b \b");
                                current->next->prev = current->prev;
                                current->prev->next = current->next;
                                mediator = current; current = current->prev; 
                                free(mediator);i--;
                                insert(str, show, i, j);
                                break;
                            }
                        }
                    }
                    break;
                }
                if (temp == 27){
                    str.start->value = 'L';
                    goto end;
                }
            }

            // Adding and printing the processed character
            
            default:{
                mediator = malloc(sizeof(node));
                mediator->next = current->next; mediator->prev = current;
                current = current->next = (current->next)->prev = mediator;
                current->value = temp;
                i++; j++;
                insert(str, show, i, j);
            }
        }
        continue;
    }
    end:
    str.length = i; str.cursor = j;
    return str;    
}

//           --------------------------getstr()--------------------------

string getstr(char *msg, int show){        // SHOW: 0->Password 1->Normal text  2->No output on screen
    printf("%s", msg);
    int last_new_line=-1, msg_len;
    for(msg_len = 0; msg[msg_len] != '\0'; msg_len++) {if (msg[msg_len] == '\n') last_new_line=msg_len;}
    char* new_msg = msg + last_new_line + 1;
    string str = to_string(new_msg);
    node *current = str.start, *mediator = NULL;
    str = editstr(str, str.length, show);
    string str_final = breakstr(&str, msg_len);
    freestr(str);
    return str_final;
}

//     -----------------------------insert()-----------------------------

void insert(string str, int show, int i, int j){
    if (show == 1){
        printf("\r\033[K");
        str.end->value = '\0';
        strprint(str); printf("\r");
        string residue = breakstr(&str, j);
        str.end->value = '\0';
        strprint(str);
        str = concatnate(str, residue);
        str.end->value = '\n';
    }
    else if (show == 0){
        for (int k = 0; k < (i-j); k++) printf("\033[C");
        printf("*");
        for (int k = 0; k < (i-j); k++) printf("\b");
    }
}

//        ----------------------------freestr()-----------------------------

void freestr(string str){
    node *current = str.start, *next = str.start->next;
    while(1){
        free(current);
        if (next->next == NULL){
            free(next);
            break;
        }
        current = next;
        next = next->next;
    }
}

//           --------------------------strprint()-----------------------

void strprint(string str){
    node *current = str.start->next;  
    while(current != str.end){
        printf("%c", current->value);
        current = current->next;
    }
    if (current->value == '\n') printf("%c", current->value);
}

//      ------------------------------------------initstr()--------------------------------------

string initstr(){
    string str;
    do
    str.start = malloc(sizeof(node));
    while (str.start == NULL);
    do 
    str.end = malloc(sizeof(node));
    while (str.end == NULL);   
    str.start->next = str.end; str.end->prev = str.start;
    str.start->prev = str.end->next = NULL; 
    str.start->value = '\0'; str.end->value = '\n';
    str.length = 0; str.cursor = 0;
    return str;
}

//      -----------------------------------------concatnate()------------------------------------

string concatnate(string str1, string str2){
    string str;
    str.start = str1.start; str.end = str2.end;
    str.length = str1.length + str2.length;
    str1.end->prev->next = str2.start->next;
    str2.start->next->prev = str1.end->prev;
    free(str1.end); free(str2.start);
    return str; 
}

//      ------------------------------------------breakstr()--------------------------------------

string breakstr(string *str, int j){
    string str2; str2.end = str->end; str2.length = str->length - j;
    node *current = str->start, *start = malloc(sizeof(node)), *end = malloc(sizeof(node));
    int residue_j, main_j;
    if (str->cursor <= j) {
        residue_j = 0;
        main_j = str->cursor; 
    } else {
        residue_j = str->cursor - j;
        main_j = j;
    }
    for (int k = 0; k < j; k++) current = current->next;
    end->prev = current; end->next = NULL; start->next = current->next; start->prev = NULL;
    end->value = '\n'; start->value = '\0';
    end->prev->next = end; start->next->prev = start;
    str->end = end; str->cursor = str->length = j;
    str2.start = start;
    str->cursor = main_j; str2.cursor = residue_j; 
    return str2;
}

//      -----------------------------------------to_char()-----------------------------------------

char* to_char(string str){
    char* sr = malloc(str.length + 1);
    int len = str.length; node* current = str.start->next;
    for (int i = 0; i < len ; i ++){
        sr[i] = current->value;
        current = current->next;
    }
    sr[len] = '\0';
    return sr;
}

string to_string(char *str){
    char temp = str[0]; int i = 0;
    string s = initstr(); node *current = s.start, *mediator = NULL;
    while(str[i] != '\0' && str[i] != '\n'){
        do {mediator = malloc(sizeof(node));}
        while(mediator == NULL);
        mediator->value = str[i]; mediator->prev = current; mediator->next = current->next;
        current = current->next = current->next->prev = mediator;
        s.cursor++; s.length++;
        i++;
    }
    return s;
}
