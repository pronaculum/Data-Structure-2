#ifndef STACK_H
#define STACK_H

// 맨날 하는거
typedef struct stack    stack;
typedef void*           stackitem;

struct stack {
    stackitem*  items;
    int         top;
    int         max_size;
};

// 외부 함수
stack* stack_create_stack(int max_size);
void stack_delete_stack(stack* stack);
void stack_push(stack* stack, stackitem item);
stackitem stack_pop(stack* stack);
stackitem stack_peek(stack* stack);
int stack_is_empty(stack* stack);
int stack_is_full(stack* stack);

#endif