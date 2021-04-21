/*
 * Class representing rockets shot from the player
 */

#ifndef ROCKET
#define ROCKET

#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "GameObject.h"
#include "ParticleEmitter.h"
#include "P_Star.h"
#include "Em_Star.h"
#include "TileHandler.h"

class Rocket : public GameObject {

   public:
      
      Rocket(SDL_Renderer* ren, SDL_Rect* cam, TileHandler* th);
 
      bool init();
      void update();
      void render();

      void shoot(int x, int y, int vel, int life);
      bool living();
      
   private:
      
      void die();

      SDL_Rect dest_R;
      int velocity;
      int alive;
      int lifetime;

      SDL_Rect* camera;

      Em_Star partEm;

      TileHandler* tileHand;
};

#endif
