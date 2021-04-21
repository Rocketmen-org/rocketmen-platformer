#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>

#include "Player.h"

#define SPRITE_W 16
#define SPRITE_H 16
#define SPRITE_SCALAR 4
#define BACKGROUND_SCALAR 4
#define WALK_SPEED_INIT 1
#define WALK_ANIMATION_SPEED_INIT 3
#define WALK_DIRECTION_INIT 4 //not moving
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define LEVEL_W 60
#define LEVEL_H 15
#define TILE_H 16
#define TILE_W 16
#define IDLE 0
#define WALK_R 1
#define WALK_L 2
#define MAKE_ROCKET 3
#define JUMP 4
#define FALL 5
#define LAND 6
#define ROCKET_VEL 6
#define ROCKET_LIFE 50

      
Player::Player(SDL_Renderer* ren, SDL_Rect* cam, TileHandler* th) : GameObject(ren), partEm(ren, cam), rocket(ren, cam, th){
   camera = cam;
   tileHand = th;
}
 
bool Player::init(){
   //load sprite sheet
   
   SDL_Surface* surface;
   surface = IMG_Load("./images/Green_Rocket_Guy_Sidescroller-sheet.png");
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

   //animation data
   std::vector<Animation> anims = {{4, 400, {0,0,16,16}}, 
	                           {4, 200, {0,16,16,16}}, 
	                           {4, 200, {0,32,16,16}},
				   {4, 200, {0,48,16,16}}, 
	                           {1, 200, {0,64,16,16}},
	                           {1, 200, {16,64,16,16}}, 
	                           {2, 200, {32,64,16,16}}};
   spriteMan = SpriteManager(anims);
   spriteMan.setAnimation(IDLE);

   //rocket
   if(!rocket.init()){
      std::cout << "Error initiating rocket: " << SDL_GetError() << std::endl;
      return false;
   }

   
   //initialize data
   //SDL_QueryTexture(obj_texture_p[0], NULL, NULL, &image_w, &image_h);
   image_w = SPRITE_W;
   image_h = SPRITE_H;

   dest_R.x = SCREEN_WIDTH/2 - (image_w * SPRITE_SCALAR) / 2;
   dest_R.y = SCREEN_HEIGHT - 3 * TILE_H * SPRITE_SCALAR + camera->y;
   dest_R.w = image_w * SPRITE_SCALAR;
   dest_R.h = image_h * SPRITE_SCALAR;

   walk_speed = WALK_SPEED_INIT;
   walk_right = false;
   walk_left = false;

   altitude = 0;
   elevation = dest_R.y;
   jump_v = 0;

   return true;
}

void Player::update(){
   //update particles
   partEm.update();
   rocket.update();
   //handle movement
   //if (altitude == 0){
   right_v = walk_right;
   left_v = walk_left;
   //}
   
   int lateral_v = right_v - left_v;
   if (altitude == 0){
      if (lateral_v > 0){
         spriteMan.setAnimation(WALK_R);
      }
      else if (lateral_v < 0){
         spriteMan.setAnimation(WALK_L);
      }
      else if (lateral_v == 0){
         spriteMan.setAnimation(IDLE);
      }
   }

   int movement = (right_v - left_v) * walk_speed * SPRITE_SCALAR;
   dest_R.x += movement;
   if (tileHand->checkTileCollision(dest_R) == true){
      dest_R.x -= movement;
      movement = 0;
   }
   camera->x = dest_R.x + (image_w * SPRITE_SCALAR) / 2 - SCREEN_WIDTH / 2;

   //bound camera to level
   if (camera->x > LEVEL_W * TILE_W * BACKGROUND_SCALAR - (camera->w)){
      camera->x =  LEVEL_W * TILE_W * BACKGROUND_SCALAR - (camera->w);
   }
   if (camera->x < 0){
      camera->x = 0;
   }

   //bound sprite to level
   if (dest_R.x > LEVEL_W * TILE_W * BACKGROUND_SCALAR - (image_w * SPRITE_SCALAR)){
      dest_R.x -= movement;
      spriteMan.setAnimation(IDLE);
   }
   if (dest_R.y > LEVEL_W * TILE_H * BACKGROUND_SCALAR - (image_h * SPRITE_SCALAR)){
      dest_R.y = SCREEN_HEIGHT - (image_h * SPRITE_SCALAR);
   }
   if (dest_R.x < 0){
      dest_R.x -= movement;
      spriteMan.setAnimation(IDLE);
   }
   if (dest_R.y < 0){
      dest_R.y = 0;
   }

   //handle jump
   if (jump_v > 0){
      spriteMan.setAnimation(JUMP);
   }

   if (altitude == 0){
      dest_R.y++; //test if we're on ground
  
      if (tileHand->checkTileCollision(dest_R) == true){
         altitude = 0;
         jump_v = 0;
         dest_R.y--;
      }
      else altitude = 1;
   }
   if (altitude == 1) {
      altitude = 1;
      dest_R.y -= jump_v--; //move vertically
  
      if (tileHand->checkTileCollision(dest_R) == true){ //test if we've landed
         altitude = 0;
         dest_R.y +=  jump_v;
         while(!tileHand->checkTileCollision(dest_R)){ //really lame and expensive way to put us one pixel above the ground
            dest_R.y++;
         }
         dest_R.y--;
         jump_v = 0;
      }
      else {
         altitude = 1; //sanity check, more than anything
      }
   }

   //jump animation
   if (jump_v > 0){
      spriteMan.setAnimation(JUMP);
   }
   else if (jump_v < 0){
      spriteMan.setAnimation(FALL);
   }
}

void Player::render(){
   src_R = spriteMan.spriteUpdate();
   dest_R.x -= camera->x; 
   dest_R.y -= camera->y;
   SDL_RenderCopy(obj_renderer_p,obj_texture_p[0], &src_R, &dest_R); // render player
   partEm.render();
   rocket.render();
   dest_R.x += camera->x; //FIX THIS
   dest_R.y += camera->y;
}

void Player::walkRight(bool move){
   walk_right = move;
}

void Player::walkLeft(bool move){
   walk_left = move;
}

bool Player::jump(){
   if (altitude == 0){
      altitude = 1;
      jump_v = 16;
      //test particle emitter
      //int movement = (right_v - left_v) * walk_speed * SPRITE_SCALAR;
      //int particle_w = SPRITE_W * BACKGROUND_SCALAR;
      //int particle_h = SPRITE_H * BACKGROUND_SCALAR;
      //partEm.init((dest_R.x + (image_w * SPRITE_SCALAR)/2) - particle_w/2 + movement , dest_R.y + (image_w * SPRITE_SCALAR) - particle_w/2, particle_w, particle_h);
      return true;
   }
   return false;
}

bool Player::shoot(int direction){
   if (!rocket.living()){
      if(direction == 1){
         rocket.shoot(dest_R.x + (image_w * SPRITE_SCALAR) - (SPRITE_W * SPRITE_SCALAR)/2, 
                      dest_R.y + (image_h * SPRITE_SCALAR)/2 - (SPRITE_H * SPRITE_SCALAR)/2,
  		      ROCKET_VEL, ROCKET_LIFE);
         return true;
      }
      else if (direction == -1){
         rocket.shoot(dest_R.x - (SPRITE_W * SPRITE_SCALAR)/2, 
                      dest_R.y + (image_h * SPRITE_SCALAR)/2 - (SPRITE_H * SPRITE_SCALAR)/2,
  		      -ROCKET_VEL, ROCKET_LIFE);
         return true;
      }
   }
   return false;
}
