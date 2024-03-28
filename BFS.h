#include <queue>
#include <vector>

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

// Define struct to represent node in BFS tree
class Node {
public:
    GridState state;
    std::vector<Node> children;

    Node() {}

    Node(GridState state) {
        this->state = state;
    }
};

// Define BFS class
class BFS {
private:
    std::queue<Node> nodeQueue;
    std::vector<Node> visitedNodes;

    Node initialState;
    Node finalState;

public:
    BFS() {
        // Initialize initial state
        initialState.state.grid[0][2] = CAR_WE;
        initialState.state.grid[1][1] = CAR_WE;
        initialState.state.grid[1][2] = CAR_NS;
        nodeQueue.push(initialState);

    }

    void calculateChildren(Node &node) {
        GridState state = node.state;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (state.grid[i][j] == CAR_WE) {
                    if (j == 0 || j == 3) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        Node newChild(newState);
                        node.children.push_back(newChild);
                    } else if (j > 0 && state.grid[i][j-1] == EMPTY) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        newState.grid[i][j-1] = CAR_WE;
                        Node newChild(newState);
                        node.children.push_back(newChild);
                    } else if (j < 3 && state.grid[i][j+1] == EMPTY) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        newState.grid[i][j+1] = CAR_WE;
                        Node newChild(newState);
                        node.children.push_back(newChild);
                    }
                } else if (state.grid[i][j] == CAR_NS) {
                    if (i == 0 || i == 2) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        Node newChild(newState);
                        node.children.push_back(newChild);
                    } else if (i > 0 && state.grid[i-1][j] == EMPTY) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        newState.grid[i-1][j] = CAR_NS;
                        Node newChild(newState);
                        node.children.push_back(newChild);
                    } else if (i < 2 && state.grid[i+1][j] == EMPTY) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        newState.grid[i+1][j] = CAR_NS;
                        Node newChild(newState);
                        node.children.push_back(newChild);
                    }
                }
            }
        }
    }
};
