#include "bstP.h"

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }

    if(data < root->data)
        insertNode(root->leftChild, data);
    else 
        insertNode(root->rightChild, data);
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}


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