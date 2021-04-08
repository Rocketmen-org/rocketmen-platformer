#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "GameScreen.h"

#define START_X 0
#define START_Y 0
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BACKGROUND_SCALAR 2 //scalar multiple of the background image to the destination
#define SCROLL_SPEED_INIT 0


      
GameScreen::GameScreen(SDL_Renderer* ren, std::string filename) : GameObject(ren){
   filepath = "./images/Backgrounds/" + filename;
}
 
bool GameScreen::init(){
   //load image
   SDL_Surface* surface;
   surface = IMG_Load(filepath.c_str());
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

   SDL_QueryTexture(obj_texture_p[0], NULL, NULL, &image_w, &image_h);

   //starting screen position
   src_R.x = 0;
   src_R.y = 0;
   src_R.w = image_w;
   src_R.h = image_h;

   //fullscreen image destination
   dest_R.x = -START_X * BACKGROUND_SCALAR;
   dest_R.y = SCREEN_HEIGHT - (image_h -START_Y) * BACKGROUND_SCALAR;
   dest_R.w = image_w * BACKGROUND_SCALAR;
   dest_R.h = image_h * BACKGROUND_SCALAR;

    //for background loop
   dest_R2.x = (-START_X + image_w) * BACKGROUND_SCALAR;
   dest_R2.y = SCREEN_HEIGHT - (image_h -START_Y) * BACKGROUND_SCALAR;
   dest_R2.w = image_w * BACKGROUND_SCALAR;
   dest_R2.h = image_h * BACKGROUND_SCALAR;

   scroll_speed_numerator = SCROLL_SPEED_INIT;
   scroll_speed_denominator = 1;
   offset = 0;

   //camera
   cam = {0, 0, 0, 0};
   camera = &cam;

   scroll_ratio_numerator = 1;
   scroll_ratio_denominator = 2;

   return true;
}

void GameScreen::update(){
   //scrolling right
   dest_R.x = -((camera->x * scroll_ratio_numerator / scroll_ratio_denominator) % (image_w * BACKGROUND_SCALAR));
   offset += scroll_speed_numerator;
   offset %= (image_w * BACKGROUND_SCALAR) * scroll_speed_denominator;
   dest_R.x += offset / scroll_speed_denominator;
      /*
       * when the screen reaches the end of the image, a second instance of the source image
       * is copied adjacently such that the background 'loops'
       *
       * NOTE: background image width * BACKGROUND_SCALAR must exceed SCREEN_WIDTH &
       *       background image height * BACKGROUND_SCALAR must exceed SCREEN_HEIGHT
       * NOTE: src rects are automatically cut off by the edges of the source image when used 
       *       for RenderCopy, while dest rects may exceed the bounds of the game screen
       */
      
   if (dest_R.x < -(image_w * BACKGROUND_SCALAR) + SCREEN_WIDTH){
      looping = true;
      dest_R2.x = dest_R.x + (image_w * BACKGROUND_SCALAR);
   }
   else {
      looping = false;
   }
   
   if (dest_R.x < -(image_w * BACKGROUND_SCALAR)){
      dest_R.x = 0 - (-(image_w * BACKGROUND_SCALAR) - dest_R.x) ;
   }
   else if (dest_R.x > 0){
      looping = true;
      dest_R.x = -(image_w * BACKGROUND_SCALAR) + dest_R.x;
      dest_R2.x = dest_R.x + (image_w * BACKGROUND_SCALAR);
   }
}

void GameScreen::render(){
   SDL_RenderCopy(obj_renderer_p, obj_texture_p[0], &src_R, &dest_R);
   if (looping)
      SDL_RenderCopy(obj_renderer_p ,obj_texture_p[0], &src_R, &dest_R2);
}

void GameScreen::setCamera(SDL_Rect* cam){
   camera = cam;
}

void GameScreen::setScroll(int numerator, int denominator, int ssn, int ssd){
   scroll_ratio_numerator = numerator; //ratio of motion to camera movement for parallax
   scroll_ratio_denominator = denominator;
   scroll_speed_numerator = ssn; //rate that the background always moves
   scroll_speed_denominator = ssd;
}
