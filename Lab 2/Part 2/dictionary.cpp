#include "dictionary.h"
#include "planner.h"
#include <string.h>
#include <cstring>
#include <vector>

Dictionary::Dictionary(){
    N = DICT_SIZE;
    J = new Journey[N];
    for(int i = 0; i < N; i++){
        J[i] = *(new struct Journey);
    }
};


int Dictionary::hashValue(string key){
    // key is the source station of the journey
    // int size = sizeof(key)/ sizeof(key[0]);
    int size = key.length();
    char* c_str = new char[size];
    strcpy(c_str, key.c_str());

    int hashValue = 0;
    int x = 33;
    for(int i = size - 1; i >= 0; i--){
        int val = c_str[i] - 'a';
        hashValue = (val + x * hashValue) % N;
    }
    return hashValue;
}

int Dictionary::findFreeIndex(string key){
    int hash = hashValue(key);
    
    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;
        
        if(J[index].src.compare("") == 0){
            return index;
        }
        // We don't actually do deletes here anyway, so ignore
        else if(J[index].src.compare("TOMBSTONE") == 0){
            return index;
        }
    }
    return -1;
}

vector<struct Journey*> Dictionary::get(string key){
    int hash = hashValue(key);
    vector<struct Journey*> journeys;

    // Get all journeys starting from a given source

    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;

        if(J[index].src.compare("") == 0){
            break;
        }

        if(J[index].src.compare(key) == 0){
            journeys.push_back(&J[index]);
        } 
    }

    return journeys;
}

bool Dictionary::put(struct Journey j){

    int freeIndex = findFreeIndex(j.src);
    if(freeIndex == -1){
        return false;
    }
    else{
        J[freeIndex] = j;
        return true;
    }

}


// Ignore below, not used
/*
bool Dictionary::remove(char key[]){
    Journey *j = get(key);
    if(j->key == ""){
        return false;
    }
    else{
        strcpy(j->key, "TOMBSTONE");
        j->value = (int)NULL;
        return true;
    }
}
*/