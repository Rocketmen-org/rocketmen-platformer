/*
 * Class representing the background image
 */

#ifndef GAME_SCREEN
#define GAME_SCREEN

#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "GameObject.h"

class GameScreen : public GameObject {

   public:
      
      GameScreen(SDL_Renderer* ren, std::string filename);
 
      bool init();
      void update();
      void render();

      void setCamera(SDL_Rect* cam);
      void setScroll(int numerator, int denominator, int ssn, int ssd);
      
   private:
      std::string filepath;
      
      SDL_Rect src_R;
      SDL_Rect dest_R;
      SDL_Rect dest_R2;
      int image_w, image_h; //width and height of image
      bool looping; //determines whether background is currently looping
      int scroll_speed_numerator;
      int scroll_speed_denominator;
      int scroll_ratio_numerator;
      int scroll_ratio_denominator;
      int offset;

      SDL_Rect* camera;
      SDL_Rect cam; //a variable I use to set the camera to a default value because I'm too lazy to check for null
};

#endif
