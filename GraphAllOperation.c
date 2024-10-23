#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Function to create a new adjacency list node
struct Node* createNode(int vertex) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add an edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function for DFS traversal
void DFSUtil(int vertex, int visited[], struct Graph* graph) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;

        if (!visited[connectedVertex]) {
            DFSUtil(connectedVertex, visited, graph);
        }
        adjList = adjList->next;
    }
}

// Function to perform DFS traversal
void DFS(struct Graph* graph) {
    int* visited = malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFSUtil(i, visited, graph);
        }
    }
    printf("\n");
    free(visited);
}

// Function for BFS traversal
void BFS(struct Graph* graph, int startVertex) {
    int* visited = malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    struct Node** queue = malloc(graph->numVertices * sizeof(struct Node*));
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    printf("%d ", startVertex);
    queue[rear++] = graph->adjLists[startVertex];

    while (front < rear) {
        struct Node* current = queue[front++];
        while (current != NULL) {
            int connectedVertex = current->vertex;

            if (!visited[connectedVertex]) {
                printf("%d ", connectedVertex);
                visited[connectedVertex] = 1;
                queue[rear++] = graph->adjLists[connectedVertex];
            }
            current = current->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

// Function to free the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* adjList = graph->adjLists[i];
        while (adjList != NULL) {
            struct Node* temp = adjList;
            adjList = adjList->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
}

// Function to get user input and perform operations
void userInput() {
    int vertices, choice, src, dest;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    while (1) {
        printf("\n1. Add Edge\n2. DFS Traversal\n3. BFS Traversal\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertices: ");
                scanf("%d %d", &src, &dest);
                addEdge(graph, src, dest);
                printf("Edge added from %d to %d\n", src, dest);
                break;
            case 2:
                printf("DFS Traversal: ");
                DFS(graph);
                break;
            case 3:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &src);
                printf("BFS Traversal starting from vertex %d: ", src);
                BFS(graph, src);
                break;
            case 4:
                printf("Exiting...\n");
                freeGraph(graph);
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

// Main function
int main() {
    userInput();
    return 0;
}
