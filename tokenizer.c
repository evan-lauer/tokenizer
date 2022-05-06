#include "value.h"
#include "linkedlist.c"
#include "talloc.c"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// Read all of the input from stdin, and return a linked list consisting of the
// tokens.
Value *tokenize() {
    char charRead;
    Value *list = makeNull();
    charRead = (char)fgetc(stdin);

    while (charRead != EOF) {
        //create new constype node
        Value* newConsNode = cons(charRead, list); // the cdr of this should be the head of the current list
                                                   // (we will create a reverse list first, then reverse it)

        Value* newCarNode; // this will become the node which contains the actual token

        if (charRead == '(') {
            ...
        } else if (charRead == ')') {
            ...
        } else if (charRead == '#') {
            ...
        } else if (charRead == '"') {
            ...
        } else if (charRead == ';') {
            ...
        else {
            ...
        }
        
        // switch (charRead) {
        //     case ' ' :
        //         // case for when the char is a space

        //         break;
        //     case '(' :
        //         // case for open paren
        //         break;
        //     case ')' :
        //         // case for closed paren
        //         break;
        //     case '"' :
        //         // case for open quote (maybe call a helper function?
        //         // and the helper function will read until the end of the string
        //         // then return, and then we move on to the next token)
                
        //         break;
        //     case ';' :
        //         // case for a comment (when we find this we need to skip the rest of the line)
        //         break;
            
        //     // Now we also need to figure out integers and doubles (signs, decimal points, etc)

        //     default :
        //         // this is our "else"
        // }
        charRead = (char)fgetc(stdin);
    }
    Value *revList = reverse(list);
    return revList;
}

// This function should be called when an open quote is found. 
// It will read characters from stdin until another quote is found.
// If a \n or EOF is found before another quote, an error is thrown.
//
// BE CAREFUL WITH THIS! ONLY CALL WHEN " IS FOUND
//
// This method will consume stdin characters up to *and including* the closing quote
char *readString()
{
    char charRead = (char)fgetc(stdin); // this should be the first character of the string

    char* newString = "\"";
    
    while (charRead != EOF && charRead != '\n')
    {
        if (charRead == '"')
        {
            return strcat(newString, (char)('"'));
        } else
        {
            // add charRead to newString
            newString = strcat(newString, charRead);
        }
        charRead = (char)fgetc(stdin);
    } // if we reach the end of the this while loop before we return, it means we have an error.
    printf("Syntax error: Closing quotation (\") expected.\n");
    texit(1);
}

// Displays the contents of the linked list as tokens, with type information
void displayTokens(Value *list){
    //token = car(list);
    printf("%c : %s \n", car(list), car(list)->type);
    if (cdr(list)->type != NULL_TYPE){
        displayTokens(cdr(list));
    }
}