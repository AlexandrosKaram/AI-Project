#include "BFS.h"

int main() {
    // Create the maze
    Maze maze(3, 4);
    maze.grid[0][2] = CAR_WE;
    maze.grid[0][3] = ROCK;
    maze.grid[1][0] = ROCK;
    maze.grid[1][1] = CAR_WE;
    maze.grid[1][2] = CAR_NS;
    maze.grid[2][2] = ROCK;

    // Create the BFS object
    BFS bfs(maze);
    bfs.bfsSearch();

    std::cout << "Ok";
}