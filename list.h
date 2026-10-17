#ifndef LIST_H
#define LIST_H

// 맨날 하는거
typedef struct listnode listnode;
typedef struct list list;

typedef void*       listdata;
typedef listnode*   listlink;

struct listnode
{
    listdata item;
    listlink next;
};
struct list
{
    listnode* root;
    int length;
};

// 외부 함수
void list_init_list(list* list);
list* list_create_list();
void list_insert_at_head(list* list, listdata item);
void list_insert_at_tail(list* list, listdata item);
void list_insert_at(list* list, listdata item, int index);
void list_insert_after(list* list, listdata item, listnode* node);
void list_delete_at_head(list* list);
void list_delete_at_tail(list* list);
void list_delete_at(list* list, int index);
void list_delete_after(list* list, listnode* node);
void list_delete_if(list* list, void* context, int (*condition)(void*, listdata));
listnode* list_search(list* list, listdata item, int (*compare)(listdata, listdata));
listdata list_get_at(list* list, int index);
listdata list_get_if(list* list, void* context, int (*condition)(void*, listdata));
int list_get_length(list* list);
int list_isListEmpty(list* list);
void list_print_list(list* list, void (*print)(listdata));
void list_clear_list(list** list);

#endif