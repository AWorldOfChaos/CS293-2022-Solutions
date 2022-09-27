#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l, int insertInBST)
{
  this->choice = choice;
  comparisons = 0;
  bstInsertFlag = insertInBST;
  
  tree = new BST;
  if (tree == NULL) {
    cerr << "Memory allocation failure." << endl;
  }
  
  if (l > 0) {
    array = new Journey[l];
    if (array != nullptr) {
      this->l = l;
    }
    else {
      this->l = -1;
    }
  }
  else {
    array = nullptr;
    this->l = -1;
  }
}

SorterTree::~SorterTree()
{
  delete[] array;
  delete tree;
}

bool SorterTree::Quicksort(int start, int finish)
{
  // Call appropriate pivot function based on choice
  // Split into 2 parts based on pivot choice
  // Ensure that the pivot is placed at the index returned by partition,
  // so that we can exclude this element in the next two recursive calls
  // to QuickSort.  This is slightly different from what is given in
  // Prof. Naveen Garg's notes/video lectures.
  // Recursively keep sorting

  // This function also looks at the bstInsertFlag, and if
  // this is set to true, then it inserts pivots in the BST
  // in sequence in which they are used in Quicksort.
  // This allows us a clean way to prevent duplication of the Quicksort
  // code in QuicksortWithBSTInsert

  if (start < finish) {
    int index = partition(start, finish);
    cout << "Pivot is (JourneyCode: " << array[index].getJourneyCode() << ", Price: " << array[index].getPrice() << ")" << endl;
    
    if (index == -1) {
      cerr << "Error in partitioning." << endl;
      return false;
    }
    else {
      if (bstInsertFlag) {
	tree->insert(array[index].getJourneyCode(), array[index].getPrice());
      }

      bool successFlag1, successFlag2;
      if (start < index) {
	successFlag1 = Quicksort(start, index-1);
      }
      else if (start == index) {
	successFlag1 = true;
      }
      else {
	successFlag1 = false;
      }

      if (successFlag1) {
	if (finish > index) {
	  successFlag2 = Quicksort(index+1, finish); 
	}
	else if (finish == index) {
	  successFlag2 = true;
	}
	else {
	  successFlag2 = false;
	}
      }
      return (successFlag1 && successFlag2);
    }
  }
  if (start == finish) {
    return true;
  }
  else {
    return false;
  }
}

// Use one of the given choose_* functions to choose a pivot element.
// Then partition the array into two parts -- the "right" half, where
// all elements are >= the pivot, and the "left" half, where all
// elements are < (strictly less than) the pivot.
// Note this is slightly different from what Prof. Naveen Gard does
// in his lectures.
// Finally, we make sure that the pivot is placed exactly "between"
// the "left" and "right" halves of the array.  This is also different
// from what Prof. Naveen Gard does in his lectures.  The advantage
// of doing this is that now we need to do Quicksort on sub-arrays
// that DO NOT include the pivot.  The pivot has already moved to its
// rightful position in the sorted array.
//
// Returns the index where the pivot element is placed after partitioning
int SorterTree::partition(int start, int finish)
{
  if (start < finish) {
    Journey *pivot;
    if (choice == 1) {
      pivot = choose_one(array, start, finish);
    }
    else if (choice == 2) {
      pivot = choose_two(array, start, finish);
    }
    else if (choice == 3) {
      pivot = choose_three(array, start, finish);
    }
    else {
      cerr << "Invalid choice option " << choice << endl;
      cerr << "Proceeding with choice 3" << endl;
      pivot = choose_three(array, start, finish);
    }
    
    Journey pivotJourney = *pivot;

    int i = start - 1;
    int j = finish + 1;
    
    while (true) {
      do {
	j = j - 1;
	comparisons++;
      } while (!(array[j] < pivotJourney) && (j > start));

      do {
	i = i + 1;
	comparisons++;
      } while ((array[i] < pivotJourney) && (i < finish));

      // Note the condition for exiting the last do-while loop above is
      // slightly different from what it is in Prof. Naveen Garg's notes/
      // lecture videos. 
      
      if (i < j) {
	// Need to swap array[i] and array[j]
	// Note that array[i] may be the pivot.  However, array[j] can't be the pivot. Why?
	// In case array[i] is the pivot, we also remember where the pivot is being
	// moved.

	if (&(array[i]) == pivot) {
	  pivot = &(array[j]);
	}
	
	Journey temp = array[j];
	array[j] = array[i];
	array[i] = temp;
      }
      else {
	// Now swap array[i] with the pivot
	Journey temp = array[i];

	array[i] = *pivot;
	*pivot = temp;
	
	return i;
      }
    }
  }
  else if (start == finish) {
    return start;
  }
  else {
    return -1;
  }
}

bool SorterTree::addArrayElement(int index, Journey jrny)
{
  if ((index >= 0) && (index < l) && (array != nullptr)) {
    array[index] = jrny;
    return true;
  }
  else {
    return false;
  }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
  // Call appropriate pivot function based on choice
  // Split into 2 parts based on pivot choice
  // Recursively keep sorting
  // Insert chosen pivot into the tree appropriately
  
  // Implemented by invoking Quicksort that has already been implemented
  // but this time bstInsertFlag is set to true.  This makes Quicksort
  // also insert the pivots in the BST.
  
  bstInsertFlag = true;
  bool flag = Quicksort(start, finish);
  bstInsertFlag = false;
  return flag;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
