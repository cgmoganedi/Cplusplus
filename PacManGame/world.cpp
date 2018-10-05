#include "world.h"
#include "helpers.h"
#include "character.h"

#include <iomanip>
using namespace std;
/**
 * Constructs the World object loading a maze from the supplied file.
 * It should initialise the \ref{map} array with the relevant tiles as well
 * as the pacman and ghost objects.
 *
 * @param filename - File from which the maze should be read.
 * @param tileWidth - Width of each tile
 * @param tileHeight - Height of each tile
 */

World::World(string filename, int tileWidth, int tileHeight)
    : food(0), points(0), ready(true), pacman(0,0,Pacman),Rghost(0,0,GhostR),Yghost(0,0,GhostY)
{
    ifstream f(filename);
    if(!f.is_open())
        throw runtime_error("Couldn't open maze file " + filename);
    // Code to read in the file...
    else{
        vector<Tile>rowVec;
        string line;
        string tmp;
        f>>line>>tmp;
        rows = stoi(line);
        cols = stoi(tmp);
        getline(f,line);
        for (int row = 0; row < rows; row+=1 ){
            getline(f,line);
            for(int col = 0; col< cols; col+=1){
                switch(line[col]){
                case '0':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Blank));
                    pacman.x = col*tileWidth;
                    pacman.y = row*tileHeight;
                    break;
                case '1':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Blank));
                    Rghost.x = col*tileWidth;
                    Rghost.y = row*tileHeight;
                    break;
                case '2':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Blank));
                    Yghost.x = col*tileWidth;
                    Yghost.y = row*tileHeight;
                    break;
                case '3':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Blank));
                    break;
                case '4':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Blank));
                    break;
                case 'x':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Wall));
                    break;
                case '.':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Food));
                    ++food;
                    break;
                case ' ':
                    rowVec.push_back(makeTile(col*tileWidth,row*tileHeight,Blank));
                    break;
                }
            }
            maze.push_back(rowVec);
        }
    }
    f.close();
    char path[20]={};
    size_t i = 0, start = 0;
    while(MAZEFILENAME[i]){
        if(MAZEFILENAME[i] == '/'){
            start = i+1;
        }
        ++i;
    }
    size_t n = 0;
    for(size_t k = start;k<i; ++k){
        path[n] = MAZEFILENAME[k];
        ++n;
    }
    fstream mz(path);
    BFS w(mz);
    stack<Cell> s = w.FindPath();
    cout << w << endl;
    while(s.size()){
        cout<<s.top()<<endl;
        s.pop();
    }
}

BFS::BFS(istream &input)
{
    input>>numRows>>numCols;
    input.ignore();
    char line[numCols];
    while(input.getline(line,256)){
        _world.push_back(line);
    }
    for(int row = 0; row < numRows; ++row){
        auto str = _world[row];
        for(int col = 0; col<numCols; ++col){
            switch (str[col]){
            case '1':
                start.col = col;
                start.row = row;
                break;
            case '0':
                goal.col = col;
                goal.row = row;
                break;
            default:break;
            }
        }
    }
    _distance = new int*[numRows];
    for(int row = 0; row < numRows; ++row){
        _distance[row] = new int[numCols];
    }
    _parent = new Cell*[numRows];
    for(int row = 0; row < numRows; ++row){
        _parent[row] = new Cell[numCols];
    }
    _discovered = new bool*[numRows];
    for(int row = 0; row < numRows; ++row){
        _discovered[row] = new bool[numCols];
    }
    for(int row = 0; row<numRows; ++row){
        for(int col = 0; col<numCols; ++col){
            _discovered[row][col] = false;
            _distance[row][col] = -1;
            _parent[row][col] = {-1,-1};
        }
    }
}

BFS::~BFS()
{
    /*for(int i = 1; i<numRows; ++i){
        delete [] _discovered[i];
        delete [] _parent[i];
        delete [] _discovered[i];
    }
    delete [] _discovered;
    delete [] _parent;
    delete [] _discovered;*/
}

// 1 Line, return the relevant distance
int &BFS::distance(int r, int c)
{
    return _distance[r][c];
}

// 1 Line, return the relevant distance
int &BFS::distance(Cell c)
{
    return  distance(c.row,c.col);
}

// 1 Line, return the relevant parent
Cell &BFS::parent(int r, int c)
{
    return _parent[r][c];
}

// 1 Line, return the relevant parent
Cell &BFS::parent(Cell c)
{
    return _parent[c.row][c.col];
}

// 1 Line, return whether the cell is open or a wall.
bool BFS::isOpen(int r, int c)
{
    if(_world[r][c] == 'x'){
        return false;
    }
    return !_discovered[r][c];
}

// 1 Line, return whether the cell is open or a wall.
bool BFS::isOpen(Cell c)
{
    return isOpen(c.row,c.col);
}

// 1 Line, return whether the cell has been discovered
bool& BFS::discovered(int r, int c)
{
    return _discovered[r][c];
}

// 1 Line, return whether the cell has been discovered
bool& BFS::discovered(Cell c)
{
    return _discovered[c.row][c.col];
}

// Calculate the shortest path as per the algorithm in the pdf
stack<Cell> BFS::FindPath()
{
    queue<Cell>que;
    stack<Cell>staq;
    distance(start) = 0;
    parent(start) = {-2,-2};
    discovered(start) = true;
    que.push(start);
    while(que.size() && !discovered(goal)){
        const Cell cur = que.front();
        que.pop();
        //UP
        Cell tmp{cur.row -1,cur.col};
        if(isOpen(tmp)){
            distance(tmp) = distance(cur) + 1;
            parent(tmp) = cur;
            discovered(tmp) = true;
            que.push(tmp);
        }
        //DOWN
        tmp.row = cur.row +1;
        tmp.col = cur.col;
        if(isOpen(tmp)){
            distance(tmp) = distance(cur) +1;
            parent(tmp) = cur;
            discovered(tmp) = true;
            que.push(tmp);
        }
        //LEFT
        tmp.row = cur.row;
        tmp.col = cur.col -1;
        if(isOpen(tmp)){
            distance(tmp) = distance(cur) +1;
            discovered(tmp) = true;
            parent(tmp) = cur;
            que.push(tmp);
        }
        //RIGHT
        tmp.row = cur.row;
        tmp.col = cur.col +1;
        if(isOpen(tmp)){
            discovered(tmp) = true;
            distance(tmp) = distance(cur) +1;
            parent(tmp) = cur;
            que.push(tmp);
        }
    }
    if(!discovered(goal)){
        return staq;
    }
    else{
        Cell cur = goal;
        staq.push(cur);
        while(cur != start){
            staq.push(parent(cur));
            cur = parent(cur);
        }
        /*stack<Cell>s;
        while(staq.size()){
            s.push(staq.top());
            staq.pop();
        }
        return s;*/
        return staq;
    }

}

// Allows you to use: cout << curr_cell << endl;
ostream& operator<<(ostream& out, const Cell& c){
    return out << "[" << c.row << "," << c.col << "]";
}

// Allows you to use: cout << w << endl;
ostream& operator<<(ostream &os, BFS& w)
{
    os << "Source: " << w.start << ", Goal: " << w.goal << endl;
    os << "BFS [" << w.numRows << "x" << w.numCols << "]" << endl;
    for(const auto& r : w._world)
        os << r << endl;
    os << "Distance" << endl;
    for(int i = 0; i < w.numRows; ++i){
        for(int j = 0; j < w.numCols; ++j){
            os << setw(4) << w.distance(i, j);
        }
        os << endl;
    }
    os << "Parents" << endl;
    for(int i = 0; i < w.numRows; ++i){
        for(int j = 0; j < w.numCols; ++j){
            os << " " << w.parent(i, j);
        }
        os << endl;
    }
    return os;
}
/**
 * Renders the World to the ::sdlRenderer buffer.
 * It calls the respective render functions on each tile first.
 * Following this, it calls the pacman and ghost objects to render
 * them above the background.
 * @param frame [optional] An optional frame number to pass to the objects to handle animation.
 */
void World::render(Texture *t, int frame)
{
    for(int row = 0; row < rows; ++row){
        for (auto &item:maze[row]){
            item.render(t,frame);
        }
    }
    pacman.render(t,frame);
    Rghost.render(t,frame);
    Yghost.render(t,frame);
}

/**
 * This function is responsible for advancing the game state.
 * Pacman and the ghosts should be moved (if possible). If pacman is
 * captured by a ghost pacman.dead should be set to true. If pacman eats
 * a food pellet the relevant totals should be updated.
 *
 * @return The same value as World::ready, indicating whether the game is finished.
 */
bool World::UpdateWorld()
{
    const SDL_Rect pos = pacman.getNextPosition();
    bool notcollide = true;
    for(int row = 0; row < rows; row++){
        for(const auto &mazeTile: maze[row]){
            if(mazeTile.myType == Wall){
                const SDL_Rect tempTile{mazeTile.x, mazeTile.y, mazeTile.w*Tile::tileWidth, mazeTile.h*Tile::tileHeight};
                if (collision(pos,tempTile, 2, 2)){
                    notcollide = false;
                    row = rows;
                    break;
                }

            }
        }
    }
    if(notcollide){
        pacman.x = pos.x;
        pacman.y = pos.y;
        bool ate = false;

        for (int i = 0; i < rows; i++){
            for ( auto &mazeTile : maze[i]){
                if(mazeTile.myType == Food){
                    SDL_Rect tempTile{mazeTile.x, mazeTile.y, mazeTile.w*Tile::tileWidth, mazeTile.h*Tile::tileHeight};
                    if(collision(pos,tempTile, 7, 7)){
                        ate =  true;
                        mazeTile = makeTile(mazeTile.x, mazeTile.y, Blank);
                    }
                }
            }
        }

        if(ate){
            cout <<"Points increased to: "<<++points<<endl;
        }
    }
    else{

    }
    if (points == food ){
        return true;
    }
    return false;
}
