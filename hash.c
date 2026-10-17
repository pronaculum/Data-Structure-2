#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"

#pragma region 맨날_하는거
// 맨날 하는거
typedef struct hash     hash;
typedef struct hashitem hashitem;

struct hashitem {
    int value;
    int key;
};

struct hash {
    list** nodes;
    int length;
    int count;
};
#pragma endregion

#pragma region 내부_함수
// 내부 함수
int hash_function(int key, int length) {
    return key % length;
}
hashitem* hash_create_hashitem(int value, int key) {
    hashitem* new_hashitem = (hashitem*)malloc(sizeof(hashitem));
    if (new_hashitem == NULL) return NULL;
    new_hashitem->value = value;
    new_hashitem->key = key;
    return new_hashitem;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
hash* hash_create_hash(int length) {
    hash* new_hash = (hash*)malloc(sizeof(hash));
    if(new_hash==NULL) return NULL;
    new_hash->nodes = (list**)malloc(sizeof(list*)*length);
    if(new_hash->nodes==NULL) {
        free(new_hash);
        return NULL;
    }
    for(int i=0; i<length; i++) {
        new_hash->nodes[i] = list_create_list();
    }
    new_hash->length = length;
    new_hash->count = 0;
    return new_hash;
}

void hash_push(hash* hash, int value, int key) {
    list* node = hash->nodes[hash_function(key, hash->length)];
    hashitem* hashitem = hash_create_hashitem(value, key);
    if (hashitem == NULL) return;
    list_insert_at_tail(node, hashitem);
    hash->count++;
}

hashitem* hash_pop(hash* hash, int key) {
    list* node = hash->nodes[hash_function(key, hash->length)];
    hashitem* item;
    for (int i=0;;i++) {
        if(i>=node->length) {
            item = NULL;
            break;
        }
        item = (hashitem*)list_get_at(node, i);
        if (item->key == key) {
            list_delete_at(node, i);
            break;
        }
    }
    hash->count--;
    return item;
}

hashitem* hash_peek(hash* hash, int key) {
    list* node = hash->nodes[hash_function(key, hash->length)];
    hashitem* item;
    for (int i=0;;i++) {
        if(i>=node->length) {
            item = NULL;
            break;
        }
        item = (hashitem*)list_get_at(node, i);
        if (item->key == key) {
            break;
        }
    }
    return item;
}
#pragma endregion