#include "value.h"
#include "linkedlist.c"
#include "talloc.c"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//tokenizing numbers
Value *numToken(char charRead) {
    char *fullnumber = talloc(301); //input cannot be longer than 300 chars
    int doubleCheck = 0;
    int numSize = 0;
    if (charRead == '+' || charRead == '-') {
      fullnumber[0] = charRead; //add
      numSize++;
      char symbolsign = charRead;
      charRead = (char)fgetc(stdin);

      if (!isdigit(charRead)) {
        charRead = ungetc(charRead, stdin);
        charRead = ungetc(symbolsign, stdin); //add back +/- since not number
        return symbolHelp(charRead);
      }
    }

    while (isdigit(charRead) || charRead == '.') { //int or double
        if (charRead == '.') {
            doubleCheck = 1; //is a double
        }
        fullnumber[numSize] = charRead;
        numSize++;
        charRead = (char)fgetc(stdin);
    }

    fullnumber[numSize] = '\0'; //end of num
    char *endptr;
    Value *newToken = talloc(sizeof(Value));
    if (doubleCheck) {
        newToken->type = DOUBLE_TYPE;
        newToken->d = strtod(fullnumber, &endptr);
    } else {
        newToken->type = INT_TYPE;
        newToken->i = strtod(fullnumber, &endptr);
    }
    ungetc(charRead, stdin);
    return newToken;

}
Value *parenthesisToken(char paren)
{
    Value* token = (Value*)talloc(sizeof(Value));
    token->type = STR_TYPE;
    char* string = (char*)talloc(sizeof(char) * 2);
    string[0] = paren;
    string[1] = '\0';
    token->s = string;
    return token;
}

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

        

        if (charRead == '(') {
            Value* token = parenthesisToken('(');
        } else if (charRead == ')') {
            Value* token = parenthesisToken(')');
        } else if (charRead == '#') {
            ...
        } else if (charRead == '"') {
            ...
        } else if (charRead == ';') {
            if(isComment(charRead)){
            }
        else {
            ...
        }
        // else if (charRead == '#') {
        //     ...
        // } else if (charRead == '"') {
        //     ...
        // } else if (charRead == ';') {
        //     ...
        // else {
        //     ...
        // }
        
        charRead = (char)fgetc(stdin);
    }
    Value *revList = reverse(list);
    return revList;
}

bool isInitial(char ch)
{
    if (65 <= ch && ch <= 90 || 97 <= ch && ch <= 122)
    {
        return true;
    }
    if (ch == '!' || ch == '$' || ch == '%' || ch == '&' || ch == '*' || ch == '/' || ch == ':' || ch == '<'
        || ch == '=' || ch == '>' || ch == '?' || ch == '~' || ch == '_' || ch == '^')
    {
        return true;
    }
    return false;
}

bool isSubsequent(char ch)
{
    if (isInitial(ch))
    {
        return true;
    }
    if (isdigit(ch))
    {
        return true;
    }
    if (ch == '.' || ch == '+' || ch == '-')
    {
        return true;
    }
    return false;
}


Value* symbolToken(char charRead)
{
    char* symbol = (char*)talloc(301);
    int symSize = 0;

    char initial = (char)fgetc(stdin);
    if (isInitial(initial))
    {
        symbol[0] = initial;
        symSize++;
    } else
    {
        printf("Syntax error: Untokenizable input: %c\n", initial);
        texit(1);
    }
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
    while(cdr(list)->type != NULL_TYPE){
        if (car(list)->type == INT_TYPE){
            printf("%i : integer \n", car(list));
        }
        if (car(list)->type == BOOL_TYPE){
            printf("%b : boolean \n", car(list));
        }
        if (car(list)->type == STR_TYPE){
            printf("%s : string \n", car(list));
        }
        if (car(list)->type == DOUBLE_TYPE){
            printf("%d : double \n", car(list));
        }
        if (car(list)->type == SYMBOL_TYPE){
            printf("%% : symbol \n", car(list));
        }
        if (car(list)->type == OPEN_TYPE){
            printf("( : open \n", car(list));
        }
        if (car(list)->type == CLOSE_TYPE){
            printf(") : close \n", car(list));
        }
        displayTokens(cdr(list));
    }
    texit(0);
}