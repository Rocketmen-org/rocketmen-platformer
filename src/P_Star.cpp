#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <fstream>

#include "P_Star.h"
      
P_Star::P_Star(SDL_Renderer* ren, SDL_Rect* camera) : Particle(ren, camera){}


bool P_Star::init(){
   //load image
   //load sprite sheet
   SDL_Surface* surface;
   surface = IMG_Load("./images/Star.png");
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

   lifetime = 0;

   dest_R.x = 0;
   dest_R.y = 0;
   dest_R.w = 0;
   dest_R.h = 0;

   return true;
}

void P_Star::update(){
   if (0 < lifetime){
      dest_R.x += vel_x;
      dest_R.y += vel_y;

      int random = rand() %4;
      if (0 < dest_R.w)
         dest_R.w -= random;
      if (0 < dest_R.h)
         dest_R.h -= random;

      lifetime--;
   }
}

void P_Star::render(){
   if(0 < lifetime){
      dest_R.x -= camera->x;
      dest_R.y -= camera->y;
      SDL_RenderCopy(obj_renderer_p,obj_texture_p[0], NULL, &dest_R); // render player
      dest_R.x += camera->x; //FIX THIS
      dest_R.y += camera->y;
   }
}

