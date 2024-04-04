#pragma once

#include "Maze.h"
#include "Node.h"
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// Define BFS class
class BFS {
private:
    Maze start;
    Maze goal;
    queue<Node*> queue;
    vector<Maze> explored;

public:
    BFS() {}
    BFS(Maze start) : start(start), goal(start) {
        Node* startNode = new Node(nullptr, start);
        queue.push(startNode);

        // Calculate target state
        for (int i = 0 ; i < goal.rows ; i++) {
            for (int j = 0 ; j < goal.cols ; j++) {
                if (goal.grid[i][j] == CAR_WE || goal.grid[i][j] == CAR_NS) {
                    goal.grid[i][j] = EMPTY;
                }
            }
        }
    }

    bool isInExplored(Maze state) {
        return find(explored.begin(), explored.end(), state) != explored.end();
    }

    void putChildrenInQueue(Node* node) {
        for (int i = 0 ; i < node->state.rows ; i++) {
            for (int j = 0 ; j < node->state.cols ; j++) {
                // Movement for first type of car
                if (node->state.grid[i][j] == CAR_WE) {
                    // Check if car can move directly out and reject other possible moves
                    if (j == 0 || j == node->state.cols - 1) {
                        Maze newState = node->state;
                        newState.grid[i][j] = EMPTY;
                        
                        if (!isInExplored(newState)) {
                            Node* childNode = new Node(node, *(new Maze(newState)));
                            queue.push(childNode);
                        }
                    }
                    // Movement inside the grid
                    else {
                        // Move west
                        if (node->state.grid[i][j - 1] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j - 1] = CAR_WE;

                            if (!isInExplored(newState)) {
                                Node* childNode = new Node(node, *(new Maze(newState)));
                                queue.push(childNode);
                            }
                        }
                        // Move east
                        if (node->state.grid[i][j + 1] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j + 1] = CAR_WE;
                            
                            if (!isInExplored(newState)) {
                                Node* childNode = new Node(node, *(new Maze(newState)));
                                queue.push(childNode);
                            }                            
                        }
                    }
                }
                // Movement for second type of car
                else if (node->state.grid[i][j] == CAR_NS) {
                    // Check if car can move directly out and reject other possible moves
                    if (i == 0 || i == node->state.rows - 1) {
                        Maze newState = node->state;
                        newState.grid[i][j] = EMPTY;

                        if (!isInExplored(newState)) {
                            Node* childNode = new Node(node, *(new Maze(newState)));
                            queue.push(childNode);
                        }
                    }
                    // Movement inside the grid
                    else {
                        // Move south
                        if (node->state.grid[i + 1][j] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i + 1][j] = CAR_NS;

                            if (!isInExplored(newState)) {
                                Node* childNode = new Node(node, *(new Maze(newState)));
                                queue.push(childNode);
                            }
                        }
                        // Move north
                        if (node->state.grid[i - 1][j] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i - 1][j] = CAR_NS;

                            if (!isInExplored(newState)) {
                                Node* childNode = new Node(node, *(new Maze(newState)));
                                queue.push(childNode);
                            }
                        }
                    }
                }
            }
        }
    }


    // Returns a sequence of nodes from the current one to the root
    vector<Node*> getPath(Node* node) {
        vector<Node*> path;
        Node* current = node;
        while (current != nullptr) {
            path.push_back(current);
            current = (*current).parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // Execute the algorithm
    void bfsSearch() {
        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();

            // Success actions
            if ((*current).state == goal) {
                vector<Node*> path = getPath(current);
                // Print path with indeces
                for (int i = 0 ; i < path.size() ; i++) {
                    if (i == 0) {
                        cout << "Initial state:" << endl;
                    } else {
                        cout << i << ".Move:" << endl;
                    }
                    path[i]->state.printMaze();
                    cout << endl;
                }
                // Print statistics
                cout << "Number of moves: " << path.size() - 1 << endl;
                cout << "Number of nodes explored: " << explored.size() << endl;
                cout << "Nodes left in the queue: " << queue.size() << endl;
                // Terminate the algorithm
                return;
            }

            // Failure actions
            putChildrenInQueue(current);
            explored.push_back(current->state);
        }
        // Target not found
    }
};