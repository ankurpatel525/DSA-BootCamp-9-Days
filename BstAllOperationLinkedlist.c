#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return createNode(key);
    
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }

    return node;
}

// Function to search for a key in the BST
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key) return root;

    if (key < root->key) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

// Function for in-order traversal of the BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Function to find the minimum value node in the BST
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a key from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: get the inorder successor
        struct Node* temp = minValueNode(root->right);
        root->key = temp->key; // Copy the inorder successor's content to this node
        root->right = deleteNode(root->right, temp->key); // Delete the inorder successor
    }
    return root;
}

// Function to get user input
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
                    printf("%d found in the BST\n", key);
                } else {
                    printf("%d not found in the BST\n", key);
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

// Main function to demonstrate the BST operations
int main() {
    struct Node* root = NULL;
    
    userInput(&root);

    return 0;
}
