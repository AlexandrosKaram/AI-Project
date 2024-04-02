#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

// Define constants for entities
const int EMPTY = 0;
const int ROCK = 1;
const int CAR_WE = 2;  // Car facing west-east
const int CAR_NS = 3;  // Car facing north-south

// Define struct to represent grid state
struct GridState {
    int grid[3][4];

    // Constructor to initialize grid
    GridState() : grid {
        {EMPTY, EMPTY, EMPTY, ROCK},
        {ROCK, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, ROCK, EMPTY}
    } {}
};


// Define BFS class
class BFS {
private:
    // Define struct to represent node in BFS tree
    class Node {
    public:
        GridState state;
        std::vector<Node*> children;
        Node* parent;

        Node() : parent(nullptr) {}

        Node(GridState state, Node* parent) : state(state), parent(parent) {}

        // Overload operator== for Node
        bool operator==(const Node& other) const {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (state.grid[i][j] != other.state.grid[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
    };

    // Queue that contains the nodes to be visited
    std::queue<Node*> nodeQueue;
    // Visited nodes
    std::vector<Node*> closed;

    // Initial positions of our cars
    Node* initialState;
    // Target
    Node* finalState;

public:
    BFS() {
        // Initialize initial state
        initialState = new Node(GridState(), nullptr);
        initialState->state.grid[0][2] = CAR_WE;
        initialState->state.grid[1][1] = CAR_WE;
        initialState->state.grid[1][2] = CAR_NS;
        nodeQueue.push(initialState);

        // Initialize final state
        finalState = new Node(GridState(), nullptr);
    }

    bool isInClosed(Node* node) {
        for (int i = 0; i < closed.size(); i++) {
            if (*(closed[i]) == *node) {
                return true;
            }
        }
        return false;
    }

    void calculateChildren(Node* node) {
        GridState state = node->state;
        for (int i = 0; i < 3 ; i++) {
            for (int j = 0; j < 4; j++) {
                // Movement for first type of car
                if (state.grid[i][j] == CAR_WE) {
                    // Check if car can move out of the grid
                    if (j == 0 || j == 3) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        Node* newChild = new Node(newState, node);

                        // Check that node hasn't been visited
                        if (!isInClosed(newChild)) {
                            node->children.push_back(newChild);
                        } else {
                            delete newChild;
                        }
                    }
                    // Movement inside the grid
                    else {
                        // Move west
                        if (state.grid[i][j - 1] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j - 1] = CAR_WE;
                            Node* newChild = new Node(newState, node);

                            if (!isInClosed(newChild)) {
                                node->children.push_back(newChild);
                            } else {
                                delete newChild;
                            }
                        }
                        // Move east
                        if (state.grid[i][j + 1] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j + 1] = CAR_WE;
                            Node* newChild = new Node(newState, node);

                            if (!isInClosed(newChild)) {
                                node->children.push_back(newChild);
                            } else {
                                delete newChild;
                            }
                        }
                    }
                }
                // Movement for second type of car
                else if (state.grid[i][j] == CAR_NS) {
                    // Check if car can move out of the grid
                    if (i == 0 || i == 2) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        Node* newChild = new Node(newState, node);

                        if (!isInClosed(newChild)) {
                            node->children.push_back(newChild);
                        } else {
                            delete newChild;
                        }
                    }
                    // Movement inside the grid
                    else {
                        // Move south
                        if (state.grid[i - 1][j] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i - 1][j] = CAR_NS;
                            Node* newChild = new Node(newState, node);

                            if (!isInClosed(newChild)) {
                                node->children.push_back(newChild);
                            } else {
                                delete newChild;
                            }
                        }
                        // Move north
                        if (state.grid[i + 1][j] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i + 1][j] = CAR_NS;
                            Node* newChild = new Node(newState, node);

                            if (!isInClosed(newChild)) {
                                node->children.push_back(newChild);
                            } else {
                                delete newChild;
                            }
                        }
                    }
                }
            }
        }
    }

    std::vector<Node*> getPath(Node* targetNode) {
        std::vector<Node*> path;
        Node* currentNode = targetNode;
        while (currentNode != nullptr) {
            path.push_back(currentNode);
            currentNode = currentNode->parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    void bfsSearch() {
        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();

            // Check if current node is the target node
            if (*current == *finalState) {
                // Target found
                std::vector<Node*> path = getPath(current);
                // Print the path along with move indices
                for (size_t i = 0; i < path.size(); ++i) {
                    std::cout << i + 1 << ". Move:" << std::endl;
                    for (int row = 0; row < 3; ++row) {
                        for (int col = 0; col < 4; ++col) {
                            std::cout << path[i]->state.grid[row][col] << " ";
                        }
                        std::cout << std::endl;
                    }
                    std::cout << std::endl;
                }
                return;
            }

            // Calculate children of current node
            calculateChildren(current);

            // Add current node to the closed list
            closed.push_back(current);

            // Add children to the queue
            for (Node* child : current->children) {
                nodeQueue.push(child);
            }
        }

        // Target not found
    }

    // Destructor to free allocated memory
    ~BFS() {
        delete initialState;
        for (Node* node : closed) {
            delete node;
        }
        closed.clear();
    }
};


#endif // BFS_H
