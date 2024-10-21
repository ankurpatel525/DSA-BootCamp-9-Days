#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the BST
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
struct Node* insert(struct Node* node, int data) {
    // If the tree is empty, return a new node
    if (node == NULL)
        return createNode(data);

    // Otherwise, recur down the tree
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    // Return the (unchanged) node pointer
    return node;
}

// Function to search for a value in the BST
struct Node* search(struct Node* root, int key) {
    // Base case: root is NULL or key is present at root
    if (root == NULL || root->data == key)
        return root;

    // Key is greater than root's data, search in right subtree
    if (key > root->data)
        return search(root->right, key);

    // Key is smaller than root's data, search in left subtree
    return search(root->left, key);
}

// Preorder traversal (Root -> Left -> Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);  // Visit root
        preorder(root->left);       // Traverse left subtree
        preorder(root->right);      // Traverse right subtree
    }
}

// Inorder traversal (Left -> Root -> Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);        // Traverse left subtree
        printf("%d ", root->data);  // Visit root
        inorder(root->right);       // Traverse right subtree
    }
}

// Postorder traversal (Left -> Right -> Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);      // Traverse left subtree
        postorder(root->right);     // Traverse right subtree
        printf("%d ", root->data);  // Visit root
    }
}

int main() {
    struct Node* root = NULL;
    int n, i, data, key;

    // Get the number of elements to insert into the BST
    printf("Enter the number of elements to insert in the BST: ");
    scanf("%d", &n);

    // Insert elements into the BST
    for (i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        root = insert(root, data);
    }

    // Perform and display different traversals
    printf("\nPreorder traversal: ");
    preorder(root);
    printf("\nInorder traversal: ");
    inorder(root);
    printf("\nPostorder traversal: ");
    postorder(root);

    // Ask user for the element to search
    printf("\n\nEnter the element to search for: ");
    scanf("%d", &key);

    // Search for the element in the BST
    struct Node* result = search(root, key);

    if (result != NULL)
        printf("Element %d found in the tree.\n", key);
    else
        printf("Element %d not found in the tree.\n", key);

    return 0;
}
