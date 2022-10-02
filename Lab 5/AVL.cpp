#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild = true;

  if(greatGrandParentNode == nullptr){       //// dont check left right if the greatgrandparent is nullptr
                                              //// That is Grandparent is root
    root = parentNode;

  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T3 = parentNode->right;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parentNode, true);
  
  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{


  TreeNode *greatGrandParentNode = grandParentNode->parent;
  

  bool isGPLeftChild;

  if(greatGrandParentNode == nullptr){   //// dont check left right if the greatgrandparent is nullptr
                                              //// That is Grandparent is root
    root = currNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T2 = currNode->left;
  
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  
  updateAVLParentChild(parentNode, currNode, true);
  
  updateAVLParentChild(grandParentNode, currNode, false);

  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;

  if(greatGrandParentNode == nullptr){         //// dont check left right if the greatgrandparent is nullptr
                                              //// That is Grandparent is root
    root = currNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    // Shouldn't happen ever
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(T3, parentNode, true);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  bool isGPLeftChild;

  if(greatGrandParentNode == nullptr){    //// dont check left right if the greatgrandparent is nullptr
                                          //// That is Grandparent is root
    root = parentNode;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }
  TreeNode *T3 = parentNode->left;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  return true;

}

bool AVLTree::insert(int jrnyCode, int price)
{

  TreeNode *newNode = new TreeNode(jrnyCode, price); // a node that will be added to the tree
  newNode->height = 0;

  TreeNode *currentNode = root;   // iterator node
  
  if(currentNode == nullptr){  // ROOT case
    root = newNode;
    root->height = 0;
    return true;
  }

  bool isLeftChild;
  bool parentNodeFound = false;

  while(!parentNodeFound){
    if(AVLLessThan(newNode, currentNode)){  // GO left
      if(!currentNode->left){               // found the empty space
        isLeftChild = true;
        parentNodeFound = true;
      }
      else{ 
        currentNode = currentNode->left;
      }
    }
    else{                                 // GO right
      if(!currentNode->right){            // empty space found
        isLeftChild = false;
        parentNodeFound = true;
      }
      else{                               
        currentNode = currentNode->right;
      }
    }
  }

  updateAVLParentChild(newNode, currentNode, isLeftChild); // add the new node
  

  TreeNode *child = newNode;
  TreeNode *grandchild = nullptr;  // keep track of the two descendentants dont have to calculate it later 
  bool isChildLeft, isGrandChildLeft;

  while(currentNode != nullptr){
    int leftHeight = -1;
    int rightHeight = -1;
    if(currentNode->left){
      leftHeight = currentNode->left->height;
    }
    if(currentNode->right){
      rightHeight = currentNode->right->height;
    }

    if(max(rightHeight, leftHeight) + 1 != currentNode->height ){
      currentNode->height = max(rightHeight, leftHeight) + 1;
    }
    else{  // height didn't change so no need to check further 
      return true;
    }

    if(abs(leftHeight - rightHeight) > 1){ // Rotation case;
      if(isChildLeft && isGrandChildLeft){ 
        
        /*
                    z
                  /
                 y
                /
               x
        */

        currentNode->height -= 2;
        rotateLeftLeft(grandchild, child, currentNode);
        return true; 
      }
      else if(!isChildLeft && !isGrandChildLeft){
        
        /*
             z
              \
               y
                \
                 x
        */
        currentNode->height-=2;
        rotateRightRight(grandchild, child, currentNode);
        return true;;
      }
      else if(!isChildLeft && isGrandChildLeft){
       
        /*
            z
             \
              y
             /
            x
        */
        child->height--;
        grandchild->height++;
        currentNode->height-=2;
        rotateRightLeft(grandchild, child, currentNode);
        return true;
      }
      else if(isChildLeft && !isGrandChildLeft){
        
        /*
            z
           /
          y
           \
            x
        */
        
        child->height--;
        grandchild->height++;
        currentNode->height-=2;
        rotateLeftRight(grandchild, child, currentNode);
        return true;
      }
    }
    

    // update the grandchild and child
    grandchild = child;
    child = currentNode;
    currentNode = currentNode->parent;
    if(!currentNode){
      break;
    }
    if(currentNode->left == child){
      isChildLeft = true;
    }
    else{
      isChildLeft = false;
    }

    if(child->left == grandchild){
      isGrandChildLeft = true;
    }
    else{
      isGrandChildLeft = false;
    }


  }


  return true;
}




// BASIC FIND EQUIVALENT TO ANY OTHER BST FIND
int AVLTree::find(int jrnyCode)
{
 

  TreeNode *currentNode = root;
  TreeNode *searchNode = new TreeNode(jrnyCode, -1);
  
  while(currentNode != nullptr){
    if(AVLLessThan(searchNode, currentNode)){
      currentNode = currentNode->left;
    }
    else if(AVLLessThan(currentNode, searchNode)){
      currentNode = currentNode->right;
    }
    else{
      return 1;
    }
  }

  return -1;
}


bool AVLTree::remove(int jrnyCode)
{
  
  TreeNode *currentNode = root; // iterator
  TreeNode *nodeNeeded = new TreeNode(jrnyCode, -1); // node to find with same journey code

  while(currentNode != nullptr){ 
    if(AVLLessThan(nodeNeeded, currentNode)){ // searching for node
      currentNode = currentNode->left;
    }
    else if(AVLLessThan(currentNode, nodeNeeded)){ // still searching
      currentNode = currentNode->right;
    }
    else{ // found it, currentNode is the required node
      bool isCurrentLeftChild;
      if(currentNode->parent == nullptr){
        isCurrentLeftChild = true;
      }
      else if(AVLLessThan(currentNode, currentNode->parent)){
        isCurrentLeftChild = true;
      }
      else{
        isCurrentLeftChild = false;
      }


      if(currentNode->left == nullptr && currentNode->right == nullptr){ // leaf case 
        currentNode = nullptr;
      }
      else if(currentNode->right == nullptr){ // has left child
        updateAVLParentChild(currentNode->left, currentNode->parent, isCurrentLeftChild);
      }
      else if(currentNode->left == nullptr){ // has right child
        updateAVLParentChild(currentNode->right, currentNode->parent, isCurrentLeftChild);
      }
      else{ // has both children 

        TreeNode *minimum = currentNode->right;
        while(minimum->left != nullptr) minimum = minimum->left; // find minimum
        TreeNode *temp = minimum->parent;
        if(minimum->right) temp = minimum->right; // find the node where we will start next 

        updateAVLParentChild(minimum->right, minimum->parent, false);
        updateAVLParentChild(currentNode->left, minimum, false );
        updateAVLParentChild(minimum, currentNode->parent, isCurrentLeftChild); // move the minimum to the new spot 
        
        if(temp == currentNode) currentNode = minimum; // special case if parent was the one to be deleted 
        else currentNode = temp; 
      }
      // return true;; 
      break;
    } 
  }


  if(currentNode == nullptr){
    return false;
  }

  TreeNode *child = nullptr;
  TreeNode *grandchild = nullptr;
  bool isChildLeft, isGrandChildLeft;


  print();
  while(currentNode != nullptr){

    int leftHeight = -1;
    int rightHeight = -1;
    if(currentNode->left != nullptr) leftHeight = currentNode->left->height;
    if(currentNode->right != nullptr) rightHeight = currentNode->right->height;

    currentNode->height = 1 + max(leftHeight, rightHeight); // update height

    if(abs(leftHeight - rightHeight) > 1){ // rotation needed 
      
      // calculate the child and grandchild as needed
      if(leftHeight > rightHeight){
        child = currentNode->left;
        isChildLeft = true;
      }
      else{
        child = currentNode->right;
        isChildLeft = false;
      }

      int leftChildHeight = -1;
      int rightChildHeight = -1;
      if(child->left != nullptr) leftChildHeight = child->left->height;
      if(child->right != nullptr) rightChildHeight = child->right->height;

      if(leftChildHeight > rightChildHeight){
        grandchild = child->left;
        isGrandChildLeft = true;
      }
      else{
        grandchild = child->right;
        isGrandChildLeft = false;
      }



      if(isChildLeft && isGrandChildLeft){ 
        
        /*
                    z
                  /
                 y
                /
               x
        */

        currentNode->height -= 2;
        rotateLeftLeft(grandchild, child, currentNode);
        currentNode = child;
      }
      else if(!isChildLeft && !isGrandChildLeft){
        
        /*
             z
              \
               y
                \
                 x
        */
        currentNode->height-=2;
        rotateRightRight(grandchild, child, currentNode);
        currentNode = child;
      }
      else if(!isChildLeft && isGrandChildLeft){
       
        /*
            z
             \
              y
             /
            x
        */
        child->height--;
        grandchild->height++;
        currentNode->height-=2;
        rotateRightLeft(grandchild, child, currentNode);
        currentNode = grandchild;
      }
      else if(isChildLeft && !isGrandChildLeft){
        
        /*
            z
           /
          y
           \
            x
        */
        
        child->height--;
        grandchild->height++;
        currentNode->height-=2;
        rotateLeftRight(grandchild, child, currentNode);
        currentNode = grandchild;
      }

    }
    
    currentNode = currentNode->parent; // go to parent
  }
  return true;
}


