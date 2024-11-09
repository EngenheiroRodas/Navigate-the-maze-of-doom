#ifndef STACK_H
#define STACK_H

typedef struct node_ {
    int row, col;     
    int energy;      
    bool visited;
    struct node_ *up, *down, *left, *right;  
}Node;

typedef struct stack_ Stack;  

Stack* createStack(unsigned capacity);
void copyStack(Stack* source, Stack* destination);
void push(Stack* stack, Node* node);
Node* pop(Stack* stack);
Node* peek(Stack* stack);
int isFull(Stack* stack);
int isEmpty(Stack* stack);
void deleteStack(Stack* stack);
int returnIndex(Stack *stack);

#endif