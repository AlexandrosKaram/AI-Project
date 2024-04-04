#include "BFS.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    // Wrong number of arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <maze_number>\n";
        return 1;
    }

    // Get the choice of the maze
    int choice = std::stoi(argv[1]);

    // Run the BFS algorithm on the chosen maze
    switch (choice) {
        case 1: {
            // Create the first maze (3x4)
            Maze maze1(3, 4);
            maze1.grid[0][2] = CAR_WE;
            maze1.grid[0][3] = ROCK;
            maze1.grid[1][0] = ROCK;
            maze1.grid[1][1] = CAR_WE;
            maze1.grid[1][2] = CAR_NS;
            maze1.grid[2][2] = ROCK;

            // Run BFS on the first maze
            BFS bfs1(maze1);
            bfs1.bfsSearch();
            break;
        }
        case 2: {
            // Create a simpler example (2x2)
            Maze maze2(2, 2);
            maze2.grid[0][0] = CAR_WE;
            maze2.grid[0][1] = ROCK;
            maze2.grid[1][1] = CAR_NS;

            // Run BFS on the second maze
            BFS bfs2(maze2);
            bfs2.bfsSearch();
            break;
        }
        case 3: {
            // Create a more complex example (4x4)
            Maze maze3(4, 4);
            maze3.grid[0][0] = ROCK;
            maze3.grid[0][1] = CAR_WE;
            maze3.grid[0][2] = CAR_NS;
            maze3.grid[1][0] = CAR_WE;
            maze3.grid[1][1] = ROCK;
            maze3.grid[1][2] = ROCK;
            maze3.grid[1][3] = CAR_WE;
            maze3.grid[2][2] = ROCK;
            maze3.grid[3][2] = CAR_WE;

            // Run BFS on the third maze
            BFS bfs3(maze3);
            bfs3.bfsSearch();
            break;
        }
        default:
            std::cerr << "Invalid choice. Please choose a number between 1 and 4.\n";
            return 1;
    }

    return 0;
}
