#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <fstream>

#include "TileHandler.h"
      
TileHandler::TileHandler(SDL_Renderer* ren) : GameObject(ren){}
 
bool TileHandler::init(){
   //Load tileset
   SDL_Surface* surface;
   surface = IMG_Load("./images/Backgrounds/Background1-sheet.png");
   if (!surface) {
      std::cout << "Error creating surface: " << SDL_GetError() << std::endl;
      return false;
   }
 
   obj_texture_p.push_back(SDL_CreateTextureFromSurface(obj_renderer_p,surface));
   SDL_FreeSurface(surface);
   if (!obj_texture_p[0]) {
      std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
      return false;
   }
   
   //separate tilesheet
   for(int i = 0; i < SHEET_H; i++){
      for(int j = 0; j < SHEET_W; j++){
         src_R[(SHEET_W * i) + j] = {j * TILE_W, i * TILE_H, TILE_W, TILE_H};
      }
   }

   //load map
   std::ifstream map( "world/level.map" );
   //If the map couldn't be loaded
   if (map.fail()){
      printf( "Unable to load map file!\n" );
      return false;
   }

   //set tiles
   for(int i = 0; i < LEVEL_H; i++){
      for(int j = 0; j < LEVEL_W; j++){
         int type = -1;
         map >> type;
         //If the was a problem in reading the map
         if (map.fail()){
            //Stop loading map
            printf( "Error loading map: Unexpected end of file!\n" );
            return false;
         }
         //if the type is valid
	 if (type >= 0 && type < TILE_SPRITES){
            tiles[(LEVEL_W * i) + j] = {type, j * TILE_W, i * TILE_H};
	 }
	 else {
	    printf( "Error loading map: Invalid tile type at %d,%d!\n", j, i );
	 }
      }
   }
   //initialize camera
   camera = {0, LEVEL_H * TILE_H * BACKGROUND_SCALAR - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

   return true;
}

void TileHandler::update(){}

void TileHandler::render(){
   for(int i = 0; i < LEVEL_W * LEVEL_H; i++){
      SDL_Rect dest_R = {tiles[i].x * BACKGROUND_SCALAR,
	                 tiles[i].y * BACKGROUND_SCALAR,
	                 TILE_W * BACKGROUND_SCALAR, 
	                 TILE_H * BACKGROUND_SCALAR};
      if(collide(dest_R, camera)){
	 dest_R.x -= camera.x;
	 dest_R.y -= camera.y;
         SDL_RenderCopy(obj_renderer_p, obj_texture_p[0], &src_R[tiles[i].type], &dest_R);
      }
   }
}

SDL_Rect* TileHandler::getCamera(){
   return &camera;
}

bool TileHandler::checkTileCollision(SDL_Rect obj_R){
   for(int i = 0; i < LEVEL_W * LEVEL_H; i++){
      if (tiles[i].type >= 1 && tiles[i].type < 4){ //if it's a wall
         SDL_Rect tile_R = {tiles[i].x * BACKGROUND_SCALAR,
   	                    tiles[i].y * BACKGROUND_SCALAR,
	                    TILE_W * BACKGROUND_SCALAR, 
	                    TILE_H * BACKGROUND_SCALAR};
         if(collide(tile_R, obj_R)){
            return true;
         }
      }
   }
   return false;
}

bool TileHandler::collide( SDL_Rect a, SDL_Rect b ){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

