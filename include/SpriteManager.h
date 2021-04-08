/*
 * Class responsible for handling sprite animation
 */

#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <vector>

struct Animation{
   int frame_count; //number of frames in the animation
   int frame_duration; //duration in milliseconds of each frame
   SDL_Rect first_frame; //dimensions and location of the first frame in the animation
};



class SpriteManager {
   public:
      SpriteManager();
      SpriteManager(std::vector<Animation> anims);
      int addAnimation(int fc, int fd, SDL_Rect ff); //returns index of added animation
      SDL_Rect spriteUpdate(); //updates the source rect to the correct animation frame
      void setAnimation(int index);
      int getAnimation();
  
   private:
      SDL_Rect frame_rect; //rect returned to the object for rendering
      int frame; //frame index
      int animation; //animation index
      std::vector<Animation> animations;
};

#endif
