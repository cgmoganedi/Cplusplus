#ifndef WORLD_H
#define WORLD_H

/** \file world.h
 * \brief World class header file.
 */

#include "tile.h"
#include "character.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include <stack>
#include <queue>

using namespace std;

/** \brief Represents the entire state of the game.
 *
 * The class stores the maze, pacman, ghosts and is responsible for
 * calling the relevant \ref{render} functions on each object.
 */
class Cell{
public:
    int row;
    int col;

    bool operator==(const Cell& rhs){
        return row == rhs.row && col == rhs.col;
    }
    bool operator!=(const Cell& rhs){
        return !(*this == rhs);
    }
    friend ostream& operator<<(ostream& out, const Cell& c);
};

class World
{
public:
    int cols;                       ///< Number of columns in the maze (measured in tiles).
    int rows;                       ///< Number of rows in the maze (measured in tiles).
    int food;                       ///< The number of food pellets left in the maze.
    int points;                     ///< The number of food pellets eaten so far.

    bool ready;                     ///< Whether or not the game should continue running for another step.
    /** True: the game can advance another step. False: the game is finished.*/

    Character pacman, Rghost, Yghost;               ///< Character object representing pacman.

    std::vector<std::vector<Tile>> maze; ///< Stores maze Tile objects, used to store the background tile states.

    World(std::string filename, int tileWidth, int tileHeight);    ///< Constructor.

    void render(Texture *t, int frame = 0);     ///< Blit all tiles & characters to the ::sdlRenderer.

    bool UpdateWorld();                    ///< Advance the world 1 timestep.
};

class BFS
{
public:
    BFS(istream& input);
    ~BFS();

    int numRows, numCols;
    Cell start, goal;

    int& distance(int r, int c);
    int& distance(Cell c);

    Cell& parent(int r, int c);
    Cell& parent(Cell c);

    bool isOpen(int r, int c);
    bool isOpen(Cell c);

    bool& discovered(int r, int c);
    bool& discovered(Cell c);

    stack<Cell> FindPath();

    friend std::ostream& operator<<(std::ostream& os, BFS& w);

public:
    vector<string> _world;
    int **_distance = nullptr;
    Cell **_parent = nullptr;
    bool ** _discovered = nullptr;
};

#endif // WORLD_H
