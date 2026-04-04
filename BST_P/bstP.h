#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
//Node for pointer-based BST
struct node
{
    int data;
    node* leftChild;
    node* rightChild;

    node(int value);
};
// simple custom queue for BFS
class NodeQueue
{
    private:
        node* arr[100];
        int front;
        int rear;
    public:
        NodeQueue()
        {
            front = 0;
            rear = 0;
        }
        bool isEmpty()
        {
            return front == rear;
        }
        void enqueue(node* n)
        {
            arr[rear] = n;
            rear++;
        }

        node* dequeue()
        {
            node* temp = arr[front];
            front++;
            return temp;

        }
};

class BST
{
    public:
        node* root;

        BST();
        ~BST();
        void clearTree(node* node);

        void insertNode(node*& root, int data);
        node* searchNode(node*& root, int data);
        void deleteNode(node*& root, int data);

        void preorder(node* root);
        void inorder(node* root);
        void postorder(node* root);

        int height(node* root);
        int countNodes(node* root);
        string isBalanced(node* root);
        void BFS(node*root);

        void printTree(node* root, int space);
};

#endif