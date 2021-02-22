#include "__text.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//  --------------------------------------  editxt()  ------------------------------------------------

text editxt(text txt, int j, int show){
    line *current = txt.start, *mediator = NULL;
    for (int k = 0; k < j; k++) current = current->next;
    int i = txt.lines;
    while(1){
        switch ((current->value).start->value){
        case ('U'): {   //      Move Up  
            (current->value).start->value = '\0';
            if (current->prev == txt.start) {current->value = editstr(current->value, (current->value).cursor, 1); break;}
            printf("\033[A");
            for (int k = 0; k < (current->value).cursor; k++) printf("\b");
            current = current->prev; j--;
            current->value = editstr(current->value, (current->next->value).cursor, 1);
            break;
        }
        case ('D'): {   //      Move Down
            (current->value).start->value = '\0';
            if (current->next == txt.end) {current->value = editstr(current->value, (current->value).cursor, 1); break;}
            printf("\033[B");
            for (int k = 0; k < (current->value).cursor; k++) printf("\b");
            current = current->next; j++;
            current->value = editstr(current->value, (current->prev->value).cursor, 1);
            break;
        }
        case ('N'): {   //      Insert a Newline
            (current->value).start->value = '\0';
            if ((current->value).cursor == (current->value).length){
                if (current->next == txt.end) break;
                printf("\033[J\n");
                text txt2; txt2.start = (line*) malloc(sizeof(line));
                txt2.start->next = current->next; txt2.start->prev = NULL; txt2.end = txt.end;
                printxt(txt2);
                for (int k = 0; k < (i-j+1); k++) printf("\033[A");
                free(txt2.start); break;
            }
            else{
                printf("\033[A\033[J");
                mediator = (line*) malloc(sizeof(line));
                mediator->next = current->next; mediator->prev = current;
                current = current->next = current->next->prev = mediator;
                current->value = breakstr(&(current->prev->value), (current->prev->value).cursor);
                strprint(current->prev->value); strprint(current->value);
                if (current->next != txt.end){
                    text txt2; txt2.start = (line*) malloc(sizeof(line)); txt2.start->next = current->next; txt2.end = txt.end;
                    printxt(txt2); free(txt2.start);
                    for (int k = 0; k < (i-j+1); k++) printf("\033[A");
                    current->value = editstr(current->value, 0, 1);
                }
                else {printf("\033[A"); current->value = editstr(current->value, 0, 1);}
                break;
            }
        }
        case ('R'): {   //      Remove the line
            (current->value).start->value = '\0';
            if (current->prev == txt.start) {current->value = editstr(current->value, (current->value).cursor, 1); break;}
            printf("\033[J");
            current = current->prev;
            line *temp = current->next->next;
            int len = (current->next->value).length;
            current->value = concatnate(current->value, current->next->value);
            if (temp != txt.end){
                text txt2; txt2.end = txt.end; 
                txt2.start = (line*)malloc(sizeof(line)); txt2.start->next = temp; 
                printxt(txt2);
                for (int k = 0; k < (i-j+1); k++) printf("\033[A");
                free(txt2.start);
            }
            else {if (show != 2) printf("\033[A\033[J");}
            free(current->next); i--; j--;
            current->next = temp; temp->prev = current;
            current->value = editstr(current->value, (current->value).length - len, 1);
            break;
        }
        case ('\0'): {
            mediator = (line*) malloc(sizeof(line));
            mediator->next = current->next; mediator->prev = current;
            current = current->next = current->next->prev = mediator;
            current->value = getstr("", show);
            i++;j++; break;
        }
        case ('L'): {
            (current->value).start->value = '\0';
            if (show != 2) {
                for (int k = 0; k < (i-j+1); k++) printf("\033[B"); 
                printf("\r");
            }
            goto cleanup;
        }
        }
    }
    cleanup:
    txt.lines = i; return txt;
}

//  ------------------------------------  getxt()  ---------------------------------------------------

text getxt(int show){
    text txt = initxt();
    line *current = txt.start, *mediator = NULL;
    editxt(txt, txt.lines, show);
    return txt;
}

//  -------------------------------------  printxt()  ------------------------------------------------

void printxt(text txt){
    line* current = txt.start->next;
    while (current != txt.end){
        strprint(current->value);
        current = current->next;
    }
}

//  -------------------------------------  freetxt()  ------------------------------------------------

void freetxt(text txt){
    line* current = txt.end->prev;
    while(current != txt.start){
        freestr(current->value);
        current = current->prev;
        free(current->next);
    }
    freestr(txt.start->value);free(txt.end); free(txt.start);
}

//  --------------------------------------  initxt()  ------------------------------------------------

text initxt(){
    text txt;
    do
    txt.start = (line*) malloc(sizeof(line));
    while (txt.start == NULL);
    do 
    txt.end = (line*) malloc(sizeof(line));
    while (txt.end == NULL);   
    txt.start->next = txt.end; txt.end->prev = txt.start;
    txt.start->prev = txt.end->next = NULL;  txt.lines = 0;
    txt.start->value = initstr();
    return txt;
}
