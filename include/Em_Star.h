/*
 * Class representing the particle emitter for a star burst effect
 */

#ifndef EM_STAR
#define EM_STAR

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "ParticleEmitter.h"
#include "P_Star.h"

#define MAX_PARTICLES 20

class Em_Star : public ParticleEmitter<P_Star>{

   public:
      
      Em_Star(SDL_Renderer* ren, SDL_Rect* cam);

      void init(int start_x, int start_y, int start_w, int start_h);
      void update();
      void render();
};

#endif

