#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "sort.h"


#pragma region 내부_함수
// 내부 함수
int minvalue(int a, int b) { return (a>b)?b:a; }
#pragma endregion

#pragma region 외부_함수
// 외부 함수
void sort_Merge(void* base, int length, sort_base_type type) {
    if (length < 2) return;
    if (type == ARRAY_INT) {
        int* result = (int*)malloc(sizeof(int)*length);
        if(result == NULL) return;
        for (int i=1;i<=length;i*=2) { for (int j=0;i*j<length;j+=2) {
                int left_pivot = i*j;                   // 범위 : i*j       ~  i*(j+1)-1
                int right_pivot = i*(j+1);              // 범위 : i*(j+1)   ~  minvalue(i*(j+2)-1, length-1)
                for(int k=i*j;k<=minvalue(i*(j+2)-1, length-1);) {
                    if (right_pivot >= length)                                      result[k++] = ((int*)base)[left_pivot++];
                    else if (((int*)base)[right_pivot] < ((int*)base)[left_pivot])  result[k++] = ((int*)base)[right_pivot++];
                    else                                                            result[k++] = ((int*)base)[left_pivot++];
                    if (left_pivot > i*(j+1)-1)                         { while (k<=minvalue(i*(j+2)-1, length-1)) { result[k++] = ((int*)base)[right_pivot++];  } break; }
                    if (right_pivot > minvalue(i*(j+2)-1, length-1))    { while (k<=minvalue(i*(j+2)-1, length-1)) { result[k++] = ((int*)base)[left_pivot++];   } break; }}}
            for (int k=0;k<length;k++) { ((int*)base)[k] = result[k]; }}
            free(result);
        }
}
void sort_print(void* array, int length, sort_sorting_type type) {
    if (type == MERGE) {
        printf("MergeSort Start\nbefore array : [ ");
        for (int i=0;i<length;i++) printf("%d ", ((int*)array)[i]);
        printf("]\n");
        sort_Merge(array, length, ARRAY_INT);
        printf("after  array : [ ");
        for (int i=0;i<length;i++) printf("%d ", ((int*)array)[i]);
        printf("]\nMergeSort End\n");
    }
}
#pragma endregion

#pragma region 존재해서는 안되는 것들
/*
struct item_ARRAY_INT {
    int start_position;
    int end_position;
    int length;
};

item_ARRAY_INT* sort_create_item_ARRAY_INT(int start_position, int end_position) {
    item_ARRAY_INT* result = (item_ARRAY_INT*)malloc(sizeof(item_ARRAY_INT));
    if(result != NULL) {
        result->start_position  = start_position;
        result->end_position    = end_position;
        result->length          = end_position - start_position + 1;
    }
    return result;
}

stack* stack = stack_create_stack(length);
if(stack == NULL) return;
item_ARRAY_INT* item = NULL;
item_ARRAY_INT* another = NULL;
int start = 1;
int end = length;
int mid = start + end / 2;
stack_push(stack, sort_create_item_ARRAY_INT(start, mid));
stack_push(stack, sort_create_item_ARRAY_INT(mid+1, end));
while(!stack_is_empty(stack)) {
    item = (item_ARRAY_INT*)stack_peek(stack);
    if(item->length > 1) {
        start = item->end_position;
        end = item->end_position;
        mid = start + end / 2;
        stack_push(stack, sort_create_item_ARRAY_INT(start, mid));
        stack_push(stack, sort_create_item_ARRAY_INT(mid+1, end));
    }
    else if(another != NULL && another->length < 2) {
        
    }
}
    명시적 스택으로 하는 머지소트
*/
#pragma endregion