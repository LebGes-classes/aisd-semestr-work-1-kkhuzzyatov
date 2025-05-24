#include <iostream>
using namespace std;

struct Node {
    int data;
    string color;
    Node *left, *right, *parent;

    Node(int data)
        : data(data)
        , color("red")
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
    {
    }
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k)
    {
        while (k != root && k->parent->color == "red") {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right;
                if (u->color == "red") {
                    k->parent->color = "black";
                    u->color = "black";
                    k->parent->parent->color = "red";
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "black";
                    k->parent->parent->color = "red";
                    rightRotate(k->parent->parent);
                }
            }
            else {
                Node* u = k->parent->parent->left;
                if (u->color == "red") {
                    k->parent->color = "black";
                    u->color = "black";
                    k->parent->parent->color = "red";
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "black";
                    k->parent->parent->color = "red";
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = "black";
    }

    void inorderHelper(Node* node)
    {
        if (node != NIL) {
            inorderHelper(node->left);
            cout << node->data << " ";
            inorderHelper(node->right);
        }
    }

    Node* searchHelper(Node* node, int data)
    {
        if (node == NIL || data == node->data) {
            return node;
        }
        if (data < node->data) {
            return searchHelper(node->left, data);
        }
        return searchHelper(node->right, data);
    }

public:
    RedBlackTree()
    {
        NIL = new Node(0);
        NIL->color = "black";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    void insert(int data)
    {
        Node* new_node = new Node(data);
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        while (current != NIL) {
            parent = current;
            if (new_node->data < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        new_node->parent = parent;

        if (parent == nullptr) {
            root = new_node;
        }
        else if (new_node->data < parent->data) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        if (new_node->parent == nullptr) {
            new_node->color = "black";
            return;
        }

        if (new_node->parent->parent == nullptr) {
            return;
        }

        fixInsert(new_node);
    }

    void inorder() { inorderHelper(root); }

    Node* search(int data)
    {
        return searchHelper(root, data);
    }
};

int main()
{
    RedBlackTree rbt;

    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);

    cout << "Inorder printing:" << endl;
    rbt.inorder();

    cout << "\nSearch 15: "
         << (rbt.search(15) != rbt.search(0))
         << endl;
    cout << "Search 25: "
         << (rbt.search(25) != rbt.search(0))
         << endl;

    return 0;
}