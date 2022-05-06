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
        //create new constype node
        Value* newNode = cons(charRead, list); //confused what the newcdr is meant to be
        switch (charRead) {
            case ' ' :
                // case for when the char is a space
                break;
            case '(' :
                // case for open paren
                break;
            case ')' :
                // case for closed paren
                break;
            case '"' :
                // case for open quote (maybe call a helper function?
                // and the helper function will read until the end of the string
                // then return, and then we move on to the next token)
                break;
            case ';' :
                // case for a comment (when we find this we need to skip the rest of the line)
                break;
            
            // Now we also need to figure out integers and doubles (signs, decimal points, etc)

            default :
                // this is our "else"
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