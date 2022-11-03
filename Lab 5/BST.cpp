#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST
  if (!root)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }

  TreeNode *current = root;

  TreeNode *newNode = new TreeNode(jrnyCode, price);

  while (true)
  {
    if (BSTLessThan(newNode, current))
    {
      if (!current->left)
      {
        updateBSTParentChild(newNode, current, true);
        return true;
      }
      else
      {
        current = current->left;
      }
    }
    else
    {
      if (!current->right)
      {
        updateBSTParentChild(newNode, current, false);
        return true;
      }
      else
      {
        current = current->right;
      }
    }
  }
  return false;
}

int BST::find(int jrnyCode)
{
  TreeNode *currentNode = root;
  TreeNode *searchNode = new TreeNode(jrnyCode, -1);

  while (currentNode != nullptr)
  {
    if (BSTLessThan(searchNode, currentNode))
    {
      currentNode = currentNode->left;
    }
    else if (BSTLessThan(currentNode, searchNode))
    {
      currentNode = currentNode->right;
    }
    else
    {
      return 1;
    }
  }

  return -1;
}

bool BST::remove(int jrnyCode)
{

  // IF NODE NOT FOUND
  TreeNode *searchNode = new TreeNode(jrnyCode, -1);
  TreeNode *currentNode = root;
  while (currentNode != nullptr)
  {
    if (BSTLessThan(searchNode, currentNode))
    {
      currentNode = currentNode->left;
    }
    else if (BSTLessThan(currentNode, searchNode))
    {
      currentNode = currentNode->right;
    }
    else
    {
      break;
    }
  }

  if(currentNode == nullptr){
    return false;
  }

  // NO CHILDREN
  if (!currentNode->left && !currentNode->right)
  {
    if (!currentNode->parent)
    {
      root = nullptr;
    }
    else if (BSTLessThan(currentNode, currentNode->parent))
    {
      currentNode->parent->left = nullptr;
    }
    else
    {
      currentNode->parent->right = nullptr;
    }
  }

  // THERE IS NO LEFT CHILD (ONLY RIGHT CHILD IS PRESENT)
  else if (!currentNode->left)
  {
    if (!currentNode->parent)
    {
      updateBSTParentChild(currentNode->right, nullptr, true);
      root = currentNode->right;
    }
    else
    {
      if (BSTLessThan(currentNode, currentNode->parent))
      {
        updateBSTParentChild(currentNode->right, currentNode->parent, true);
      }
      else
      {
        updateBSTParentChild(currentNode->right, currentNode->parent, false);
      }
    }
  }

  // THERE IS NO RIGHT CHILD (ONLY LEFT CHILD IS PRESENT)
  else if (!currentNode->right)
  {
    if (!currentNode->parent)
    {
      updateBSTParentChild(currentNode->left, nullptr, true);
      root = currentNode->left;
    }
    else
    {
      if (BSTLessThan(currentNode,  currentNode->parent))
      {
        updateBSTParentChild(currentNode->left, currentNode->parent, true);
      }
      else
      {
        updateBSTParentChild(currentNode->left, currentNode->parent, false);
      }
    }
  }

  // THE NODE HAS BOTH ITS CHILDREN
  else
  {
    TreeNode *successor = currentNode->right;
    while (successor->left)
    {
      successor = successor->left;
    }

    // DELETE THE SUCCESSOR
    if (! successor->right)
    {
      if (BSTLessThan(successor , successor->parent))
      {
        successor->parent->left = nullptr;
      }
      else
      {
        successor->parent->right = nullptr;
      }
    }
    else
    {

      if (BSTLessThan(successor, successor->parent))
      {
        updateBSTParentChild(successor->right, successor->parent, true);
      }
      else
      {
        updateBSTParentChild(successor->right, successor->parent, false);
      }
    }
    // COPY SUCCESSOR TO THE CURRENT NODE

    if(currentNode->parent){
      bool isCurrentNodeLeftChild = BSTLessThan(currentNode, currentNode->parent);
      updateBSTParentChild(currentNode->left, successor, true);
      updateBSTParentChild(currentNode->right, successor, false);
      updateBSTParentChild(successor, currentNode->parent, isCurrentNodeLeftChild);
    }
    else{
      updateBSTParentChild(currentNode->left, successor, true);
      updateBSTParentChild(currentNode->right, successor, false);
      updateBSTParentChild(successor, nullptr, true);
      root = successor;
    }
  }
  
  return true;
}
