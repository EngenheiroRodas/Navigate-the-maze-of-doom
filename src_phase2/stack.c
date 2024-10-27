
/* The following stack structure has taken inspiration from AED/Lab06/src/(stack.h && stack.c) */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

/* Define the Stack structure */
struct stack_ {
    int top;
    unsigned capacity;
    Node** array;
};

/* Function to create a stack of given capacity; initializes size as 0 */
Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Node**) malloc(stack->capacity * sizeof(Node*));
    if (!stack->array) return NULL;
    
    return stack;
}

/* Copies the stack from source to destination */
void copyStack(Stack* source, Stack* destination) {
    while (!isEmpty(destination)) {
        pop(destination);
    }
    
    for (int i = 0; i <= source->top; i++) {
        push(destination, source->array[i]);
    }
    return;
}

/* Stack is full when top is equal to the last index */
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

/* Stack is empty when top is equal to -1 */
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

/* Function to add a Node* to the stack. It increases top by 1 */
void push(Stack* stack, Node* node) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
    return;
}

/* Function to remove a Node* from the stack. It decreases top by 1 */
Node* pop(Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

/* Function to return the top Node* from the stack without removing it */
Node* peek(Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top];
}

int returnIndex(Stack *stack) {
    return stack->top;
}

/* Function to delete the stack and free memory */
void deleteStack(Stack* stack) {
    free(stack->array);
    free(stack);
    return;
}