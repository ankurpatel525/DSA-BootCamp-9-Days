#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the AVL tree
struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// Function to get the height of the node
int height(struct Node *N) {
    if (N == NULL) return 0;
    return N->height;
}

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // New node is initially added at leaf
    return newNode;
}

// Function to right rotate subtree rooted with y
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;
    x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;
    y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;

    // Return new root
    return y;
}

// Get balance factor of node N
int getBalance(struct Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

// Function to insert a key in the AVL tree
struct Node* insert(struct Node* node, int key) {
    // Perform the normal BST insertion
    if (node == NULL) return createNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplicates are not allowed
    }

    // Update the height of this ancestor node
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Get the balance factor of this ancestor node to check whether it became unbalanced
    int balance = getBalance(node);

    // If the node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function for in-order traversal of the AVL tree
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Function to search for a key in the AVL tree
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Function to find the minimum value node in the AVL tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a key from the AVL tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    // Perform standard BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key; // Copy the inorder successor's content to this node
            root->right = deleteNode(root->right, temp->key); // Delete the inorder successor
        }
    }

    // If the tree had only one node then return
    if (root == NULL) return root;

    // Update the height of the current node
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Get the balance factor of this node
    int balance = getBalance(root);

    // If the node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to get user input and perform operations
void userInput(struct Node** root) {
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Inorder Traversal\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                *root = insert(*root, key);
                printf("Inserted %d\n", key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(*root, key)) {
                    printf("%d found in the AVL tree\n", key);
                } else {
                    printf("%d not found in the AVL tree\n", key);
                }
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                *root = deleteNode(*root, key);
                printf("Deleted %d\n", key);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorder(*root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

// Main function to demonstrate the AVL tree operations
int main() {
    struct Node* root = NULL;
    
    userInput(&root);

    return 0;
}
