#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed during quicksort
  bool bstInsertFlag; // Should we insert pivots in the BST?
  
public:
  SorterTree(int choice, int l, int insertInBST); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree() { return tree;} // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor

  bool addArrayElement(int index, Journey jrny);
  int partition(int start, int finish);
  int getComparisons() {return comparisons;}
};
