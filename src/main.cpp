#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include "GameEngine.h"

const int GAME_SPEED = 60; //fps

int main(){ 
   
   GameEngine* ge = new GameEngine();
   int cycle_duration = 1000/GAME_SPEED + 1;
   int computation_time;
   int cycle_start;

   //Start up the game
   if(!ge->init()){
		perror("Game engine failed to init\n");
		return 1;
   }
	
   //While application is running
   while(ge->isRunning()){
      //get start time
      cycle_start = SDL_GetTicks();
      //Handle events on queue
      ge->handleEvents();
      //update game objects
      ge->updateMechanics();
      //render to screen
      ge->render();
      //get end time
      computation_time = SDL_GetTicks() - cycle_start;
      //delay until cycle duration has passed
      if(computation_time < cycle_duration)
         SDL_Delay(cycle_duration - computation_time);
   }
   ge->quit();
   return 0; 
}
