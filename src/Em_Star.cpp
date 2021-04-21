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

#include "Em_Star.h"

#define PARTICLE_VEL 6
#define PI 3.141592


      
Em_Star::Em_Star(SDL_Renderer* ren, SDL_Rect* cam) : ParticleEmitter<P_Star>(ren, cam){}
   

void Em_Star::init(int start_x, int start_y, int start_w, int start_h){
   for(int i = 0; i < MAX_PARTICLES; i++){
      particles[i].setRect(start_x, start_y, start_w, start_h);
      int theta = rand() % 360;
      particles[i].setV((int) (1 + rand() % PARTICLE_VEL) * cos(theta * PI/180), (int) (1 + rand() % PARTICLE_VEL) * sin(theta * PI/180));
      particles[i].setLifetime(5 + (rand() % 20));
   }
}

void Em_Star::update(){
   for(int i = 0; i < MAX_PARTICLES; i++){
      particles[i].update();
   }
}

void Em_Star::render(){
   for(int i = 0; i < MAX_PARTICLES; i++){
      particles[i].render();
   }
}


