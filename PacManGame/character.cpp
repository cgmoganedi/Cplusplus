#include "character.h"
#include "tile.h"
#include "helpers.h"

/**
 * @brief Character::Character
 * @param myX X window co-ordinate.
 * @param myY Y window co-ordinate.
 * @param t Type of character.
 */
Character::Character(int myX, int myY, TileType t)
    :x(myX), y(myY), uTile(makeTile(x,y,t,Up)), dTile(makeTile(x,y,t,Down)), lTile(makeTile(x,y,t,Left)), rTile(makeTile(x,y,t,Right))
{

}

/**
 * @brief Character::render Call the relevant tiles render function based on current direction.
 * @param t Texture object for rendering.
 * @param frame Frame number to render.
 */
void Character::render(Texture *t, int frame)
{
    uTile.x = x;
    dTile.x = x;
    lTile.x = x;
    rTile.x = x;

    uTile.y = y;
    dTile.y = y;
    lTile.y = y;
    rTile.y = y;

    if (dir == Up){
        uTile.render(t,frame);
    }
    else if (dir == Down ){
        dTile.render(t,frame);
    }
    else if(dir == Left){
        lTile.render(t,frame);
    }
    else{
        rTile.render(t,frame);
    }
}
/**
 * @brief Character::getNextPosition Calculates the position of the character based on direction.
 * @return SDL_Rect of the position and dimensions (in pixels) of the character.
 */
SDL_Rect Character::getNextPosition()
{
    SDL_Rect position{x,y,Tile::tileWidth,Tile::tileHeight};
    switch (dir){
    case Up:
        position.y -= 5; //uTile.y - 5;
        //position.x = uTile.x;
        return position;
    case Down:
        position.y += 5;// dTile.y + 5;
        //position.x = dTile.x;
        return position;
    case Left:
        //position.y = lTile.y;
        position.x -= 5; //lTile.x - 5;
        return position;
    case Right:
        //position.y = rTile.y;
        position.x += 5;// rTile.x + 5;
        return position;

    }
}
/**
 * @brief Character::handle_event Handles the SDL Events for Arrow Keypresses
 * @param e SDL_Event to check.
 */
void Character::handle_event(const SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:    dir = Up; break;
            case SDLK_DOWN:  dir = Down; break;
            case SDLK_LEFT:  dir = Left; break;
            case SDLK_RIGHT: dir = Right; break;
        }
    }
}
