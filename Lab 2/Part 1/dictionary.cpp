#include "dictionary.h"

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i = 0; i < N; i++){
        Entry e;
        strcpy(e.key, "");
        e.value = (int)NULL;
        A[i] = e;
    }
};


int Dictionary::hashValue(char key[]){
    // int size = sizeof(key)/ sizeof(key[0]);
    int size = 0;
    while(key[size] != '\0'){
        size++;
    }
    int hashValue = 0;
    int x = 33;
    for(int i = size - 1; i >= 0; i--){
        int val = key[i] - 'a';
        hashValue = (val + x * hashValue) % N;
    }
    return hashValue;
}

int Dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);
    
    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;
        
        if(strcmp(A[index].key,"") == 0){
            return index;
        }
        else if(strcmp(A[index].key,"TOMBSTONE") == 0){
            return index;
        }
    }
    return -1;
}

struct Entry* Dictionary::get(char key[]){
    int hash = hashValue(key);

    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;

        if(strcmp(A[index].key,"") == 0){
            return NULL;
        }       

        if(strcmp(A[index].key,key) == 0){
            return &A[index];
        } 
    }

    return NULL;
}

bool Dictionary::put(Entry e){

    int size = sizeof(e.key) / sizeof(e.key[0]);
    int freeIndex = findFreeIndex(e.key);
    if(freeIndex == -1){
        return false;
    }
    else{
        A[freeIndex] = e;
        return true;
    }

}

bool Dictionary::remove(char key[]){
    Entry *e = get(key);
    if(e->key == ""){
        return false;
    }
    else{
        strcpy(e->key, "TOMBSTONE");
        e->value = (int)NULL;
        return true;
    }
}