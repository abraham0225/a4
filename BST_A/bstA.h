#ifndef BSTA_H
#define BSTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

// Simple custom queue for BFS
class IntQueue
{
    private:
        int arr[100];
        int front;
        int rear;

    public:
        IntQueue()
        {
            front = 0;
            rear = 0;
        }

        bool isEmpty()
        {
            return front == rear;
        }

        void enqueue(int x)
        {
            arr[rear] = x;
            rear++;
        }

        int dequeue()
        {
            int temp = arr[front];
            front++;
            return temp;
        }
};

class BST
{
    private:
        int* tree;
        int capacity;

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

        int heightHelper(int index);
        int countNodesHelper(int index);
        int findMin(int index);
        void clearSubtree(int index);
        void copySubtree(int fromIndex, int toIndex);
        void deleteHelper(int index, int data);

    public:
        BST(int size);
        ~BST();

        void insertI(int data);
        void insertR(int data);
        void insertRhelper(int index, int data);

        bool searchI(int data);
        bool searchR(int data);
        bool searchRhelper(int index, int data);

        void preorder(int index = 0);
        void inorder(int index = 0);
        void postorder(int index = 0);

        int height();
        int countNodes();
        string isBalanced();
        void deleteNode(int data);
        void BFS();

        void printTree(int index = 0, int depth = 0);
};

#endif