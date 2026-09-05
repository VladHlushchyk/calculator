#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "header.h"

/*
    Creates node and returns pointer to it.
*/
Node *node_create(Node* prev_node, double value, char type);


/*
    frees all the nodes what left.
    Returns EXIT_FAILURE if first_node == NULL, and EXIT_SUCCESS if everything is ok.
*/
int free_nodes(Node *first_node);


// Mathematical operations(i call them actions)
double add          (double, double);
double substract    (double, double);
double multiply     (double, double);
double divide       (double, double);

/*
    Finds action by symbol in 
        extern const Action actions[];
    and returns ID of it or -1(if failure)
*/
int find_action(char symbol);


// Parser, and functions to parse
/*
    Reads first non-space letter;
    Returns readed char, EXIT_SUCCESS(if reach end of std_in) or EXIT_FAILURE
*/
char getC(void);

/*
    Reads number from the flow (of nodes), and returns it as double
*/
double get_num(char *c);

/*
    Parses all the date from std_in, and creates flow of nodes that contain it.
    Returns NULL(if failure) or first node of the flow
*/
Node *parser(void);

// Solver
/*
    Solves the example, that is already parsed.
    Needs first_node of the node-flow to work correctly
    Returns the result of example, or EXIT_FAILURE
*/
double solver(Node *first_node);

#endif