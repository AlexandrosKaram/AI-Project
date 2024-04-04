#pragma once

#include "Maze.h"
#include <vector>

// Define Node class
class Node {
public:
    Node* parent;
    Maze state;

    // Constructors
    Node() : parent(nullptr) {}
    Node(Node* parent, Maze state) : parent(parent), state(state) {}

    // Overload == operator
    bool operator==(const Node other) {
        return state == other.state;
    }
};