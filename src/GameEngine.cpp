#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "GameEngine.h"
#include "Player.h"
#include "GameScreen.h"
#include "TileHandler.h"

#define FREQUENCY 44100
#define AUDIO_CHANNELS 2
#define SAMPLING_RATE 2048 //power of 2

//player object
Player* player; //RECONCILE THE WHOLE _P THING
GameScreen* background1;
GameScreen* background2;
GameScreen* background3;
GameScreen* background4;
TileHandler* tileHandler;

GameEngine::GameEngine(){
   screen_width = 640;
   screen_height = 480;
   game_speed = 60;
   game_is_running = true;
}

GameEngine::GameEngine(int sw, int sh, int gs){
   screen_width = sw;
   screen_height = sh;
   game_speed = gs;
   game_is_running = true;
}

bool GameEngine::init(){
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
      std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;	
      return false;
   }

   //Enable gpu_enhanced textures
   IMG_Init(IMG_INIT_PNG);

   //load mixer
   if(Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, SAMPLING_RATE) < 0)
      {
         printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
         return false;
      }
  
   window_p = SDL_CreateWindow("my_game", 
	 		        SDL_WINDOWPOS_CENTERED, 
	 		        SDL_WINDOWPOS_CENTERED, 
	 		        screen_width,
	       		        screen_height, 0);
   if (!window_p){
      std::cout << "Error creating window: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return false;
   }

   renderer_p = SDL_CreateRenderer(window_p,-1,0);
   if (!renderer_p){
      std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(window_p);
      SDL_Quit();
      return false;
   }

   //Intitalize game objects
   background1 = new GameScreen(renderer_p, "Clouds1.png");
   if(!background1->init()){
      quit(); 
	   std::cout << "Error creating GameScreen 1: " << SDL_GetError() << std::endl; 
      return false;
   }

   background2 = new GameScreen(renderer_p, "Mountains1.png");
   if(!background2->init()){
      quit(); 
	   std::cout << "Error creating GameScreen 2: " << SDL_GetError() << std::endl; 
      return false;
   }

   background3 = new GameScreen(renderer_p, "Mountains2.png");
   if(!background3->init()){
      quit(); 
	   std::cout << "Error creating GameScreen 3: " << SDL_GetError() << std::endl; 
      return false;
   }

   background4 = new GameScreen(renderer_p, "Clouds2.png");
   if(!background4->init()){
      quit(); 
	   std::cout << "Error creating GameScreen 4: " << SDL_GetError() << std::endl; 
      return false;
   }


   tileHandler = new TileHandler(renderer_p);
   if(!tileHandler->init()){
      quit();
	   std::cout << "Error creating TileHandler: " << SDL_GetError() << std::endl; 
      return false;
   }

   player = new Player(renderer_p, tileHandler->getCamera(), tileHandler);
   if(!player->init()){
      quit(); 
	   std::cout << "Error creating Player: " << SDL_GetError() << std::endl; 
      return false;
   }

   //player->setCamera(tileHandler->getCamera());
   background1->setCamera(tileHandler->getCamera());
   background2->setCamera(tileHandler->getCamera());
   background3->setCamera(tileHandler->getCamera());
   background4->setCamera(tileHandler->getCamera());


   background1->setScroll(1, 2, 1, 2);
   background2->setScroll(1, 4, 0, 1);
   background3->setScroll(1, 8, 0, 1);
   background4->setScroll(1, 6, 1, 4);

   //Load music
   music = Mix_LoadMUS( "music/Rocky Desert v02.wav");
   if(music == NULL )
   {
      printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
      return false;
   }
   //Load sound effects
   jump_sfx = Mix_LoadWAV( "sfx/Jump.wav" );
   if(jump_sfx == NULL)
   {
      printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
      return false;
   }

   //volume
   Mix_VolumeChunk(jump_sfx,(MIX_MAX_VOLUME/16));
   Mix_VolumeMusic(MIX_MAX_VOLUME/8);
   
  //play music
   Mix_PlayMusic(music, -1 );

   return true;
}

void GameEngine::handleEvents(){
   while( SDL_PollEvent(&input) != 0 ){
      //User requests quit
      if(input.type == SDL_QUIT)
         game_is_running = false;
      if(input.type == SDL_KEYDOWN && !input.key.repeat){
         switch(input.key.keysym.sym){
 	    case SDLK_LEFT:
	       player->walkLeft(true);
	       break;
	    case SDLK_RIGHT:
	       player->walkRight(true);
	       break;
	    case SDLK_SPACE:
	       if(player->jump()){
	          Mix_PlayChannel( -1, jump_sfx, 0 );
	       }
	       break;
	    case SDLK_d:
	       player->shoot(1);
	       break;
	    case SDLK_a:
	       player->shoot(-1);
	       break;
	 }
      }
           if(input.type == SDL_KEYUP){
         switch(input.key.keysym.sym){
	    case SDLK_LEFT:
	       player->walkLeft(false);
	       break;
	    case SDLK_RIGHT:
	       player->walkRight(false);
	       break;
	 }
      }
   }
}

void GameEngine::updateMechanics(){
   background1->update();
   background2->update();
   background3->update();
   background4->update();
   player->update();
   tileHandler->update(); 
}

void GameEngine::render(){
   SDL_RenderClear(renderer_p);

   //render game objects
   background4->render();
   background3->render();
   background2->render();
   background1->render();
   tileHandler->render();
   player->render(); //GENERALIZE

   SDL_RenderPresent(renderer_p);
}

void GameEngine::quit(){
   Mix_FreeMusic(music );
   
   SDL_DestroyRenderer(renderer_p);
   SDL_DestroyWindow(window_p);

//   Mix_Quit();
   IMG_Quit();
   SDL_Quit();
}

/********************************************/

bool GameEngine::isRunning(){
   return game_is_running;
}
