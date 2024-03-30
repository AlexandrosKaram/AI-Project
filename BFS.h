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


// Define BFS class
class BFS {
private:
    // Define struct to represent node in BFS tree
    class Node {
    public:
        GridState state;
        std::vector<Node> children;

        Node() {}

        Node(GridState state) {
            this->state = state;
        }

        // Overload operator== for Node
        bool operator==(const Node& other) const {
            return state.grid == other.state.grid;
        }
    };

    // Queue that contains the nodes to be visited
    std::queue<Node> nodeQueue;
    // Visited nodes
    std::vector<Node> closed;

    // Initial positions of our cars
    Node initialState;
    // Target
    Node finalState;

public:
    BFS() {
        // Initialize initial state
        initialState.state.grid[0][2] = CAR_WE;
        initialState.state.grid[1][1] = CAR_WE;
        initialState.state.grid[1][2] = CAR_NS;
        nodeQueue.push(initialState);

    }

    bool isInClosed(Node node) {
        for (int i = 0 ; i < closed.size() ; i++) {
            if (closed[i] == node) {
                return true;
            }
        }
        return false;
    }

    void calculateChildren(Node &node) {
        GridState state = node.state;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                // Movement for first type of car
                if (state.grid[i][j] == CAR_WE) {
                    // Check if car can move out of the grid
                    if (j == 0 || j == 3) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        Node newChild(newState);
                        
                        // Check that node hasn't been visited
                        if (!isInClosed(newChild)) {
                            node.children.push_back(newChild);
                        }
                    // Movement inside the grid
                    } else {
                        // Move west
                        if (state.grid[i][j-1] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j-1] = CAR_WE;
                            Node newChild(newState);

                            if (!isInClosed(newChild)) {
                                node.children.push_back(newChild);
                            }
                        }
                        // Move east
                        if (state.grid[i][j+1] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j-1] = CAR_WE;
                            Node newChild(newState);

                            if (!isInClosed(newChild)) {
                                node.children.push_back(newChild);
                            }
                        }
                    }
                // Movement for second type of car
                } else if (state.grid[i][j] == CAR_NS) {
                    // Check if car can move out of the grid
                    if (i == 0 || i == 2) {
                        GridState newState = state;
                        newState.grid[i][j] = EMPTY;
                        Node newChild(newState);

                        if (!isInClosed(newChild)) {
                            node.children.push_back(newChild);
                        }
                    } else {
                        // Move south
                        if (state.grid[i-1][j] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i-1][j] = CAR_NS;
                            Node newChild(newState);

                            if (!isInClosed(newChild)) {
                                node.children.push_back(newChild);
                            }
                        }
                        // Move north
                        if (state.grid[i+1][j] == EMPTY) {
                            GridState newState = state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i+1][j] = CAR_NS;
                            Node newChild(newState);

                            if (!isInClosed(newChild)) {
                                node.children.push_back(newChild);
                            }
                        }
                    }
                }
            }
        }
    }

    void bfsSearch() {
        
    }
};
