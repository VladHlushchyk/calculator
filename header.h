#ifndef HEADER_H
#define HEADER_H


// Header files

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


// define values
#define BUF_SIZE 128


// Custom types/structures
typedef struct Node {
    struct Node *next;
    struct Node *prev;      //prev is previous for short
    double value;
    char type;
} Node;
/*types:
    'n' - number;
    'b' - bracket;
    'a' - action like +, *... It takes two numbers: the one before, and one after it;
*/

typedef double (*Func_ptr)(double, double); 

typedef struct {
    char symbol;                        //The symbol to identify the action
    char type;
    int priority;
    Func_ptr action;
} Action;


// Consts
/*
    Array, where all actions is stored.
    You also can add your custom action, it only must have 2 inputs(double a, b) and return double value
*/
extern const Action actions[];

extern const int actions_am;        // actions_am is amount of actions


#endif