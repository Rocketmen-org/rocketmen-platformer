#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 

#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* ren){
   obj_renderer_p = ren;
}

void GameObject::quit(){
   if (!(obj_texture_p.size() != 0)){
      for(SDL_Texture* tex: obj_texture_p){
         SDL_DestroyTexture(tex);
      }
   }
}
