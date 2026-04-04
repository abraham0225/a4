#include "bstA.h"

// Create array BST and mark all spots empty
BST::BST(int size)
{
    capacity = size;
    tree = new int[capacity];

    for(int i = 0; i < size; i++)
        tree[i] = INT_MIN;
}

// Free array memory
BST::~BST()
{
    delete[] tree;
}

// Return index of left child
int BST::leftChild(int index)
{
    return 2 * index + 1;
}

// Return index of right child
int BST::rightChild(int index)
{
    return 2 * index + 2;
}

// Return index of parent
int BST::parent(int index)
{
    return (index - 1) / 2;
}

// Iterative insert
// Ignore duplicates
void BST::insertI(int data)
{
    if(tree[0] == INT_MIN)
    {
        tree[0] = data;
        return;
    }

    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == data)
            return;

        if(data < tree[index])
        {
            if(leftChild(index) < capacity && tree[leftChild(index)] == INT_MIN)
            {
                tree[leftChild(index)] = data;
                return;
            }
            index = leftChild(index);
        }
        else
        {
            if(rightChild(index) < capacity && tree[rightChild(index)] == INT_MIN)
            {
                tree[rightChild(index)] = data;
                return;
            }
            index = rightChild(index);
        }
    }
}

// Recursive insert
void BST::insertR(int data)
{
    insertRhelper(0, data);
}

// Recursive helper for insert
// Ignore duplicates
void BST::insertRhelper(int index, int data)
{
    if(index >= capacity)
        return;

    if(tree[index] == INT_MIN)
    {
        tree[index] = data;
        return;
    }

    if(tree[index] == data)
        return;

    if(data < tree[index])
        insertRhelper(leftChild(index), data);
    else
        insertRhelper(rightChild(index), data);
}

// Iterative search
bool BST::searchI(int data)
{
    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == INT_MIN)
            return false;
        if(tree[index] == data)
            return true;

        if(data < tree[index])
            index = leftChild(index);
        else
            index = rightChild(index);
    }

    return false;
}

// Recursive search
bool BST::searchR(int data)
{
    return searchRhelper(0, data);
}

// Recursive search helper
bool BST::searchRhelper(int index, int data)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return false;

    if(tree[index] == data)
        return true;

    if(data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

// Preorder traversal: center left right
void BST::preorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}

// Inorder traversal: left center right
void BST::inorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));
}

// Postorder traversal: left right center
void BST::postorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    postorder(leftChild(index));
    postorder(rightChild(index));
    cout << tree[index] << " ";
}

// Print tree sideways
void BST::printTree(int index, int depth)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    printTree(rightChild(index), depth + 1);

    for(int i = 0; i < depth; i++)
        cout << "   ";
    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
}

// Public height function
int BST::height()
{
    return heightHelper(0);
}

// Recursively compute height
// Empty tree = -1, leaf = 0
int BST::heightHelper(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return -1;

    int leftH = heightHelper(leftChild(index));
    int rightH = heightHelper(rightChild(index));

    if(leftH > rightH)
        return leftH + 1;
    else
        return rightH + 1;
}

// Public node counter
int BST::countNodes()
{
    return countNodesHelper(0);
}

// Recursively count nodes
int BST::countNodesHelper(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return 0;

    return 1 + countNodesHelper(leftChild(index)) + countNodesHelper(rightChild(index));
}

// Check if whole tree is balanced
string BST::isBalanced()
{
    int leftH = heightHelper(1);
    int rightH = heightHelper(2);

    if(leftH - rightH > 1)
        return "Left-heavy";
    if(rightH - leftH > 1)
        return "Right-heavy";

    return "Yes";
}

// Find smallest value in a subtree
int BST::findMin(int index)
{
    while(leftChild(index) < capacity && tree[leftChild(index)] != INT_MIN)
        index = leftChild(index);

    return index;
}

// Clear an entire subtree recursively
void BST::clearSubtree(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    clearSubtree(leftChild(index));
    clearSubtree(rightChild(index));
    tree[index] = INT_MIN;
}

// Copy one subtree to another location
void BST::copySubtree(int fromIndex, int toIndex)
{
    if(toIndex >= capacity)
        return;

    if(fromIndex >= capacity || tree[fromIndex] == INT_MIN)
    {
        tree[toIndex] = INT_MIN;
        return;
    }

    tree[toIndex] = tree[fromIndex];
    copySubtree(leftChild(fromIndex), leftChild(toIndex));
    copySubtree(rightChild(fromIndex), rightChild(toIndex));
}

// Public delete function
void BST::deleteNode(int data)
{
    deleteHelper(0, data);
}

// Delete a node from array BST
void BST::deleteHelper(int index, int data)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    if(data < tree[index])
    {
        deleteHelper(leftChild(index), data);
    }
    else if(data > tree[index])
    {
        deleteHelper(rightChild(index), data);
    }
    else
    {
        int left = leftChild(index);
        int right = rightChild(index);

        bool hasLeft = (left < capacity && tree[left] != INT_MIN);
        bool hasRight = (right < capacity && tree[right] != INT_MIN);

        // Case 1: leaf
        if(!hasLeft && !hasRight)
        {
            tree[index] = INT_MIN;
        }
        // Case 2: only left child
        else if(hasLeft && !hasRight)
        {
            copySubtree(left, index);
            clearSubtree(left);
        }
        // Case 3: only right child
        else if(!hasLeft && hasRight)
        {
            copySubtree(right, index);
            clearSubtree(right);
        }
        // Case 4: two children
        else
        {
            int minIndex = findMin(right);
            int minValue = tree[minIndex];
            tree[index] = minValue;
            deleteHelper(right, minValue);
        }
    }
}

// Breadth-first traversal using custom queue
void BST::BFS()
{
    if(tree[0] == INT_MIN)
        return;

    IntQueue q;
    q.enqueue(0);

    while(!q.isEmpty())
    {
        int index = q.dequeue();
        cout << tree[index] << " ";

        if(leftChild(index) < capacity && tree[leftChild(index)] != INT_MIN)
            q.enqueue(leftChild(index));

        if(rightChild(index) < capacity && tree[rightChild(index)] != INT_MIN)
            q.enqueue(rightChild(index));
    }
}