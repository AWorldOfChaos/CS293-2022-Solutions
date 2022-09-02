#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

template <typename T>
class StackNode{
//element of my_stack
public:
    T val;
    StackNode<T>* next;
    StackNode(T t, StackNode<T>* ptr):val{t},next{ptr}{}
};
template <typename T>
class my_stack{
//stack implemented as a linked list
    StackNode<T>* head = NULL;
public:
    bool empty(){ //returns if the stack is empty
        return (head!=NULL);
    }
    void push(T ptr){//adds an element to the top of the stack
        StackNode<T> *temp = head;
        head = new StackNode<T>{ptr, temp};
    }
    void pop(){ //removes the last added element from the stack
        StackNode<T>* temp = head;
        if(head==NULL) throw "Pop called on empty stack";
        head = head->next;
        delete temp;
    }
    T top(){//returns the value of the most recently added element of the stack
        if(head==NULL) throw "Pop called on empty stack";
        return head->val;
    }
};



// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    // Adding the first node
    if(root == NULL){
        root = new TreeNode(JourneyCode,price,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    if(find(JourneyCode,price))return false;
    TreeNode *curr = root;
    while(true){
        curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(price > curr->price){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(JourneyCode,price,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(JourneyCode,price,NULL,NULL,curr);
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(root==NULL)return false;
    TreeNode* curr = root;
    while(true){
      
        if(curr->price==price){
            if(curr->JourneyCode==JourneyCode){
                return true;
            }else return false;
        } else if(curr->price > price){
      
            if(curr->left==NULL){
                return false;
            }else{
                curr = curr->left;
            }
        }else{
            if(curr->right==NULL){
                return false;
            }else{
                curr = curr->right;
            }
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
  // Returning false, if the node doesn't exist!
    if(!find(JourneyCode,price))return false;
    
    TreeNode* curr = root;
    bool last = false;

    // finding the  node to be deleted
    while(true){
        curr->sizeOfTree--; // Decrement size of subtree for each parent node!
        if(curr->JourneyCode==JourneyCode && curr->price==price){
            break;
        }else if(curr->price > price){
            curr = curr->left;
            last = true;
        }else{
            curr = curr->right;
            last = false;
        }
    }
    // If it has no left child, just replace the node with its right child!
    if(curr->left==NULL){
    
        if(curr->parent!=NULL){
            if(last){
                curr->parent->left = curr->right;
            }else{
                curr->parent->right = curr->right;
            }
            if(curr->right!=NULL){
                curr->right->parent = curr->parent;
            }
            delete curr;
        }else{
            root = curr->right;
            delete curr;  
        }
    }else if(curr->right==NULL){
        //   If it has no right child, just replace it with left child
        if(curr->parent!=NULL){
            if(last){
                curr->parent->left = curr->left;
            }else{
                curr->parent->right = curr->left;
            }
            curr->left->parent = curr->parent;
            
            delete curr;
        }else{
            root = curr->left;
            delete curr;     
        }
    }else{
        // If its has both left and right children

        TreeNode *todel = curr; // Marking the node which is to be deleted
        
        // Find its predecessor
        curr = curr->left;
        last = false;
        
        
        while(curr->right!=NULL){
            
            curr->sizeOfTree--;
            curr = curr->right;
            last = true;
        }

        // Swap the node with its predecessor
        todel->JourneyCode = curr->JourneyCode;
        todel->price = curr->price;
        if(!last){
            curr->parent->left = curr->left;
        }else{
            curr->parent->right = curr->left;
        }
        if(curr->left!=NULL)curr->left->parent = curr->parent;
        
        // Delete the node which previously represented the predecessor
        delete curr;
        
    }
  
    return true; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(root==NULL)return;
    if(typeOfTraversal==0){
        TreeNode * curr = root;
        cout<<"("<<root->JourneyCode<<","<<root->price<<")"<<endl;
        
        // traverse as if the left-subtree was the only structure
        root = curr->left;
        traverse(typeOfTraversal);

        // traverse as if the right-subtree was the only structure

        root = curr->right;
        traverse(typeOfTraversal);
        // leave no side-effects after you're done
        root = curr;
    }else if(typeOfTraversal==1){
        TreeNode * curr = root;

        // traverse as if the left-subtree was the only structure
        root = curr->left;
        traverse(typeOfTraversal);


        // traverse as if the right-subtree was the only structure
        root = curr->right;
        traverse(typeOfTraversal);
        
        cout<<"("<<curr->JourneyCode<<","<<curr->price<<")"<<endl;

        // leave no side-effects after you're done
        root = curr;
        
    }else{
        TreeNode * curr = root;
       
        // traverse as if the left-subtree was the only structure
        root = curr->left;
        traverse(typeOfTraversal);

        cout<<"("<<curr->JourneyCode<<","<<curr->price<<")"<<endl;
        
        
        // traverse as if the right-subtree was the only structure
        root = curr->right;
        traverse(typeOfTraversal);

        // leave no side-effects after you're done
        root = curr;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root==NULL)return -1;
    TreeNode *curr  =root;

    // Moving left as long as you can, to find the minimum
    while(curr->left!=NULL) curr = curr->left;
    return curr->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int lc = 0;     // Maintaining the number of journeys that cost less than the lowerPriceBound
    int rc = 0;     // Maintaining the number of Journeys that cost more than the upperPriceBound
    TreeNode *curr = root;
    
    while(curr!=NULL){
        // If Price is less than bound, then this node along with its left subtree need to be included in lc
        if(curr->price < lowerPriceBound){
            lc += curr->sizeOfTree - (curr->right!=NULL?curr->right->sizeOfTree:0);
            curr = curr->right;
        }else{
        // Else, Just Move Right
            curr = curr->left;
        }
    }
    curr = root;
    while(curr!=NULL){
        // If Price is greater than bound, then this node along with its right subtree need to be included in rc
        if(curr->price > upperPriceBound){
            rc += curr->sizeOfTree - (curr->left!=NULL?curr->left->sizeOfTree:0);
            curr = curr->left;
        }else{
        // Else just move left
            curr = curr->right;
        }
    }

    return (root!=NULL?root->sizeOfTree:0)-lc-rc;   // Provided the tree isn't empty, just subtract lc and rc from the size of the whole tree
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream f(filename);
    root->customStoreSubTree(f);
    f.close();
    return;
}
	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
 
void BST::customLoad (int flag, string filename) {
    ifstream f{filename};
    my_stack<TreeNode*> S; //stack holds pointers to the nodes in which only the left ptr has been assigned to
    int data{0};
    TreeNode* prev{NULL};
    bool isFirstNode{1};
    if(flag==LOAD_LEFT_SUBTREE){
        //ignore the data of the root
        f>>data;
        if(data!=-2){
            f>>data;
            f>>data;
        }
        else return;
    }
    while(f>>data){
        if(data == -1){
            S.push(prev);
            int price, JourneyCode;
            f>>price;
            if(price == -2){
                prev->left = NULL;
            }
            else{
                f>>JourneyCode;
                prev->left = new TreeNode{JourneyCode, price, NULL, NULL, prev};
                prev = prev->left;
            }
            continue;
        }
        if(isFirstNode){
            if(data == -2){
                root = NULL;
                break;
            }
            isFirstNode = 0;
            int jcode;
            f>>jcode;
            root = new TreeNode{jcode, data, NULL, NULL, NULL};
            prev = root;
            continue;
        }
        if(flag==LOAD_LEFT_SUBTREE && S.empty()) break;
        prev = S.top();
        S.pop();
        if(data == -2){
            prev->right = NULL;
            continue;
        }
        int JourneyCode;
        f>>JourneyCode;
        prev->right = new TreeNode{JourneyCode, data, NULL, NULL, prev};
        prev = prev->right;
    }
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
        cout << '('<< root->JourneyCode<<','<<root->price<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

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

