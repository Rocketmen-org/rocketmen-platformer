#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <fstream>

#include "Particle.h"
      
Particle::Particle(SDL_Renderer* ren, SDL_Rect* camera) : GameObject(ren){
   this->camera = camera;
}

void Particle::setRect(int x, int y, int w, int h){
   dest_R.x = x;
   dest_R.y = y;
   dest_R.w = w;
   dest_R.h = h;
}

void Particle::setV(int xv, int yv){
   vel_x = xv;
   vel_y = yv;
}

void Particle::setLifetime(int t){
   lifetime = t;
}

void Particle::setCamera(SDL_Rect* cam){
   camera = cam;
}
