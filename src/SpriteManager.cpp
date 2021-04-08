#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "SpriteManager.h"

SpriteManager::SpriteManager(){
   frame = 0;
   animation = 0;
}

SpriteManager::SpriteManager(std::vector<Animation> anims){
   frame = 0;
   animation = 0;
   animations = anims;
}

int SpriteManager::addAnimation(int fc, int fd, SDL_Rect ff){
   Animation newAnimation = {fc, fd, ff};
   animations.push_back(newAnimation);
   return animations.size() - 1;
}

SDL_Rect SpriteManager::spriteUpdate(){
   frame = static_cast<int>(SDL_GetTicks() / animations[animation].frame_duration) % animations[animation].frame_count;
   frame_rect = animations[animation].first_frame;
   frame_rect.x += frame_rect.w * frame;
   return frame_rect;
}

void SpriteManager::setAnimation(int index){
   if (index != animation){
      animation = index;
      frame = 0;
   }
}

int SpriteManager::getAnimation(){
   return animation;
}
