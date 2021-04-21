#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "Rocket.h"

#define PARTICLE_W 16
#define PARTICLE_H 16
#define SPRITE_SCALAR 4

Rocket::Rocket(SDL_Renderer* ren, SDL_Rect* cam, TileHandler* th) : GameObject(ren), partEm(ren, cam){
   camera = cam;
   tileHand = th;
}

bool Rocket::init(){
   //load sprite
   SDL_Surface* surface;
   surface = IMG_Load("./images/Rocket.png");
   if (!surface) {
      std::cout << "Error creating surface: " << SDL_GetError() << std::endl;
      return false;
   }
      
   obj_texture_p.push_back(SDL_CreateTextureFromSurface(obj_renderer_p,surface));
   SDL_FreeSurface(surface);
   if (!obj_texture_p[0]) {
      std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
      return false;
   }

   //initialize data
   alive = false;
   lifetime = 0;
   velocity = 0;
   SDL_QueryTexture(obj_texture_p[0], NULL, NULL, &dest_R.w, &dest_R.h);
   dest_R.w *= SPRITE_SCALAR;
   dest_R.h *= SPRITE_SCALAR;
   dest_R.x = 0;
   dest_R.y = 0;

   return true;
}

void Rocket::update(){
   if(alive){
      if (lifetime-- < 0){
         die();
      }
      else {
         dest_R.x += velocity;
         if (tileHand->checkTileCollision(dest_R) == true){
            die();
         }
      }
   }
   partEm.update();
}

void Rocket::render(){
   if(alive){
      dest_R.x -= camera->x; 
      dest_R.y -= camera->y;
      if (velocity >= 0)
         SDL_RenderCopy(obj_renderer_p,obj_texture_p[0], NULL, &dest_R); // render rocket
      else SDL_RenderCopyEx(obj_renderer_p,obj_texture_p[0], NULL, &dest_R, 0, NULL, SDL_FLIP_HORIZONTAL);
      partEm.render();
      dest_R.x += camera->x; //FIX THIS
      dest_R.y += camera->y;
   }
   partEm.render();
}

void Rocket::shoot(int x, int y, int vel, int life){
   alive = true;
   dest_R.x = x;
   dest_R.y = y;
   velocity = vel;
   lifetime = life;
}

bool Rocket::living(){
   return alive;
}

void Rocket::die(){
   alive = false;
   partEm.init(dest_R.x + (dest_R.w)/2 - (PARTICLE_W * SPRITE_SCALAR)/2, 
               dest_R.y + (dest_R.h)/2 - (PARTICLE_H * SPRITE_SCALAR)/2,
               PARTICLE_W * SPRITE_SCALAR, 
               PARTICLE_H * SPRITE_SCALAR);
}
