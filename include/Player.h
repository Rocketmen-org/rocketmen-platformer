/*
 * Class representing the 'player character'
 */

#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "GameObject.h"
#include "SpriteManager.h"
#include "ParticleEmitter.h"
#include "P_Star.h"
#include "Em_Star.h"
#include "TileHandler.h"
#include "Rocket.h"

class Player : public GameObject {

   public:
      
      Player(SDL_Renderer* ren, SDL_Rect* cam, TileHandler* th);
 
      bool init();
      void update();
      void render();

      void walkRight(bool move);
      void walkLeft(bool move);

      bool jump();

      bool shoot(int direction);
      
   private:
      SDL_Rect dest_R;
      SDL_Rect src_R;
      int image_w, image_h; //width and height of image
      int walk_speed;
      
      bool walk_right; //inputs
      bool walk_left;

      bool right_v; //actual movement values
      bool left_v;

      int altitude; //height off the ground
      int elevation; //height of the ground
      int jump_v; //jump velocity

      SpriteManager spriteMan;
      SDL_Rect* camera;

      Em_Star partEm;

      TileHandler* tileHand;

      Rocket rocket;
};

#endif
