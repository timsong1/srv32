// The is an example to create a red-black tree for key insertion and deleting.
// This code is generated by ChatGPT.

#ifdef GDBSTUB
// do not check coverage here
// LCOV_EXCL_START

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

static Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // New node is always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

static Node* insertBST(Node* root, Node* pt) {
    if (root == NULL) return pt;

    if (pt->data < root->data) {
        root->left = insertBST(root->left, pt);
        root->left->parent = root;
    } else if (pt->data > root->data) {
        root->right = insertBST(root->right, pt);
        root->right->parent = root;
    }

    return root;
}

static void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (x->right != NULL)
        x->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void rotateRight(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (x->left != NULL)
        x->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

static void fixViolation(Node **root, Node *pt) {
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;

    while ((pt != (*root)) && (pt->color != BLACK) && (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /* Case : A
           Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left) {
            Node *uncle_pt = grand_parent_pt->right;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                int temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        } else {  // Parent of pt is right child of Grand-parent of pt
            Node *uncle_pt = grand_parent_pt->left;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                int temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
    }
    (*root)->color = BLACK;
}

static Node* minValueNode(Node* node) {
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

static Node* deleteNodeBST(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNodeBST(root->left, data);
    else if (data > root->data)
        root->right = deleteNodeBST(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNodeBST(root->right, temp->data);
        }
    }

    return root;
}

void insertNode(Node **root, int data) {
    // Allocate memory for new node
    Node *pt = createNode(data);

    // Perform standard BST insert
    (*root) = insertBST((*root), pt);

    // Fix Red Black Tree violations
    fixViolation(root, pt);
}

void deleteNode(Node **root, int data) {
    // Perform standard BST delete
    (*root) = deleteNodeBST((*root), data);
}

Node* findNode(Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (root->data < data)
        return findNode(root->right, data);

    return findNode(root->left, data);
}

/*
void inorderTraversal(Node *root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main(void) {
    Node *root = NULL;
    insertNode(&root, 7);
    insertNode(&root, 3);
    insertNode(&root, 18);
    insertNode(&root, 10);
    insertNode(&root, 22);
    insertNode(&root, 8);
    insertNode(&root, 11);

    printf("Inorder Traversal of Red-Black Tree before deletion: ");
    inorderTraversal(root);
    printf("\n");

    deleteNode(&root, 10);

    printf("Inorder Traversal of Red-Black Tree after deletion: ");
    inorderTraversal(root);
    printf("\n");

    int key = 22;
    Node* foundNode = findNode(root, key);
    if (foundNode != NULL)
        printf("Node with key %d found in the Red-Black Tree.\n", key);
    else
        printf("Node with key %d not found in the Red-Black Tree.\n", key);

    key = 33;
    foundNode = findNode(root, key);
    if (foundNode != NULL)
        printf("Node with key %d found in the Red-Black Tree.\n", key);
    else
        printf("Node with key %d not found in the Red-Black Tree.\n", key);

    return 0;
}
*/
// LCOV_EXCL_STOP
#endif // GDBSTUB

