//~ mymap.h
// Seyfal Sultanov
// Mac OS Monterey 12.2.1 (21D62)
// VS Code Version: 1.72.2 (Universal)
// CS 251 - Data Structures
// Program 5 - mymap
// Prof. Adam Koehler

//--------------------------------------------------------------------------------

//! this program took a loooong time but I'm glad I got it to work
//! here are the directions as for the unique comments:

    //~ milestone identifier aka if the function was updated for the milestone
    //* important comment or description
    //! warning or error
    // TODO: something to do
    //^ something that is in progress OR line identifier for the helper function

//--------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <sstream>

using namespace std;

template <typename keyType, typename valueType>
class mymap
{
private:
    struct NODE
    {
        keyType key;     // used to build BST
        valueType value; // stored data for the map
        NODE *left;      // links to left child
        NODE *right;     // links to right child
        int nL;          // number of nodes in left subtree
        int nR;          // number of nodes in right subtree
        bool isThreaded;
    };
    NODE *root; // pointer to root node of the BST
    int size;   // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator
    {
    private:
        NODE *curr; // points to current in-order node for begin/end

    public:
        iterator(NODE *node)
        {
            curr = node;
        }

        keyType operator*()
        {
            return curr->key;
        }

        bool operator==(const iterator &rhs)
        {
            return curr == rhs.curr;
        }

        bool operator!=(const iterator &rhs)
        {
            return curr != rhs.curr;
        }

        bool isDefault()
        {
            return !curr;
        }

        // operator++:

        // This function should advance curr to the next in-order node.
        // O(logN)
        //~ milestone 5
        iterator operator++()
        {

            if (curr->isThreaded)
            {
                curr = curr->right;
            }
            else
            {
                if (curr->right != nullptr)
                    curr = curr->right;

                if (curr->left != nullptr)
                {
                    while (curr->left != nullptr)
                    {
                        curr = curr->left;
                    }
                }
            }

            return iterator(curr);
        }
    };

    //* helper function for destructor and copy constructor to delete all nodes
    //~ milestone 5
    // This function deletes nodes in the tree, beginning with the given node
    // and moving to the left subtree. If the node is not threaded, it moves
    // to the right subtree.
    void _clear(NODE *node)
    {

        // If node is null, return.
        if (node == nullptr)
        {
            return;
        }
        else
        {
            // Delete left subtree.
            _clear(node->left);
            if (!node->isThreaded)
            {
                // Delete right subtree.
                _clear(node->right);
            }
        }

        this->size--; // Decrement size.
        delete node;  // Delete node.
    }

    //* helper function to output the tree in order to a string
    //~ milestone 5
    // This function creates a string representation of a node in a trie.
    // The string representation is of the form
    //     < node->key, node->value >
    // where the node->key and node->value are the key and value of the
    // node, respectively. If the node has no value, then the value is
    // omitted from the string representation.
    // For example, if the node is a leaf node with key "hello" and value 42,
    // then the string representation is < hello, 42 >.
    // If the node has a value of 0, then the string representation is
    // just < hello >.
    // The string representation is appended to the output stream `out`.
    void _toString(NODE *node, stringstream &out) const
    {

        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {

            NODE *curr = node;
            _toString(node->left, out);
            out << "key: " << node->key << " value: " << node->value << endl;

            // if node is not threaded, clear the left subtree
            if (node->isThreaded)
            {
                curr = nullptr;
            }
            else
            {
                // if node is threaded, clear the right subtree
                _toString(node->right, out);
            }
        }
    }

    //* helper function for copy constructor to copy all nodes
    //~ milestone 5
    // Copy the nodes in a list, beginning with the given node and moving
    void _copy(NODE *other)
    {

        // if node doesnt point to anything, return
        if (other == nullptr)
        {
            return;
        }
        else
        {
            _copy(other->left);
            if (!other->isThreaded)
            {
                _copy(other->right);
            }
            this->put(other->key, other->value);
        }
    }

    //* helper function for vector constructor to populate the vector
    //~ milestone 5
    // Code that creates a vector of pairs from a binary search tree
    // This code is used to create a vector of pairs from a binary search tree
    // so that it can be sorted using the standard library sort function.
    // The variable name node is used to reference the root of the binary search tree.
    // The variable name v is used to reference the vector of pairs.
    void _toVector(NODE *node, vector<pair<keyType, valueType>> &v) const
    {

        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {
            NODE *curr = node;
            _toVector(node->left, v);
            v.push_back(make_pair(node->key, node->value));

            // if node is not threaded, clear the left subtree
            if (node->isThreaded)
            {
                curr = nullptr;
            }
            else
            {
                // if node is threaded, clear the right subtree
                _toVector(node->right, v);
            }
        }
    }

    //* helper function for checkBalance to output the tree in order to a string
    //~ milestone 5
    // This function checks that the AVL tree is balanced.
    // It does so by checking the difference in height between the left and right
    // subtrees of each node. The difference should never be more than 1.
    // The function takes a node as its argument and will recursively traverse
    // down the tree, checking each node. If the difference in height is greater
    // than 1, it will print an error message.
    void _checkBalance(NODE *node, stringstream &out)
    {

        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {
            NODE *curr = node;
            _checkBalance(node->left, out);
            out << "key: " << node->key << ", nL: " << node->nL << ", nR: " << node->nR << endl;

            // if node is not threaded, clear the left subtree
            if (node->isThreaded)
            {
                curr = nullptr;
            }
            else
            {
                // if node is threaded, clear the right subtree
                _checkBalance(node->right, out);
            }
        }
    }

    //* helper bool function that checks if the seesaw property is true
    //~ milestone 5
    // This function checks if a seesaw can be placed on a node.
    // It returns true if the seesaw can be placed, and false if it cannot.
    // In order to be placed, the seesaw must be on the ground and must not
    // be on a node that already has a seesaw on it.
    // This function is used by the placeSeesaw() function.
    // The node parameter is the node that the seesaw is being placed on.
    bool _checkSeesaw(NODE *node)
    {
        // get the max nL and nR
        int _max = max(node->nL, node->nR);
        int _min = min(node->nL, node->nR);
        _min = 2 * _min + 1;

        // if the max is less than or equal to the min, return true
        if (_max <= _min)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //* helper function to find nodes which make tree unbalanced by traversing the tree in order
    //~ milestone 5
    // This function searches the tree rooted at node for an unbalanced
    // node.
    // If it finds one, it returns a pointer to the unbalanced node.
    // If it does not find one, it returns NULL.
    NODE *_findUnbalanced(NODE *node)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return nullptr;
        }
        // if the only node is root, return
        else if (node->left == nullptr && node->right == nullptr)
        {
            return nullptr;
        }
        else
        {
            NODE *curr = node;
            NODE *left = _findUnbalanced(node->left);
            NODE *right = _findUnbalanced(node->right);

            // if the seesaw property is false, return the node
            if (!_checkSeesaw(node))
            {
                return node;
            }
            // if the left subtree is unbalanced, return the left node
            else if (left != nullptr)
            {
                return left;
            }
            // if the right subtree is unbalanced, return the right node
            else if (right != nullptr)
            {
                return right;
            }
            else
            {
                return nullptr;
            }
        }
    }

    //* helper function to find the parent of a node
    //~ milestone 5
    // Search for the parent of a given node in a tree.
    // node: the node to search for the parent of
    // child: the child of the node to search for
    NODE *_findParent(NODE *node, NODE *child)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return nullptr;
        }
        else
        {
            NODE *curr = node;
            NODE *left = _findParent(node->left, child);
            NODE *right = _findParent(node->right, child);

            // if the left child is the child, return the node
            if (node->left == child)
            {
                return node;
            }
            // if the right child is the child, return the node
            else if (node->right == child)
            {
                return node;
            }
            // if the left subtree is unbalanced, return the left node
            else if (left != nullptr)
            {
                return left;
            }
            // if the right subtree is unbalanced, return the right node
            else if (right != nullptr)
            {
                return right;
            }
            else
            {
                return nullptr;
            }
        }
    }

    //* helper function to balance the tree
    //~ milestone 5
    // This code recursively balances the tree. It first balances the left subtree
    // and then the right subtree. Then it checks the seesaw property and balances
    // the tree if the seesaw property is false.
    void _balance(NODE *node)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {
            NODE *curr = node;
            // recursively balance the left subtree
            _balance(node->left);
            // recursively balance the right subtree
            _balance(node->right);

            // if the seesaw property is not true, balance the tree
            if (!_checkSeesaw(node))
            {
                // if the left subtree is unbalanced, balance the left subtree
                if (node->nL > node->nR)
                {
                    _balanceLeft(node);
                }
                // if the right subtree is unbalanced, balance the right subtree
                else if (node->nR > node->nL)
                {
                    _balanceRight(node);
                }
            }
        }
    }

    //* helper function to balance the left subtree
    //~ milestone 5
    // This function balances the left subtree of a node.
    void _balanceLeft(NODE *node)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {
            // set a pointer to the node
            NODE *curr = node;
            // balance the left subtree
            _balanceLeft(node->left);
            // balance the right subtree
            _balanceLeft(node->right);

            // if the seesaw property is not true, balance the tree
            if (!_checkSeesaw(node))
            {
                // if the left subtree is unbalanced, balance the left subtree
                if (node->nL > node->nR)
                {
                    // if the left subtree is unbalanced, balance the left subtree
                    if (node->left->nL > node->left->nR)
                    {
                        _rotateRight(node);
                    }
                    // if the right subtree is unbalanced, balance the right subtree
                    else if (node->left->nR > node->left->nL)
                    {
                        _rotateLeft(node->left);
                        _rotateRight(node);
                    }
                }
            }
        }
    }

    //* helper function to balance the right subtree
    //~ milestone 5
    // This function balances the right subtree of a node.
    void _balanceRight(NODE *node)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        // else, node points to something
        else
        {
            // set a pointer to the node
            NODE *curr = node;
            // balance the right subtree, recursively
            _balanceRight(node->left);
            _balanceRight(node->right);

            // if the seesaw property is not true, balance the tree
            if (!_checkSeesaw(node))
            {
                // if the right subtree is unbalanced, balance the right subtree
                if (node->nR > node->nL)
                {
                    // if the left subtree is unbalanced, balance the left subtree
                    if (node->right->nL > node->right->nR)
                    {
                        _rotateRight(node->right);
                        _rotateLeft(node);
                    }
                    // if the right subtree is unbalanced, balance the right subtree
                    else if (node->right->nR > node->right->nL)
                    {
                        _rotateLeft(node);
                    }
                }
            }
        }
    }

    //* helper function to rotate the tree to the right
    //~ milestone 5
    // This function takes a node and rotates it to the right
    // It does this by making the left child of the node the new root
    // It then makes the right child of the new root the old root
    // If the node is the root, it rotates the root to the right
    // If the node is not the root, it rotates the node to the right
    void _rotateRight(NODE *node)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {
            NODE *curr = node;
            NODE *parent = _findParent(root, node);

            // if the node is the root, rotate the root to the right
            if (node == root)
            {
                root = node->left;
                node->left = root->right;
                root->right = node;
            }
            // if the node is not the root, rotate the node to the right
            else
            {
                // if the node is the left child, rotate the node to the right
                if (parent->left == node)
                {
                    parent->left = node->left;
                    node->left = parent->left->right;
                    parent->left->right = node;
                }
                // if the node is the right child, rotate the node to the right
                else if (parent->right == node)
                {
                    parent->right = node->left;
                    node->left = parent->right->right;
                    parent->right->right = node;
                }
            }
        }
    }

    //* helper function to rotate the tree to the left
    //~ milestone 5
    // Same as rotateRight, but rotates the tree to the left
    void _rotateLeft(NODE *node)
    {
        // if node doesnt point to anything, return
        if (node == nullptr)
        {
            return;
        }
        else
        {
            NODE *curr = node;
            NODE *parent = _findParent(root, node);

            // if the node is the root, rotate the root to the left
            if (node == root)
            {
                root = node->right;
                node->right = root->left;
                root->left = node;
            }
            // if the node is not the root, rotate the node to the left
            else
            {
                // if the node is the left child, rotate the node to the left
                if (parent->left == node)
                {
                    parent->left = node->right;
                    node->right = parent->left->left;
                    parent->left->left = node;
                }
                // if the node is the right child, rotate the node to the left
                else if (parent->right == node)
                {
                    parent->right = node->right;
                    node->right = parent->right->left;
                    parent->right->left = node;
                }
            }
        }
    }

public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    //~ milestone 5
    mymap()
    {
        root = nullptr; // set root to nullptr
        size = 0;       // set size to 0
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //~ milestone 3
    mymap(const mymap &other)
    {
        //* the initial idea to use = operator failed so some duplicate code from = operator is here
        this->root = new NODE();                         // create a new node
        this->root->key = other.root->key;               // set the key of the new node to the key of the other node
        this->root->value = other.root->value;           // set the value of the new node to the value of the other node
        this->root->nL = other.root->nL;                 // set the nL of the new node to the nL of the other node
        this->root->nR = other.root->nR;                 // set the nR of the new node to the nR of the other node
        this->root->isThreaded = other.root->isThreaded; // set the isThreaded of the new node to the isThreaded of the other node
        this->size = 1;                                  // set the size to 1 because the root is the only node
        //^ line 161
        _copy(other.root); // call the copy helper function
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //~ milestone 3
    mymap &operator=(const mymap &other)
    {

        if (this != &other) // if the other mymap is not the same as this mymap
        {
            this->clear();                                   // clear this mymap
            this->root = new NODE();                         // create a new node
            this->root->key = other.root->key;               // set the key of the new node to the key of the other node
            this->root->value = other.root->value;           // set the value of the new node to the value of the other node
            this->root->nL = other.root->nL;                 // set the nL of the new node to the nL of the other node
            this->root->nR = other.root->nR;                 // set the nR of the new node to the nR of the other node
            this->root->isThreaded = other.root->isThreaded; // set the isThreaded of the new node to the isThreaded of the other node
            this->size = 1;                                  // set the size to 1 because the root is the only node
            //^ line 161
            _copy(other.root); // call the copy helper function
        }
        return *this; // return this mymap
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    //~ milestone 5
    void clear()
    {
        // use helper function to delete all nodes
        //^ line 82
        _clear(root);   // first call the helper function to delete all nodes
        root = nullptr; // set root to nullptr
        size = 0;       // set size to 0
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    //~ milestone 5
    ~mymap()
    {
        clear(); // call the clear function
    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    //~ milestone 5
    void put(keyType key, valueType value)
    {

        //* almost the whole function is copied from the project 4 with minor changes

        // if the tree is empty, create a new node and make it the root
        if (root == nullptr)
        {
            NODE *newNode = new NODE;    // create a new node
            newNode->key = key;          // set the key of the new node to the key
            newNode->value = value;      // set the value of the new node to the value
            newNode->left = nullptr;     // set the left child of the new node to nullptr
            newNode->right = nullptr;    // set the right child of the new node to nullptr
            newNode->nL = 0;             // set the nL of the new node to 0
            newNode->nR = 0;             // set the nR of the new node to 0
            newNode->isThreaded = false; // set the isThreaded of the new node to false
            root = newNode;              // set the root to the new node
            size++;                      // increment size
            return;                      // return
        }

        // if the tree is not empty, find the node to insert the new node
        NODE *curr = root;      // set curr to the root
        NODE *prev = nullptr;   // set prev to nullptr
        while (curr != nullptr) // while curr is not nullptr
        {
            prev = curr;         // set prev to curr
            if (key < curr->key) // if the key is less than the key of curr
            {
                curr = curr->left; // set curr to the left child of curr
            }
            else if (key > curr->key) // if greater
            {
                //* line taken from the jumpstart
                curr = (curr->isThreaded) ? nullptr : curr->right; // Search Right
            }
            else // if equal
            {
                curr->value = value; // set the value of curr to the value
                return;              // return
            }
        }

        // create a new node and insert it
        NODE *newNode = new NODE;
        newNode->key = key;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->isThreaded = true;

        // if the new node is smaller than the previous node, insert it to the
        // left
        if (key < prev->key)
        {
            prev->left = newNode;
            newNode->right = prev;
            prev->nL++;
            size++;
            return;
        }

        // if the new node is larger than the previous node, insert it to the
        // right
        if (key > prev->key)
        {
            prev->right = newNode;
            prev->isThreaded = false;
            size++;
            return;
        }

        //* this part is new and implemented almost fully using the helper functions

        // check for the seesaw in the BST
        NODE *unbalanced = _findUnbalanced(root);

        // if the seesaw is found, re-balance the BST
        if (unbalanced != nullptr)
        {
            _balance(unbalanced); // call the balance helper function
        }
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //~ milestone 5
    bool contains(keyType key)
    {

        // if the tree is empty, return false
        if (root == nullptr)
        {
            return false;
        }

        // if the tree is not empty, find the node
        NODE *curr = root;

        while (curr != nullptr) // while curr is not nullptr
        {
            if (key < curr->key) // if the key is less than the key of curr
            {
                curr = curr->left; // set the curr to the left child of curr
            }
            else if (key > curr->key) // else if greater
            {
                //* implementation before i got stuck and started using the jumpstart, left there for reference
                // search the right sub-tree if the node is not threaded
                // if (curr -> isThreaded == false) {
                //     curr = curr -> right;
                // } else {
                //     curr = nullptr;
                // }
                //* the follwoing line was taken from https://docs.google.com/presentation/d/1L6gD4DqLEfNfQGnnK68ABrvuCXEjq6MY2F-j1dANI2M/preview?slide=id.gf91941521b_1_0
                curr = (curr->isThreaded) ? nullptr : curr->right; // Search Right
            }
            else // if equal
            {
                return true; // return true
            }
        }

        return false; // return false
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //~ milestone 5
    valueType get(keyType key)
    {
        //* interestingly get and contains are almost the same, except for the return value

        // if the tree is empty, return the default value
        if (root == nullptr)
        {
            return valueType();
        }

        // if the tree is not empty, find the node with the given key
        NODE *curr = root;
        while (curr != nullptr)
        {
            if (key < curr->key) // if the key is less than the key of curr
            {
                curr = curr->left; // set the curr to the left child of curr
            }
            else if (key > curr->key) // else if greater
            {
                //* implementation before i got stuck and started using the jumpstart, left there for reference
                // search the right sub-tree if the node is not threaded
                // if (curr -> isThreaded == false) {
                //     curr = curr -> right;
                // } else {
                //     curr = nullptr;
                // }
                //* the follwoing line was taken from https://docs.google.com/presentation/d/1L6gD4DqLEfNfQGnnK68ABrvuCXEjq6MY2F-j1dANI2M/preview?slide=id.gf91941521b_1_0
                curr = (curr->isThreaded) ? nullptr : curr->right; // Search Right
            }
            else // if equal
            {
                return curr->value; // return the value of curr
            }
        }

        // if the key is not found, return the default value
        return valueType();
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    //~ milestone 5
    valueType operator[](keyType key)
    {
        //* new idea, use get(), put() and contains() to implement this function ( old implementation is deleted )

        // if the key is not found, insert the new node
        if (!contains(key)) // if the key is not found
        {
            put(key, valueType()); // insert the new node
        }
        valueType value = get(key); // get the value of the node with the given key
        return value;               // return the value
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    //~ milestone 5
    int Size()
    {
        return size; // return the size of the tree, easy one
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //~ milestone 5
    iterator begin()
    {

        // if the tree is empty, return an iterator to the end
        if (root == nullptr)
        {
            // return iterator to the end
            return iterator(nullptr);
        }

        // if the tree is not empty, find the left-most node
        NODE *curr = root;
        while (curr->left != nullptr) // while the left child of curr is not nullptr
        {
            curr = curr->left; // set the curr to the left child of curr
        }

        return iterator(curr); // return an iterator to the left-most node
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    //
    // Time Complexity: O(1)
    //
    //~ milestone 5
    iterator end()
    {
        return iterator(nullptr); // return an iterator to the end
    }

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //~ milestone 5
    string toString()
    {
        //* toString, toVector and checkBalance are all very similar in implementation

        // if the tree is empty, return an empty string
        if (root == nullptr)
        {
            return ""; // return an empty string
        }

        // if the tree is not empty, traverse the tree in order
        NODE *curr = root; // set the curr to the root
        stringstream ss;   // create a stringstream
        // use helper function to traverse the tree in order and output
        //^ line 102
        _toString(curr, ss); // traverse the tree in order and output

        return ss.str();
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //~ milestone 5
    vector<pair<keyType, valueType>> toVector()
    {

        // if the tree is empty, return an empty vector
        if (root == nullptr)
        {
            return vector<pair<keyType, valueType>>(); // return an empty vector
        }

        // if the tree is not empty, traverse the tree in order
        NODE *curr = root;                  // set the curr to the root
        vector<pair<keyType, valueType>> v; // create a vector
        // use helper function to traverse the tree in order and output
        //^ line 241
        _toVector(curr, v);

        return v;
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //! milestone 5 ( should work, but i havent tested all the edge cases )
    string checkBalance()
    {

        // if the tree is empty, return an empty string
        if (root == nullptr)
        {
            return ""; // return an empty string
        }

        // if the tree is not empty, traverse the tree in pre-order
        NODE *curr = root; // set the curr to the root
        stringstream ss;   // create a stringstream
        // use helper function to traverse the tree in pre-order and output
        //^ line 282
        _checkBalance(curr, ss); // traverse the tree in pre-order

        return ss.str(); // return the string
    }
};
