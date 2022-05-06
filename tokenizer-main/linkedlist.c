#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>
#include "linkedlist.h"
#include "value.h"


// Create a new NULL_TYPE value node.
Value *makeNull(){
    Value *val = (Value *)malloc(sizeof(Value));
    val->type = NULL_TYPE;
    return val;
}

// Create a new CONS_TYPE value node.
Value *cons(Value *newCar, Value *newCdr){
    Value *consVal = (Value *)malloc(sizeof(Value));
    consVal->type = CONS_TYPE;
    consVal->c = (struct ConsCell){.car = newCar, .cdr = newCdr};
    return consVal;
}


// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
Value *car(Value *list){
    assert(list->type != NULL_TYPE);
    return list->c.car;
}

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
Value *cdr(Value *list){
    assert(list->type != NULL_TYPE);
    return list->c.cdr;
}

// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isNull(Value *value){
    assert(value);
    return (value->type == NULL_TYPE);
}

// Display the contents of the linked list to the screen in some kind of
// readable format
void display(Value *list){
    Value *cur = list;
    while (cur->type != NULL_TYPE) {
        if (car(cur)->type == INT_TYPE){
            printf("value = %d\n", car(cur)->i);
        }
        if (car(cur)->type == DOUBLE_TYPE){
            printf("value = %lf\n", car(cur)->d);
        }
        if (car(cur)->type == STR_TYPE){
            printf("value = %s\n", car(cur)->s);
        }
        cur = cdr(cur);
    }
}

// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory whatsoever between the original list and the new one.
Value *reverse(Value *list){
    Value* cur = list;
    Value* head = makeNull();
    while(cur->type != NULL_TYPE)
    {
        Value* newCar = (Value *)malloc(sizeof(Value));
        if (car(cur)->type == STR_TYPE)
        {
            //newCar = (Value *)malloc(sizeof(Value *));
            newCar->s = malloc(sizeof(char)*(strlen(car(cur)->s) + 1));
            strcpy(newCar->s, car(cur)->s);
            newCar->type = STR_TYPE;
        } else
        if (car(cur)->type == INT_TYPE)
        {
            //newCar = (Value *)malloc(sizeof(Value *));
            newCar->i = car(cur)->i;
            newCar->type = INT_TYPE;
        } else
        if (car(cur)->type == DOUBLE_TYPE)
        {
            //newCar = (Value *)malloc(sizeof(Value *));
            newCar->d = car(cur)->d;
            newCar->type = DOUBLE_TYPE;
        }

        Value* newConsCell = cons(newCar, head);
        head = newConsCell;
        cur = cdr(cur);
    }
    
    return head;
}

// Frees up all memory directly or indirectly referred to by list. This includes strings.
void cleanup(Value *list){
    Value* cur = list;
    while (!isNull(cur)){
        Value *next = cdr(cur);
        if (car(cur)->type == STR_TYPE){
            free(car(cur)->s);
        }
        free(car(cur));
        free(cur);
        cur = next;
    }
    free(cur);
}

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(Value *value){
    Value *cur = value;
    assert(cur);
    int length = 0;
    if (cur->type == NULL_TYPE){
        return 0;
    }
    //need to use assertions but this line failing
    //assert(!isNull(cur));
    while (cur->type != NULL_TYPE){
        Value *next = cdr(cur);
        length++;
        cur = next;
    }
    return length;
}

