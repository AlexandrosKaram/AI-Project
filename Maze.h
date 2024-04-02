#pragma once

#include <iostream>

const int EMPTY = 0;
const int ROCK = 1;
const int CAR_WE = 2;
const int CAR_NS = 3;

// Class to represent the state of the grid
class Maze {
public:
    int rows;
    int cols;
    int** grid;

    // Constructors
    Maze() : rows(0), cols(0), grid(nullptr) {}

    Maze(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;

        grid = new int*[rows];
        for (int i = 0 ; i < rows ; i++) {
            grid[i] = new int[cols];
            for (int j = 0 ; j < cols ; j++) {
                grid[i][j] = EMPTY;
            }
        }
    }

    Maze(const Maze& other) {
        rows = other.rows;
        cols = other.cols;

        grid = new int*[rows];
        for (int i = 0 ; i < rows ; i++) {
            grid[i] = new int[cols];
            for (int j = 0 ; j < cols ; j++) {
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    // Print the grid
    void printMaze() {
        for (int i = 0 ; i < rows ; i++) {
            for (int j = 0 ; j < cols ; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Overload == operator
    bool operator==(const Maze other) {
        if (rows == other.rows && cols == other.cols) {
            for (int i = 0 ; i < rows ; i++) {
                for (int j = 0 ; j < cols ; j++) {
                    if (grid[i][j] != other.grid[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
};
