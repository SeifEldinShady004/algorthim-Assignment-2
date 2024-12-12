#include <iostream>
using namespace std;

template <typename t>
struct node {
    t data;
    string color;
    node *left, *right, *parent;

    node(t data){
        this->data = data;
        color = "RED";
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

template <typename t>
class RedBlackTree {
private:
    node<t>* root;
    node<t>* NIL;

    void leftRotate(node<t>* x) {
        node<t>* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(node<t>* x) {
        node<t>* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(node<t>* k) {
        while (k != root && k->parent->color == "RED") {
            if (k->parent == k->parent->parent->left) {
                node<t>* u = k->parent->parent->right;
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    rightRotate(k->parent->parent);
                }
            } else {
                node<t>* u = k->parent->parent->left;
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = "BLACK";
    }

    void fixDelete(node<t>* x) {
        while (x != root && x->color == "BLACK") {
            if (x == x->parent->left) {
                node<t>* sibling = x->parent->right;
                if (sibling->color == "RED") {
                    sibling->color = "BLACK";
                    x->parent->color = "RED";
                    leftRotate(x->parent);
                    sibling = x->parent->right;
                }
                if (sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                    sibling->color = "RED";
                    x = x->parent;
                } else {
                    if (sibling->right->color == "BLACK") {
                        sibling->left->color = "BLACK";
                        sibling->color = "RED";
                        rightRotate(sibling);
                        sibling = x->parent->right;
                    }
                    sibling->color = x->parent->color;
                    x->parent->color = "BLACK";
                    sibling->right->color = "BLACK";
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                node<t>* sibling = x->parent->left;
                if (sibling->color == "RED") {
                    sibling->color = "BLACK";
                    x->parent->color = "RED";
                    rightRotate(x->parent);
                    sibling = x->parent->left;
                }
                if (sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                    sibling->color = "RED";
                    x = x->parent;
                } else {
                    if (sibling->left->color == "BLACK") {
                        sibling->right->color = "BLACK";
                        sibling->color = "RED";
                        leftRotate(sibling);
                        sibling = x->parent->left;
                    }
                    sibling->color = x->parent->color;
                    x->parent->color = "BLACK";
                    sibling->left->color = "BLACK";
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = "BLACK";
    }

    void sortHelper(node<t>* node) {
        if (node != NIL) {
            sortHelper(node->left);
            cout << node->data << " ";
            sortHelper(node->right);
        }
    }

    node<t>* searchHelper(node<t>* node, t data) {
        if (node == NIL || node->data == data) {
            return node;
        } if (data < node->data) {
            return searchHelper(node->left, data);
        }
        return searchHelper(node->right, data);
    }

    void transplant(node<t>* u, node<t>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    node<t>* minimum(node<t>* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

public:
    RedBlackTree() {
        NIL = new node<t>(t());
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    void insert(t data) {
        node<t>* new_node = new node<t>(data);
        new_node->left = NIL;
        new_node->right = NIL;

        node<t>* parent = nullptr;
        node<t>* current = root;

        while (current != NIL) {
            parent = current;
            if (new_node->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        new_node->parent = parent;

        if (parent == nullptr) {
            root = new_node;
        } else if (new_node->data < parent->data) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        if (new_node->parent == nullptr) {
            new_node->color = "BLACK";
            return;
        }

        if (new_node->parent->parent == nullptr) {
            return;
        }

        fixInsert(new_node);
    }

    void deletenode(t data) {
        node<t>* z = search(data);
        if (z == NIL) return;

        node<t>* y = z;
        node<t>* x;
        string originalColor = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            originalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (originalColor == "BLACK") {
            fixDelete(x);
        }
    }

    void sort() {
        sortHelper(root);
        cout << endl;
    }

    node<t>* search(t data) {
        return searchHelper(root, data);
    }
};



//int main() {
//    RedBlackTree<string> rbtString;
//
//    rbtString.insert("apple");
//    rbtString.insert("banana");
//    rbtString.insert("grape");
//    rbtString.insert("cherry");
//    rbtString.insert("pear");
//    cout << "Tree after insertions (sorted): ";
//    rbtString.sort();
//
//
//    rbtString.deletenode("banana");
//    cout << "Tree after deleting 'banana' (sorted): ";
//    rbtString.sort();
//
//    rbtString.deletenode("pear");
//    cout << "Tree after deleting 'pear' (sorted): ";
//    rbtString.sort();
//
//    rbtString.deletenode("apple");
//    cout << "Tree after deleting 'apple' (sorted): ";
//    rbtString.sort();
//
//    rbtString.deletenode("orange");
//    cout << "Tree after attempting to delete non-existent node 'orange' (sorted): ";
//    rbtString.sort();
//
//    cout << "Tree properties validated manually by checking colors and structure." << endl;
//
//    return 0;
//}
