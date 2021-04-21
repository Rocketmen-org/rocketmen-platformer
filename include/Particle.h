/*
 * Abstract Class representing a particle in a particle system
 */

#ifndef PARTICLE
#define PARTICLE

#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "GameObject.h"

class Particle : public GameObject {

   public:
      
      Particle(SDL_Renderer* ren, SDL_Rect* camera);

      virtual bool init() = 0;
      void setRect(int x, int y, int w, int h);
      void setV(int xv, int yv);
      void setLifetime(int t);
      void setCamera(SDL_Rect* cam);
      virtual void update() = 0;
      virtual void render() = 0;

   protected:
      //all particles have position, velocity, and lifetime
      SDL_Rect dest_R;
      
      int lifetime;
      int vel_x, vel_y;

      SDL_Rect* camera;
};

#endif
