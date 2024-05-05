// The is an example to create a binray for key insertion and deleting.
// It is simple enough to store the beakpoint information.
// This code is generated by ChatGPT.
#include <stdio.h>
#include <stdlib.h>

#ifdef GDBSTUB
// do not check coverage here
// LCOV_EXCL_START
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new tree node
static TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the binary tree
void insert(TreeNode **root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }

    if (data < (*root)->data)
        insert(&((*root)->left), data);
    else
        insert(&((*root)->right), data);
}

// Function to find a node with given data in the binary tree
TreeNode* find(TreeNode *root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return find(root->left, data);
    else
        return find(root->right, data);
}

// Function to find the minimum value node in a binary tree
static TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the binary tree
TreeNode* delete(TreeNode *root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = delete(root->left, data);
    else if (data > root->data)
        root->right = delete(root->right, data);
    else {
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        TreeNode *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

/*
// Function to perform inorder traversal of the binary tree
void inorderTraversal(TreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main(void) {
    TreeNode *root = NULL;

    // Inserting elements into the binary tree
    insert(&root, 5);
    insert(&root, 3);
    insert(&root, 8);
    insert(&root, 1);
    insert(&root, 4);
    insert(&root, 7);
    insert(&root, 9);

    // Printing inorder traversal of the binary tree
    printf("Inorder traversal of the binary tree: ");
    inorderTraversal(root);
    printf("\n");

    // Finding an element in the binary tree
    int searchValue = 4;
    TreeNode *foundNode = find(root, searchValue);
    if (foundNode != NULL)
        printf("Element %d found in the binary tree\n", searchValue);
    else
        printf("Element %d not found in the binary tree\n", searchValue);

    // Deleting an element from the binary tree
    int deleteValue = 3;
    root = delete(root, deleteValue);

    // Printing inorder traversal of the binary tree after deletion
    printf("Inorder traversal of the binary tree after deletion: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
*/
// LCOV_EXCL_STOP
#endif // GDBSTUB

