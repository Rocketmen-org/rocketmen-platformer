/*
 * Class representing a particle in a star burst effect
 */

#ifndef P_STAR
#define P_STAR

#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "Particle.h"

class P_Star : public Particle {

   public:
      
      P_Star(SDL_Renderer* ren, SDL_Rect* camera);

      bool init();
      void update();
      void render();
};

#endif

