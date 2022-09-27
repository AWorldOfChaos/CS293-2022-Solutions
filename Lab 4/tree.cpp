// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::insert(int JourneyCode, int price)
{
  cout << "Trying to insert (JourneyCode: " << JourneyCode << ", Price: " << price << ")" << endl;
  
  struct TreeNode *nodeToInsert = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
  if (nodeToInsert == NULL) {
    cerr << "Memory allocation failure." << endl;
    return false;
  }

  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  if (root == NULL) {
    root = nodeToInsert;
    root->shortestPathLength = 1;
    root->longestPathLength = 1;
    return true;
  }
  else {
    // root != NULL
    
    while (currNode != nullptr) {
      if (JourneyCode < currNode->JourneyCode) {
	parentOfCurrNode = currNode;
	currNode = currNode->left;
      }
      else if (currNode->JourneyCode < JourneyCode) {
	parentOfCurrNode = currNode;
	currNode = currNode->right;
      }
      else { // currNode->JourneyCode == JourneyCode
	// There was already a node in the BST with the same journey code
	// as the one that we are trying to insert.  While this shouldn't
	// arise in a real-world scenario (two different journeys shouldn't
	// have the same code), we'll handle it in any case here.
	
	// Insert the new node to the right of currNode
	break;
      }
    }
    
    
    struct TreeNode *lowestNodeForUpdatingPathLengths;
    
    if (currNode == NULL) {
      // JourneyCode is not present in the BST.  We must now
      // insert an appropriate child of parentOfCurrNode.
      //
      // Do not forget to update shortestPathLength and
      // longestPathLength of (possibly all) BST nodes in the
      // path from the root to the new node you are inserting
      
      nodeToInsert->parent = parentOfCurrNode;
      nodeToInsert->shortestPathLength = 1;
      nodeToInsert->longestPathLength = 1;
      
      if (JourneyCode < parentOfCurrNode->JourneyCode) {
	parentOfCurrNode->left = nodeToInsert;
      }
      else if (parentOfCurrNode->JourneyCode < JourneyCode) {
	parentOfCurrNode->right = nodeToInsert;
      }
      else {
	// This case should never arise.  Just a sanity check
	cerr << "Unexpected branch taken!" << endl;
	return false;
      }
      
      lowestNodeForUpdatingPathLengths = parentOfCurrNode;
    }
    else {
      // There was already a node in the BST with the same journey code
      // as the one that we are trying to insert. Insert the new node to
      // the right of currNode
      
      nodeToInsert->right = currNode->right;
      currNode->right = nodeToInsert;
      if (nodeToInsert->right != nullptr) {
	nodeToInsert->right->parent = nodeToInsert;
      }
      nodeToInsert->parent = currNode;
      
      nodeToInsert->shortestPathLength = 1; // due to NULL left child
      if (nodeToInsert->right != nullptr) {
	nodeToInsert->longestPathLength = nodeToInsert->right->longestPathLength + 1;
      }
      else {
	nodeToInsert->longestPathLength = 1; // both left and right children are NULL
      }
      
      lowestNodeForUpdatingPathLengths = currNode;
    }
    
    // Now update the path lengths from lowestNodeForUpdatingPathLengths
    // all the way up to the root
    
    while (lowestNodeForUpdatingPathLengths != NULL) {
      lowestNodeForUpdatingPathLengths->updatePathLengths();
      lowestNodeForUpdatingPathLengths = lowestNodeForUpdatingPathLengths->parent;
    }
    
    return true;
  }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  struct TreeNode *currNode = root;
  while (currNode != nullptr) {
    if (JourneyCode < currNode->JourneyCode) {
      currNode = currNode->left;
    }
    else if (currNode->JourneyCode < JourneyCode) {
      currNode = currNode->right;
    }
    else { // currNode->JourneyCode == JourneyCode
      // Found a node in the BST with the same JourneyCode that we
      // are looking for.  Recall however that we've allowed multiple
      // nodes with the same JourneyCode to be inserted in the
      // BST (may not be realistic, because a journey code is supposed
      // to uniquely identify a journey -- but let's overlook this
      // aspect for now).  Recall also that during insert, we inserted
      // a node with the same journey code as its parent as the
      // right child of the parent.  So, once we've found a node
      // with the journey code we're looking for, we may have to
      // keep going down its right child, grandchild, ...
      // to see if we find a node with matching journey code AND
      // price.  Of course, as we are going down in this way,
      // if we ever find a node with journey code != the required
      // journey code, we can return false.  This is because
      // all nodes with the same journey code will be present in
      // a contiguous stretch linked by right child pointers.
      
      while (currNode != nullptr) {
	if (currNode->JourneyCode != JourneyCode) {
	  return false;
	}
	else {
	  if (currNode->price != price) {
	    currNode = currNode->right;
	  }
	  else {
	    return true;
	  }
	}
      }
    }
  }
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
  // First find the node to delete using code very similar
  // to that used for find

  struct TreeNode *currNode = root;
  while (currNode != nullptr) {
    if (JourneyCode < currNode->JourneyCode) {
      currNode = currNode->left;
    }
    else if (currNode->JourneyCode < JourneyCode) {
      currNode = currNode->right;
    }
    else { // JourneyCode == currNode->JourneyCode
      // Recall what we did for "find" in this case.
      // We'll do the same thing here as well.
      
      while (currNode != nullptr) {
	if (currNode->JourneyCode != JourneyCode) {
	  // Couldn't find a node with matching journey code
	  // and price
	  return false;
	}
	else {
	  if (currNode->price != price) {
	    currNode = currNode->right;
	  }
	  else {
	    // Found a node that matches both journey code
	    // and price given as arguments of this function.
	    // So we can go ahead and delete this node.

	    struct TreeNode *nodeToDelete = currNode;
	    struct TreeNode *parentOfNodeToDelete = currNode->parent;
	    struct TreeNode *lowestNodeForUpdatingPathLengths = nullptr;
    
	    // Case 1: nodeToDelete is a leaf (has no children)
	    
	    // Simply delete nodeToDelete and update its parent's
	    // left/right child pointer to nullptr.  We will update
	    // the shortest/longest path lengths from affected nodes
	    // later.  However, we will remember the lowest node whose
	    // shortest/longest path lengths may have to be updated.
    
	    if ((nodeToDelete->left == nullptr) && (nodeToDelete->right == nullptr)) {
	      if (parentOfNodeToDelete != nullptr) {
		if (parentOfNodeToDelete->left == nodeToDelete) {
		  // Deleting left child of parentOfNodeToDelete
		  // Hence update the left child pointer of parentOfNodeToDelete
		  // to nullptr.  In the following function, "true" indicates
		  // that we are updating the left child of parentOfNodeToDelete
	  
		  updateBSTParentChild(nullptr, parentOfNodeToDelete, true);
		}
		else {
		  // Deleting right child of parentOfNodeToDelete
	  
		  updateBSTParentChild(nullptr, parentOfNodeToDelete, false);
		}
		
		lowestNodeForUpdatingPathLengths = parentOfNodeToDelete;
	      }
	      else { // parentOfNodeToDelete == nullptr
		// Recall that nodeToDelete is a leaf.  If its parent
		// is nullptr, then the tree had only one node (root), which
		// is also nodeToDelete.
	
		// In this case, the root of the BST has to be set to null
		
		root = nullptr;
		lowestNodeForUpdatingPathLengths = nullptr;
	      }
      
	      delete nodeToDelete;
	    }
	    else {
	      if ((nodeToDelete->left == nullptr) || (nodeToDelete->right == nullptr)) {
		// Case 2: nodeToDelete is not a leaf node, and has exactly one
		//         child
	
		if (nodeToDelete == root) {
		  // This is a simple case to handle.  Simply make the (only)
		  // child of root as the new root.
	  
		  if (nodeToDelete->left != nullptr) {
		    root = nodeToDelete->left;
		  }
		  else {
		    // nodeToDelete->right != nullptr
		    root = nodeToDelete->right;
		  }
		  
		  root->parent = nullptr;
		  lowestNodeForUpdatingPathLengths = nullptr;
		  // Note that no path length updations are needed here
		  
		  delete nodeToDelete;
		}
		else {
		  // nodeToDelete is not root
		  
		  // In this case, we must connect the parent of nodeToDelete
		  // appropriately to the only child of nodeToDelete
		  
		  struct TreeNode *parentOfNodeToDelete = nodeToDelete->parent;
		  struct TreeNode *childOfNodeToDelete;
		  
		  if (nodeToDelete->left != nullptr) {
		    childOfNodeToDelete = nodeToDelete->left;
		  }
		  else {
		    childOfNodeToDelete = nodeToDelete->right;
		  }
		  
		  if (parentOfNodeToDelete->left == nodeToDelete) {
		    updateBSTParentChild(childOfNodeToDelete, parentOfNodeToDelete, true);
		  }
		  else {
		    updateBSTParentChild(childOfNodeToDelete, parentOfNodeToDelete, false);
		  }
		  
		  lowestNodeForUpdatingPathLengths = parentOfNodeToDelete;
		  delete nodeToDelete;
		}
	      }
	      else {
		// Case 3: nodeToDelete has two children
		
		// In this case, we can either proceed with finding the
		// predecessor of nodeToDelete in sorted order, or
		// the successor of nodeToDelete in sorted order.
		
		// Choosing to proceed with finding successor of nodeToDelete
		// in the sorted order.
		// This is the leftmost node in the right subtree of nodeToDelete
		
		// Move right once, and then continue along the left
		// children until the leftmost node is encountered.
		
		struct TreeNode *successorNode = nodeToDelete->right;
		while (successorNode != nullptr) {
		  if (successorNode->left != nullptr) {
		    successorNode = successorNode->left;
		  }
		  else break;
		}
		
		// Found the leftmost node in the right subtree.
		// Clearly successorNode has no left child.
		
		// Now move successorNode to where nodeToDelete was.
		// A few sub-cases need to be considered here.
	
		struct TreeNode *parentOfSuccessorNode = successorNode->parent;
		
		if (parentOfSuccessorNode == nodeToDelete) {
		  // successorNode is right child of nodeToDelete
		  
		  // Since successorNode is now replacing nodeToDelete, let's
		  // make the left child of nodeToDelete the new left child of
		  // successorNode.
	  
		  updateBSTParentChild(nodeToDelete->left, successorNode, true);
	  
		  // The right child of nodeToDelete was successorNode itself.
		  // So, no change needs to be done to the right child of
		  // successorNode.
		  
		  lowestNodeForUpdatingPathLengths = successorNode;
		}
		else {
		  // nodeToDelete is not the parent of successorNode.
		  // Therefore, parentOfSuccessorNode is a descendant of
		  // nodeToDelete.
		  
		  // Recall successorNode has no left subtree.  But it
		  // can have a right (possibly NULL) subtree.
		  // Make the right subtree of successorNode the left
		  // subtree of parentOfSuccessorNode
	  
		  updateBSTParentChild(successorNode->right, parentOfSuccessorNode, true);
		  
		  // Since nodeToDelete must be replaced with successorNode,
		  // make the left/right subtrees of nodeToDelete the new left/right
		  // subtrees, respectively, of successorNode
		  
		  updateBSTParentChild(nodeToDelete->left, successorNode, true);
		  updateBSTParentChild(nodeToDelete->right, successorNode, false);
		  
		  lowestNodeForUpdatingPathLengths = parentOfSuccessorNode;
		}
	
		// Finally replace nodeToDelete with successorNode
		
		if (nodeToDelete->parent != nullptr) {
		  // nodeToDelete is not the root
		  if (nodeToDelete->parent->left == nodeToDelete) {
		    updateBSTParentChild(successorNode, nodeToDelete->parent, true);
		  }
		  else {
		    updateBSTParentChild(successorNode, nodeToDelete->parent, false);
		  }
		}
		else {
		  // nodeToDelete is the root.  So now successorNode becomes
		  // the root.
		  root = successorNode;
		}

		delete nodeToDelete;
	      }
	    }
	    
	    // REMEMBER to update the shortest and longest path
	    // lengths of appropriate nodes in the tree after a
	    // successful deletion.
	    
	    currNode = lowestNodeForUpdatingPathLengths;
	    while (currNode != nullptr) {
	      currNode->updatePathLengths();
	      currNode = currNode->parent;
	    }
	    
	    return true;
	  }
	}
      }
    }
  }

  // Couldn't find a node with matching journey code
  return false;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
	// Are there any other siblings to the right?
	bool rightSiblingPresent = (isLeft && (curr->parent->right != nullptr));
        printBST( prefix + (rightSiblingPresent ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (rightSiblingPresent ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}

