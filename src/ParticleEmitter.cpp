#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <math.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "ParticleEmitter.h"
#include "P_Star.h"

#define PARTICLE_VEL 6
#define PI 3.141592

      
template <class P>
ParticleEmitter<P>::ParticleEmitter(SDL_Renderer* ren, SDL_Rect* cam) : particles(MAX_PARTICLES, P(ren, cam)){
   for(int i = 0; i < MAX_PARTICLES; i++){
     particles[i].init();
   }
   
   srand(time(NULL));
}

template <class P>
ParticleEmitter<P>::~ParticleEmitter(){}

template class ParticleEmitter<P_Star>;
