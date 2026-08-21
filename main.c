#include "header.h"


#define BUF_SIZE 128

// Nodes and linked list stuff

Node *node_create(Node* prev_node, double value, char type)
{
    Node *curr_node = malloc( sizeof(Node) );

    curr_node->value = value;
    curr_node->type = type;
    curr_node->prev = prev_node;

    if(prev_node != NULL)
        prev_node->next = curr_node;
    
    curr_node->next = NULL;
    return curr_node;
}


// Actions stuff

// Mathematical operations(i call them actions)
double add          (double a, double b) { return a+b; }
double substract    (double a, double b) { return a-b; }
double multiply     (double a, double b) { return a*b; }
double divide       (double a, double b) { return a/b; }

const Action actions[] = { 
    { '+', 'a', 1, add }, 
    { '-', 'a', 1, substract }, 
    { '*', 'a', 2, multiply }, 
    { '/', 'a', 2, divide },
    { '^', 'a', 2, pow}
};

const int actions_am = sizeof(actions) / sizeof(Action);        // actions_am is amount of actions


// Functions

int find_action(char symbol)
{
    for(int i = 0; i < actions_am; ++i)
    {
        if(actions[i].symbol == symbol)
        {
            return i;
        }
    }
    return -1;
}

char getC(void)
{
    char c;
    do
    {
        c = getchar();
    }while( (isspace(c) && c != '\n') || c == EOF);

    if(isprint(c))
        return c;
    else if (c == '\n' || c == '=' || c == '\0')
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}

double get_num(char *c)
{
    int i;
    *c;
    char arr[BUF_SIZE];

    for(i=0; (i < BUF_SIZE && isdigit(*c)) || (*c == '.' || *c == ','); i++)
    {
        if( *c == '.' || *c == ',')
        {

            if(arr[i-1] != '.')
                arr[i]='.';
            else --i;

        } else
            arr[i] = *c;

        *c = getC();
    }
    
    arr[i] = '\0';
    double num = atof(arr);

    return num;
}


Node *parser(void)
{
    char c = getC();

    Node *first_node = NULL;
    Node *curr_node = NULL;
    Node *previous_node = NULL;

    if(c == EXIT_FAILURE)
        return NULL;

    while (c != EXIT_SUCCESS)
    {
        if(isdigit(c))
        {
            double num = get_num(&c);

            if(first_node == NULL)
            {
                first_node = node_create(NULL, num, 'n');
                curr_node = first_node;
                previous_node = first_node;
            }
            else
            {
                curr_node = node_create(previous_node, num, 'n');
                previous_node = curr_node;
            }
        }
        else if(c == '(' || c == ')')
        {   
            curr_node = node_create(previous_node, c, 'b');
            previous_node = curr_node;
            c = getC();
        }
        else
        {
            int i;

            for(i = 0; i < actions_am; ++i)
            {
                if(actions[i].symbol == c)
                {
                    char type = actions[i].type;

                    if(first_node == NULL)
                    {
                        if(type == 'r')
                        {
                            first_node = node_create(NULL, c, type);
                            curr_node = first_node;
                            previous_node = first_node;
                        }
                        else return NULL;
                    }
                    else
                    {
                        curr_node = node_create(previous_node, c, type);
                        previous_node = curr_node;
                    }

                    break;
                }
            }
            if(i == actions_am)
                return NULL;

            c = getC();
        }
    }

    curr_node->next = NULL;

    return first_node;
}


double solver(Node *first_node)
{
    if(first_node == NULL)
    {
        puts("Error in parser");
        return EXIT_FAILURE;
    }

    Node *curr_node = first_node;

    while(curr_node->next != NULL)
    {
        Node *prev_node = curr_node->prev;
        Node *next_node = curr_node->next;

        switch(curr_node->type)
        {
            default:
                curr_node = next_node;
                break;

            case 'a':
                int action_id = find_action(curr_node->value);
                int next_action_id = 0;
                if(next_node->next != NULL)
                    next_action_id = find_action(next_node->next->value);

                if(actions[action_id].priority < actions[next_action_id].priority)
                {
                    Node *next_action = next_node->next;
                    next_node->next = next_action->next->next;
                    next_action->next->next = curr_node;    //You can understand curr_node as curr_action

                    double a = next_action->prev->value;
                    double b = next_action->next->value;
                    next_action->prev->value = actions[next_action_id].action(a, b);

                    free(next_action->next);
                    free(next_action);
                }

                double a = prev_node->value;
                double b = next_node->value;
                next_node->value = actions[action_id].action(a, b);

                if(prev_node->prev != NULL)
                {
                    prev_node->prev->next = next_node;
                    next_node->prev = prev_node->prev;
                }
                else
                {
                    first_node = next_node;
                    first_node->prev = NULL;
                }

                free(prev_node);
                free(curr_node);
                curr_node = next_node;
                break;
        }
    }
    return curr_node->value;
}



int main(void)
{
    printf("Type it:\n");
    Node * node = parser();
    // node_printer(node);
    double res = solver(node);
    printf("\nRes: %g\n", res);

    return EXIT_SUCCESS;
}