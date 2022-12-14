#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"


#define ALLOCATE_OBJ(type, objectType)  (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type){
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;
    return object;
}

static uint32_t hashString(const char* key, int length){
    uint32_t hash = 2166136261u;
    for(int i = 0; i < length; i++){
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }

    return hash;
}

static ObjString* allocateString(char* chars, int length, uint32_t hash){
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    tableSet(&vm.strings, string, NIL_VAL);
    string->length = length;
    string->chars = chars;
    string->hash = hash;
    return string;
}

ObjString* takeString(char* chars, int length){
    uint32_t hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm.strings, chars ,length, hash);
    if(interned != NULL) return interned;
    return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length){
    uint32_t hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);

    if(interned != NULL){
        FREE_ARRAY(char, chars, length + 1);
        return interned;
    }

    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length, hash);
}

void printObject(Value value){
    switch(OBJ_TYPE(value)){
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

ObjString* tableFindString(Table* table, const char* chars, int length, uint32_t hash){
    if(table->count == 0) return NULL;

    uint32_t index = hash % table->capacity;
    for(;;){
        Entry* entry = &table->entries[index];
        if(entry->key == NULL){
            //stop if an empty non-tombstone entry
            if(IS_NIL(entry->value)) return NULL;
        } else if(entry->key->length == length && entry->key->hash == hash &&
                    memcmp(entry->key->chars, chars, length) == 0){
            //found it
            return entry->key;
        }

        index = (index + 1) % table->capacity;
    }
}