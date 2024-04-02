#pragma once

#include "Maze.h"
#include <vector>

class Node {
public:
    Maze state;
    Node* parent;

    // Constructors
    Node() : parent(nullptr) {}
    Node(Node* parent, Maze state) : parent(parent), state(state) {}

    // Overload == operator
    bool operator==(const Node other) {
        return state == other.state;
    }
};