#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"

#pragma region 맨날_하는거
// 맨날 하는거
#define GOLD 0.6180339887

typedef struct hash         hash;
typedef struct hashnode     hashnode;
typedef struct context      context;

typedef void*   hashdata;
typedef void*   hashkey;

typedef enum {
    STRING,
    UNSIGNEDINT
} hashtype;

struct hashnode {
    hashdata    item;
    hashkey     key;
};

struct hash {
    list**      buckets;
    int         length;
    int         count;
    hashtype    type;
};

#pragma endregion

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
    }
    return 0;
}
int hash_condSTR(void* context, listdata listdata) { return hash_is_equal(STRING, (hashkey)context, ((hashnode*)listdata)->key); }
int hash_condUINT(void* context, listdata listdata) { return hash_is_equal(UNSIGNEDINT, (hashkey)context, ((hashnode*)listdata)->key); }
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
    //이미 있자나용;;
    list_insert_at_tail(bucket, new_hashnode);
    hash->count++;
}

hashnode* hash_pop(hash* hash, hashkey key) {
    list* bucket = hash->buckets[hash_function(key, hash->length)];
    hashnode* result = list_get_if(bucket, key, (hash->type == STRING)?&hash_condSTR:&hash_condUINT);
    list_delete_if(bucket, key, (hash->type == STRING)?&hash_condSTR:&hash_condUINT);
    if (result != NULL) hash->count--;
    return result;
}

hashnode* hash_peek(hash* hash, hashkey key) {
    list* bucket = hash->buckets[hash_function(key, hash->length)];
    return list_get_if(bucket, key, (hash->type == STRING)?&hash_condSTR:&hash_condUINT);
}
#pragma endregion