/*
 * Abstract Class representing the manager for a particle system
 */

#ifndef PARTICLE_EMITTER
#define PARTICLE_EMITTER

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "Particle.h"
#include "P_Star.h"

//might make this a constructer argument later on...
#define MAX_PARTICLES 20

template <class P>
class ParticleEmitter{

   public:
      
      ParticleEmitter(SDL_Renderer* ren, SDL_Rect* cam);
      virtual ~ParticleEmitter();

      virtual void init(int start_x, int start_y, int start_w, int start_h) = 0; //different than most of the init functions in that it gets called whenever you reset the particles...
      virtual void update() = 0;
      virtual void render() = 0;

   protected:
      std::vector<P> particles;
};

#endif
