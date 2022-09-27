#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 4)
    {
      cout<<"Incorrect number of arguments"<<endl;
      exit(0);
    }
  
  int num_entries = atoi(argv[1]); // Number of journeys to enter
  int pivot_chooser = atoi(argv[2]); // Choice of function to be used for choosing pivot
  int insert_in_bst = atoi(argv[3]); // Whether pivots should be inserted in BST or not
  
  assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
  assert(0 <= insert_in_bst && insert_in_bst <= 1);
  assert (num_entries > 0);

  // Write your code here to accept input of journeys, input one per line as a (code, price) pair
  // Also write code here to obtain different inputs as in the various parts of the question
  // Add functionality to time your code (chrono may be helpful here)

  int journeyCode, price;
  SorterTree mySorter(pivot_chooser, num_entries, insert_in_bst);
  
  if (num_entries > 0) {
    for (int i = 0; i < num_entries; i++) {
      cin >> journeyCode >> price;
      cout << "Read " << journeyCode << " " << price << endl;
      Journey myJourney(journeyCode, price);
      mySorter.addArrayElement(i, myJourney);
    }
    
    cout << "Array before quicksort" << endl;
    mySorter.printArray();

    mySorter.Quicksort(0, num_entries-1);

    cout << "Array after quicksort" << endl;
    mySorter.printArray();
    cout << "Number of comparisons in sorting: " << mySorter.getComparisons() << endl;
    
    if (insert_in_bst) {
      BST *treeOfPivots = mySorter.getTree();
      cout << "Printing tree (root imbalance: " << treeOfPivots->getImbalance() << ")" << endl << endl;
      treeOfPivots->printBST(" ", false);

      // The following code is simply to test the find and remove
      // functionality for Binary Search Trees.  It is not really needed
      // for lab assignment 4, and can be safely commented out when
      // running on large examples.
      
      // cout << endl << "Now finding/deleting some elements from BST" << endl;
      // cout << "No. of elements to find/delete from BST: ";

      // int num_el_to_find_delete;
      // cin >> num_el_to_find_delete;
      // cout << num_el_to_find_delete;
      
      // for (int i=0; i < num_el_to_find_delete; i++) {
      // 	cout << "Element " << i+1 << " (JourneyCode Price): ";
      // 	cin >> journeyCode >> price;
      // 	if (treeOfPivots->find(journeyCode, price)) {
      // 	  cout << "Found ... ";
      // 	  if (treeOfPivots->remove(journeyCode, price)) {
      // 	    cout << "and successfully deleted !!!" << endl;
      // 	  }
      // 	  else {
      // 	    cout << "but couldn't be deleted !!!" << endl;
      // 	  }
      // 	}
      // 	else {
      // 	  cout << "Not found ..." << endl;
      // 	}
      // }
      // cout << "Printing tree after deletes" << endl;
      // treeOfPivots = mySorter.getTree();
      // treeOfPivots->printBST(" ", false);
    }
  }
}
