#include "bstP.h"
// Constructor for one node
node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}
// start with an empty tree
BST::BST()
{
    root = nullptr;
}
// free all nodes in the tree
BST::~BST()
{
    clearTree(root);
}
//Recursively delete every node
void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}
// Insert into BST recursively
// Ignore duplicates to preserve BST property
void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }
    if(data == root->data)
        return;

    if(data < root->data)
        insertNode(root->leftChild, data);
    else 
        insertNode(root->rightChild, data);
}
//Search for value recursively
node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}
//Delete node from pointer BST
void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        // case 1: no left child
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        // case 2: no right child
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        //case 3: two children
        else {
            node* temp = root->rightChild;
            // find smallest value in right subtree
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
             //replace current value, then delete duplicate    
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}
// Preorder: center left right
void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}
// Inorder: left center right
void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}
// Postorder: left right center
void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}
//Recursively compute height
//Empty trr = -1, leaf = 0 
int BST::height(node* root)
{
    if(root == nullptr)
        return -1;
    int leftH = height(root->leftChild);
    int rightH = height(root->rightChild);
    if(leftH > rightH)
        return leftH + 1;
    else
        return rightH + 1;
}
//Recursively count total nodes
int BST::countNodes(node* root)
{
    if(root == nullptr)
        return 0;
    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);   
}
//Check whether tree is balanced
//Return Yes, Left-heavy, or Right-heavy
string BST::isBalanced(node* root)
{
    if(root == nullptr)
        return "Yes";
    int leftH = height(root->leftChild);
    int rightH = height(root->rightChild);
    if(leftH - rightH > 1)
        return "Left-heavy";
    if(rightH - leftH > 1)
        return "Right-heavy";
    string leftResult = isBalanced(root->leftChild);
    string rightResult = isBalanced(root->rightChild);
    if(leftResult != "Yes")
        return leftResult;
    if(rightResult != "Yes")
        return rightResult;
    return "Yes";
}
//Breadth-first traversal using custom queue
void BST:: BFS(node*root)
{
    if(root == nullptr)
        return;
    NodeQueue q;
    q.enqueue(root);
    while(!q.isEmpty())
    {
        node* temp = q.dequeue();
        cout << temp->data << " ";
        if(temp->leftChild != nullptr)
            q.enqueue(temp->leftChild);
        if(temp->rightChild != nullptr)
            q.enqueue(temp->rightChild);
    }
}
// to print tree sideways
void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->leftChild, space);
}