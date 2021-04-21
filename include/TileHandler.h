/*
 * Class responsible for rendering elements from a tileset based on a map
 */

#ifndef TILE_HANDLER
#define TILE_HANDLER

#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <vector>
#include <fstream>

#include "GameObject.h"

#define TILE_W 16 //in pixels
#define TILE_H 16
#define LEVEL_W 60 //in tiles
#define LEVEL_H 15
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BACKGROUND_SCALAR 4 //scalar multiple of the background image to the destination
#define SCROLL_SPEED_INIT 2
#define TILE_SPRITES 7
#define SHEET_W 7 //tileset dimensions
#define SHEET_H 1


struct Tile {
   int type;
   int x;
   int y;
};

class TileHandler : public GameObject {

   public:
      
      TileHandler(SDL_Renderer* ren);

      bool init();
      void update();
      void render();

      bool checkTileCollision(SDL_Rect obj);

      SDL_Rect* getCamera();
      
   private:

      bool collide( SDL_Rect a, SDL_Rect b ); //returns true if collision occurs

      SDL_Rect src_R[7];
      struct Tile tiles[LEVEL_W * LEVEL_H];
      SDL_Rect camera;
};

#endif
