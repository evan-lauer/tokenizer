#include "value.h"
#include "linkedlist.c"
#include "talloc.c"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Read all of the input from stdin, and return a linked list consisting of the
// tokens.
Value *tokenize() {
    char charRead;
    Value *list = makeNull();
    charRead = (char)fgetc(stdin);

    while (charRead != EOF) {
        if (charRead == .....) {
            //create new constype node
            newNode = cons(charRead, Value *newCdr) //confused what the newcdr is meant to be
            newNode->type = int;
        } else if (charRead == ......) { //do we need an else if for every type?
            ...
        } else {
            makeNull();
        }
        charRead = (char)fgetc(stdin);
    }
    Value *revList = reverse(list);
    return revList;
}

// Displays the contents of the linked list as tokens, with type information
void displayTokens(Value *list){
    //token = car(list);
    printf("%c : %s \n", car(list), car(list)->type);
    if (cdr(list)->type != NULL_TYPE){
        displayTokens(cdr(list));
    }}