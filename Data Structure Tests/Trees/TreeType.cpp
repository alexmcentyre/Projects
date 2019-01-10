#include<iostream>
#include<math.h>
using namespace std;
#include "TreeType.h"


template<class ItemType>
struct TreeNode
{
  ItemType info;
  TreeNode<ItemType>* left;
  TreeNode<ItemType>* right;
};


template<class ItemType>
bool TreeType<ItemType>::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode<ItemType>* location;
  try
  {
    location = new TreeNode<ItemType>;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

template<class ItemType>
bool TreeType<ItemType>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

template<class ItemType>
int CountNodes(TreeNode<ItemType>* tree);

template<class ItemType>
int TreeType<ItemType>::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}

template<class ItemType>
int CountNodes(TreeNode<ItemType>* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template<class ItemType>
void Retrieve(TreeNode<ItemType>* tree, 
     ItemType& item, bool& found);

template<class ItemType>
ItemType TreeType<ItemType>::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

template<class ItemType>
void Retrieve(TreeNode<ItemType>* tree, 
     ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 

template<class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item);

template<class ItemType>
void TreeType<ItemType>::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

template<class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode<ItemType>;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
} 

template<class ItemType>
void DeleteNode(TreeNode<ItemType>*& tree);

template<class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item);

template<class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << "is not in tree\n";
}

template<class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

template<class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

template<class ItemType>
void DeleteNode(TreeNode<ItemType>*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode<ItemType>* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    //GetPredecessor(tree->left, data);
    tempPtr = PtrToSuccessor(tree);
    tree->info = tempPtr->info;
    data = tree->info;
    //Delete(tree->left, data);  // Delete predecessor node.
    Delete(tree->right, data);
  }
}

template<class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

template<class ItemType>
void PrintTree(TreeNode<ItemType>* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    PrintTree(tree->left);   // Print left subtree.
    cout << tree->info<<" ";
    PrintTree(tree->right);  // Print right subtree.
  }
}

template<class ItemType>
void TreeType<ItemType>::Print() const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(root);
}

template<class ItemType>
TreeType<ItemType>::TreeType()
{
  root = NULL;
}

template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree);

template<class ItemType>
TreeType<ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

template<class ItemType>
void TreeType<ItemType>::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}

template<class ItemType>
void CopyTree(TreeNode<ItemType>*& copy, 
	      const TreeNode<ItemType>* originalTree);

template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

template<class ItemType>
void TreeType<ItemType>::operator= 
     (const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  }

}

template<class ItemType>
void CopyTree(TreeNode<ItemType>*& copy, 
	      const TreeNode<ItemType>* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode<ItemType>;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}
// Function prototypes for auxiliary functions.

template<class ItemType>
void PreOrder(TreeNode<ItemType>*, QueType<ItemType>&);
// Enqueues tree items in preorder.

template<class ItemType>
void InOrder(TreeNode<ItemType>*, QueType<ItemType>&);
// Enqueues tree items in inorder.

template<class ItemType>
void PostOrder(TreeNode<ItemType>*, QueType<ItemType>&);
// Enqueues tree items in postorder.


template<class ItemType>
void TreeType<ItemType>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
  switch (order)
  { 
  case PRE_ORDER:    preQue.MakeEmpty();
		             PreOrder(root, preQue);
                     break;
  case IN_ORDER:     inQue.MakeEmpty();
					 InOrder(root, inQue);
                     break;
  case POST_ORDER:  postQue.MakeEmpty();
					PostOrder(root, postQue);
                     break;
  }
}

template<class ItemType>
void PreOrder(TreeNode<ItemType>* tree, 
	      QueType<ItemType>& preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL)
  {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}

template<class ItemType>
void InOrder(TreeNode<ItemType>* tree, 
	     QueType<ItemType>& inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL)
  {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}

template<class ItemType>
void PostOrder(TreeNode<ItemType>* tree, 
	       QueType<ItemType>& postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}


template<class ItemType>
ItemType TreeType<ItemType>::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER  : preQue.Dequeue(item);
                      if (preQue.IsEmpty())
                        finished = true;
                      break;
    case IN_ORDER   : inQue.Dequeue(item);
                      if (inQue.IsEmpty())
                        finished = true;
                      break;
    case  POST_ORDER: postQue.Dequeue(item);
                      if (postQue.IsEmpty())
                        finished = true;
                      break;
  }
  return item;
}


template<class ItemType>
void TreeType<ItemType>::LevelOrderPrint(){
  int level = 0;
  int count = 0;
  cout << endl;
  QueType<TreeNode<ItemType>*> holder;
  holder.Enqueue(this->root);
  while(!holder.IsEmpty()){
    TreeNode<ItemType>* temp;
    holder.Dequeue(temp);
    cout << temp->info << " ";
    count++;
    if(count == pow(2, level)){
      cout << endl;
      level++;
      count = 0;
    }//if
    if(temp->left != NULL){
      holder.Enqueue(temp->left);
    }//if
    if(temp->right != NULL){
      holder.Enqueue(temp->right);
    }//if
  }//while
  cout << endl;
}//LevelOrderPrint

template<class ItemType>
void Mirror(TreeNode<ItemType>*& mirror, const TreeNode<ItemType>* originalTree){
  if(originalTree == NULL){
    mirror = NULL;
  }//if
  else{
    mirror = new TreeNode<ItemType>;
    mirror->info = originalTree->info;
    Mirror(mirror->left, originalTree->right);
    Mirror(mirror->right, originalTree->left);
  }//else
}//Mirror

template<class ItemType>
TreeType<ItemType> TreeType<ItemType>::MirrorImage(){
  TreeType<ItemType> mirror;
  Mirror(mirror.root, this->root);
  return mirror;
}//MirrorImage

template<class ItemType>
void PrePrint(TreeNode<ItemType>* tree){
  if(tree != NULL){
    cout << tree->info << " ";
    PrePrint(tree->left);
    PrePrint(tree->right);
  }//if
}//PrePrint

template<class ItemType>
void PostPrint(TreeNode<ItemType>* tree){
  if(tree != NULL){
    PostPrint(tree->left);
    PostPrint(tree->right);
    cout << tree->info << " ";
  }//if
}//PostPrint

template<class ItemType>
void TreeType<ItemType>::PreOrderPrint(){
  PrePrint(this->root);
}//PreOrderPrint

template<class ItemType>
void TreeType<ItemType>::InOrderPrint(){
  PrintTree(this->root);
}//InOrderPrint

template<class ItemType>
void TreeType<ItemType>::PostOrderPrint(){
  PostPrint(this->root);
}//PostOrderPrint

template<class ItemType>
TreeNode<ItemType>* PtrToSuccessor(TreeNode<ItemType>*& tree){
  //TreeNode<ItemType>* temp;
  /*
  if(tree->right == NULL){
    TreeNode<ItemType>* tempRoot;
    TreeNode<ItemType>* temp;
    tempRoot = this->root;
    while(tempRoot != NULL){
      if(tree->info == tempRoot->info){
	break;
      }//if
      else if(tree->info > tempRoot->info){
	tempRoot = tempRoot->right;
      }//else if
      else{
	temp = tempRoot;
	tempRoot = tempRoot->left;
      }//else
    }//while
    return temp;
  }//if
  */

  //else{
  TreeNode<ItemType>* temp;
  temp = tree->right;
  while(temp->left != NULL){
    temp = temp->left;
  }//while
  return temp;
    //}//else
}//PtrToSuccessor

template<class ItemType>
void TreeType<ItemType>::Ancestors(ItemType value){
  QueType<TreeNode<ItemType>*> queue1;
  QueType<TreeNode<ItemType>*> queue2;
  QueType<TreeNode<ItemType>*> queue;
  TreeNode<ItemType>* tempRoot;
  tempRoot = this->root;

  while(true){
    while((tempRoot != NULL) && (tempRoot->info != value)){
      
      if(queue1.IsEmpty()){
	queue1.Enqueue(tempRoot);
	while(!queue2.IsEmpty()){
	  TreeNode<ItemType>* temp;
	  queue2.Dequeue(temp);
	  queue1.Enqueue(temp);
	}//while
      }//if
      else{
	queue2.Enqueue(tempRoot);
	while(!queue1.IsEmpty()){
	  TreeNode<ItemType>* temp;
	  queue1.Dequeue(temp);
	  queue2.Enqueue(temp);
	}//while
      }//else
      
      tempRoot = tempRoot->left;
    }//while
    if((tempRoot != NULL) && (tempRoot->info == value)){
      break;
    }//if
    if(!queue1.IsEmpty()){
      queue = queue1;
    }//if
    else{
      queue = queue2;
    }//else
    
    if(queue.getFront()->info->right == NULL){
      queue.Dequeue(tempRoot);
      while((!queue.IsEmpty()) && (queue.getFront()->info->right == tempRoot)){
	queue.Dequeue(tempRoot);
      }//while
    }//if

    if(queue.IsEmpty()){
      tempRoot = NULL;
    }//if
    else{
      tempRoot = queue.getFront()->info->right;
    }//else
  }//while
  while(!queue.IsEmpty()){
    TreeNode<ItemType>* print;
    queue.Dequeue(print);
    cout << print->info << " ";
  }//while
  queue1.MakeEmpty();
  queue2.MakeEmpty();
  queue.MakeEmpty();
}//Ancestors

template<class ItemType>
void TreeType<ItemType>::setRoot(TreeNode<ItemType>* r){
  root = r;
}//setRoot


template<class ItemType>
TreeNode<ItemType>* Maker(int& first, int& last, int list[]){
  if(first > last){
    return NULL;
  }//if
    int middle;
    middle = (first + last)/2;
    TreeNode<ItemType>* temp;
    temp->info = list[middle];
    //temp->left = Maker(first, middle + 1, list);
    //temp->right = Maker(middle + 1, last, list);
    return temp;
}//rMake

template<class ItemType>
void MakeTree(int list[], int length, TreeType<int>& tree){
  TreeType<int> temp;
  //temp.setRoot(Maker(0, length - 1, list));
  tree = temp;
}//MakeTree
