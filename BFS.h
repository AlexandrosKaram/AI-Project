#pragma once

#include "Maze.h"
#include "Node.h"
#include <queue>
#include <vector>
#include <algorithm>

// Define BFS class
class BFS {
private:
    Maze start;
    Maze goal;
    std::queue<Node*> queue;
    std::vector<Node*> explored;

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

    bool isAlreadyExplored(Node* node) {
        for (int i = 0 ; i < explored.size() ; i++) {
            if (*(node) == *(explored[i])) {
                return true;
            }
        }
        return false;
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
                        Node* childNode = new Node(node, *(new Maze(newState)));

                        if (!isAlreadyExplored(childNode)) {
                            queue.push(childNode);
                        } else {
                            delete childNode;
                        }
                    }
                    // Movement inside the grid
                    else {
                        // Move west
                        if (node->state.grid[i][j - 1] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j - 1] = CAR_WE;
                            Node* childNode = new Node(node, *(new Maze(newState)));

                            if (!isAlreadyExplored(childNode)) {
                                queue.push(childNode);
                            } else {
                                delete childNode;
                            }
                        }
                        // Move east
                        if (node->state.grid[i][j + 1] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i][j + 1] = CAR_WE;
                            Node* childNode = new Node(node, *(new Maze(newState)));

                            if (!isAlreadyExplored(childNode)) {
                                queue.push(childNode);
                            } else {
                                delete childNode;
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
                        Node* childNode = new Node(node, *(new Maze(newState)));

                        if (!isAlreadyExplored(childNode)) {
                            queue.push(childNode);
                        } else {
                            delete childNode;
                        }
                    }
                    // Movement inside the grid
                    else {
                        // Move south
                        if (node->state.grid[i + 1][j] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i + 1][j] = CAR_NS;
                            Node* childNode = new Node(node, *(new Maze(newState)));

                            if (!isAlreadyExplored(childNode)) {
                                queue.push(childNode);
                            } else {
                                delete childNode;
                            }
                        }
                        // Move north
                        if (node->state.grid[i - 1][j] == EMPTY) {
                            Maze newState = node->state;
                            newState.grid[i][j] = EMPTY;
                            newState.grid[i - 1][j] = CAR_NS;
                            Node* childNode = new Node(node, *(new Maze(newState)));

                            if (!isAlreadyExplored(childNode)) {
                                queue.push(childNode);
                            } else {
                                delete childNode;
                            }
                        }
                    }
                }
            }
        }
    }

    // Returns a sequence of nodes from the current one to the root
    std::vector<Node*> getPath(Node* node) {
        std::vector<Node*> path;
        Node* current = node;
        while (node != nullptr) {
            path.push_back(current);
            current = (*current).parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    // Execute the algorithm
    void bfsSearch() {
        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();

            // Success actions
            if ((*current).state == goal) {
                std::vector<Node*> path = getPath(current);
                // Print path with indeces
                for (int i = 0 ; i < path.size() ; i++) {
                    std::cout << i << ".Move:" << std::endl;
                    path[i]->state.printMaze();
                }
                // Terminate the algorithm
                return;
            }

            // Failure actions
            putChildrenInQueue(current);
            explored.push_back(current);

        }
        // Target not found
    }
};