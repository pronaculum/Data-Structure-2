#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "hash.h"

#pragma region 내부_함수
// 내부 함수
int hash_function(hashkey key, int length) {
    double tmp = *(unsigned int*)key * GOLD;
    return (int)((tmp - (unsigned int)tmp) * length);
}
int hash_is_equal(hashtype type, hashkey key1, hashkey key2) {
    int result = 1;
    switch (type)
    {
    case STRING:
        for (int i=0;i<4;i++) result *= ((char*)key1)[i] == ((char*)key2)[i];
        return result;
    case UNSIGNEDINT:
        return *(unsigned int*)key1 == *(unsigned int*)key2;
    case INDEX :
        return *(int*)key1 == *(int*)key2;
    }
    return 0;
}
int hash_condSTR(void* context, listdata listdata) { return hash_is_equal(STRING, (hashkey)context, ((hashnode*)listdata)->key); } //5번 기능(1)
int hash_condUINT(void* context, listdata listdata) { return hash_is_equal(UNSIGNEDINT, (hashkey)context, ((hashnode*)listdata)->key); }
int hash_condINDEX(void* context, listdata listdata) { return hash_is_equal(INDEX, (hashkey)context, ((hashnode*)listdata)->key); } //4번 기능(1)
hashnode* hash_create_hashbucket(hashdata item, hashkey key) {
    hashnode* new_hashnode = (hashnode*)malloc(sizeof(hashnode));
    if (new_hashnode == NULL) return NULL;
    new_hashnode->item = item;
    new_hashnode->key = key;
    return new_hashnode;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
hash* hash_create_hash(int length, hashtype type) {
    hash* new_hash = (hash*)malloc(sizeof(hash));
    if(new_hash==NULL) return NULL;
    new_hash->buckets = (list**)malloc(sizeof(list*)*length);
    if(new_hash->buckets==NULL) {
        free(new_hash);
        return NULL;
    }
    for(int i=0; i<length; i++) {
        new_hash->buckets[i] = list_create_list();
    }
    new_hash->length = length;
    new_hash->count = 0;
    new_hash->type = type;
    return new_hash;
}

void hash_push(hash* hash, hashdata item, hashkey key) {
    list* bucket = hash->buckets[hash_function(key, hash->length)];
    hashnode* new_hashnode = hash_create_hashbucket(item, key);
    if (new_hashnode == NULL) return;
    if (list_get_if(bucket, key, (hash->type == STRING)?&hash_condSTR:&hash_condUINT) != NULL) return;
    hashnode* result = NULL;
    switch (hash->type) {
        case STRING:        result = list_get_if(bucket, key, &hash_condSTR);   break;
        case UNSIGNEDINT:   result = list_get_if(bucket, key, &hash_condUINT);  break;
        case INDEX :        result = list_get_if(bucket, key, &hash_condINDEX); break;
    }
    if (result != NULL) return;
    //이미 있자나용;;
    list_insert_at_tail(bucket, new_hashnode);
    hash->count++;
}

hashnode* hash_pop(hash* hash, hashkey key) { //4번 기능(2), 5번 기능(2)
    list* bucket = hash->buckets[hash_function(key, hash->length)];
    hashnode* result = NULL;
    switch (hash->type) {
        case STRING:        result = list_get_if(bucket, key, &hash_condSTR);   break;
        case UNSIGNEDINT:   result = list_get_if(bucket, key, &hash_condUINT);  break;
        case INDEX :        result = list_get_if(bucket, key, &hash_condINDEX); break;
    }
    switch (hash->type) {
        case STRING:        list_delete_if(bucket, key, &hash_condSTR);   break;
        case UNSIGNEDINT:   list_delete_if(bucket, key, &hash_condUINT);  break;
        case INDEX :        list_delete_if(bucket, key, &hash_condINDEX); break;
    }
    if (result != NULL) hash->count--;
    return result;
}

hashnode* hash_peek(hash* hash, hashkey key) { //4번 기능(3), 5번 기능(3)
    list* bucket = hash->buckets[hash_function(key, hash->length)];
    switch (hash->type) {
        case STRING:        return list_get_if(bucket, key, &hash_condSTR);
        case UNSIGNEDINT:   return list_get_if(bucket, key, &hash_condUINT);
        case INDEX :        return list_get_if(bucket, key, &hash_condINDEX);
    }
    return NULL;
}

void hash_print_node(hashnode* node, void(*print)(void*)) {
    if (node == NULL)  {
        printf("NULLERR\n");
        return;
    }
    print(node->item);
}
#pragma endregion