#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  
};

class Dictionary {
 private:
  int N; // size of array A
  struct Journey *J; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key);
  
  // Default constructor
  Dictionary(); 

  // Return a vector of journeys starting from the given source station.
  vector<struct Journey*> get(string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Journey j);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(string key);
};

#endif