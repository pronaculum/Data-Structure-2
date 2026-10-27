#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#pragma region 내부_함수
// 내부 함수
listnode* list_create_listnode(listdata item, listlink next) {
    listnode* new_listnode = (listnode*)malloc(sizeof(listnode));
    if (new_listnode==NULL) return NULL;
    new_listnode->item = item;
    new_listnode->next = next;
    return new_listnode;
}

listnode* list_find_tail(list* list) {
    if (list->root==NULL) return NULL;
    listnode* current = list->root;
    while (current->next!=NULL) {current = current->next;}
    return current;
}

listnode* list_find_at(list* list, int index) {
    if (index<0 || index>=list->length) return NULL;
    listnode* current = list->root;
    while (index-->0) {
        current = current->next;
    }
    return current;
}

void list_delete_node(list* list, listnode* before_node, listnode* target_node) {
    if (list->length<=0 || target_node==NULL) return;
    if (before_node==NULL) list->root = target_node->next;
    else before_node->next = target_node->next;
    free(target_node);
    list->length--;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
void list_init_list(list* list) {
    listnode* second_node;
    while(list->length>1) {
        second_node = list->root->next;
        free(list->root);
        list->root = second_node;
        list->length--;
    }
    if(list->root!=NULL) free(list->root);

    list->root = NULL;
    list->length = 0;
}

list* list_create_list() {
    list* new_list = (list*)malloc(sizeof(list));
    if(new_list==NULL) return NULL;
    new_list->root = NULL;
    new_list->length = 0;
    return new_list;
}

void list_insert_at_head(list* list, listdata item) {
    listnode* new_node = list_create_listnode(item, list->root);
    if(new_node==NULL) return;
    list->root = new_node;
    list->length++;
}

void list_insert_at_tail(list* list, listdata item) {
    listnode* new_node = list_create_listnode(item, NULL);
    if(new_node==NULL) return;
    if(list->root==NULL) list->root = new_node;
    else list_find_tail(list)->next = new_node;
    list->length++;
}

void list_insert_at(list* list, listdata item, int index) {
    if(index == 0) {
        list_insert_at_head(list, item);
        return;
    }
    if(index == list->length) {
        list_insert_at_tail(list, item);
        return;
    }
    listnode* before_node = list_find_at(list, index-1);
    if(before_node==NULL) return;
    listnode* new_node = list_create_listnode(item, before_node->next);
    if(new_node==NULL) return;
    before_node->next = new_node;
    list->length++;
}

void list_insert_after(list* list, listdata item, listnode* node) {
    if(node==NULL) return;
    listnode* new_node = list_create_listnode(item, node->next);
    if(new_node==NULL) return;
    node->next = new_node;
    list->length++;
}

void list_delete_at_head(list* list) {
    if(list->length==0) return;
    list_delete_node(list, NULL, list->root);
}

void list_delete_at_tail(list* list) {
    if(list->length==0) return;
    if(list->length==1) {
        list_delete_node(list, NULL, list->root);
        return;
    }
    listnode* before_tail = list_find_at(list, list->length-2);
    list_delete_node(list, before_tail, before_tail->next);
}

void list_delete_at(list* list, int index) {
    if(list->length==0) return;
    if(index==0) {
        list_delete_at_head(list);
        return;
    }
    if(index==list->length-1) {
        list_delete_at_tail(list);
        return;
    }
    listnode* before_node = list_find_at(list, index-1);
    if(before_node==NULL || before_node->next==NULL) return;
    list_delete_node(list, before_node, before_node->next);
}

void list_delete_after(list* list, listnode* node) {
    if(list->length==0 || node==NULL || node->next==NULL) return;
    list_delete_node(list, node, node->next);
}

void list_delete_if(list* list, void* context, int (*condition)(void*, listdata)) {
    if(list->length==0) return;
    listnode* current = list->root;
    listnode* before_node = NULL;
    while(current!=NULL) {
        if(condition(context, current->item)) {
            list_delete_node(list, before_node, current);
            return;
        }
        before_node = current;
        current = current->next;
    }
}

listnode* list_search(list* list, listdata item, int (*compare)(listdata, listdata)) {
    if(list->length==0) return NULL;
    listnode* current = list->root;
    while(current!=NULL) {
        if(compare(current->item, item)==0) return current;
        current = current->next;
    }
    return NULL;
}

listdata list_get_at(list* list, int index) {
    listnode* node = list_find_at(list, index);
    if(node==NULL) return NULL;
    return node->item;
}

listdata list_get_if(list* list, void* context, int (*condition)(void*, listdata)) {
    listnode* cur_ptr = list->root;
    for (int i = 0; i < list->length; i++) {
        listdata item = cur_ptr->item;
        if(condition(context, item)) return item;
        cur_ptr = cur_ptr->next;
    }
    return NULL;
}

int list_get_length(list* list) {
    return list->length;
}

int list_isListEmpty(list* list) {
    return list->length>0?0:1;
}

void list_print_list(list* list, void (*print)(listdata)) {
    if(list->length==0) return;
    listnode* current = list->root;
    while(current!=NULL) {
        print(current->item);
        current = current->next;
    }
}

void list_clear_list(list** list) {
    list_init_list(*list);
    free(*list);
    *list = NULL;
}
#pragma endregion