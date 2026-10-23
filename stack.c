#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#pragma region 외부_함수
// 외부 함수
stack* stack_create_stack(int max_size) {
    stack* s = (stack*)malloc(sizeof(stack));
    if (s == NULL) return NULL;
    s->items = (stackitem*)malloc(sizeof(stackitem)*max_size);
    if (s->items == NULL) {
        free(s);
        return NULL;
    }
    s->top = -1;
    s->max_size = max_size;
    return s;
}

void stack_delete_stack(stack* stack) {
    if (stack == NULL) return;
    free(stack->items);
    free(stack);
}

int stack_is_empty(stack* stack) {
    return stack->top == -1;
}

int stack_is_full(stack* stack) {
    return stack->top >= stack->max_size - 1;
}

void stack_push(stack* stack, stackitem item) {
    if (stack == NULL || stack->items == NULL || stack_is_full(stack)) return;
    stack->items[++stack->top] = item;
}

stackitem stack_pop(stack* stack) {
    if (stack == NULL || stack->items == NULL || stack_is_empty(stack)) return NULL;
    return stack->items[stack->top--];
}

stackitem stack_peek(stack* stack) {
    if (stack == NULL || stack->items == NULL || stack_is_empty(stack)) return NULL;
    return stack->items[stack->top];
}

#pragma endregion