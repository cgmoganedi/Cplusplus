#include <iostream>
#include <thread>
#include <chrono>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "helpers.h"
#include "character.h"
#include "world.h"

using namespace std;

int main()
{
    // SpriteSheet Filename
    string spriteFilename = SPRITEFILENAME; // Leave this line
    Texture myTexture;
    myTexture.loadFile(spriteFilename, 20, 20);
    Tile::tileWidth = myTexture.tileWidth();
    Tile::tileHeight = myTexture.tileHeight();
    // Setup and Load Texture object here
    int frame = 0;
    //vector<Tile>testTiles = getTestTiles();
    //Character myPacman( 0, 0, Pacman);
    World myWorld(MAZEFILENAME, Tile::tileWidth, Tile::tileHeight);
    Tile gameOverTile = makeTile(Tile::tileWidth*myWorld.cols/2-50,Tile::tileHeight*myWorld.rows/2,GameOver);
	
    bool quit = false;
    bool over = false;
    myTexture.scaleGraphics(myWorld.rows, myWorld.cols);

    while(!quit){
        // Handle any SDL Events
        // Such as resize, clicking the close button,
        //  and process and key press events.
        SDL_Event e;
        while(SDL_PollEvent(&e)){
        	if(e.type == SDL_QUIT){
        		quit = true;
        	}
            myTexture.handle_event(e, myWorld.rows, myWorld.cols);
            myWorld.pacman.handle_event(e);
            myWorld.Rghost.handle_event(e);
            myWorld.Yghost.handle_event(e);
        }
        over = myWorld.UpdateWorld();

        // Update the Game State Information
        SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(myTexture.myWin.sdlRenderer);
        myWorld.render(&myTexture, frame);
        if(over){
            gameOverTile.render(&myTexture,frame);
        }
        SDL_RenderPresent(myTexture.myWin.sdlRenderer);
        ++frame;
        this_thread::sleep_for(chrono::milliseconds(75));
    }

    return 0;
}
