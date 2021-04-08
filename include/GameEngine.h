/*
 * Class responsible for initialization of the SDL library as well as
 * event handling, game mechanics, and rendering to the game window
 */

#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h>

class GameEngine {
   public:
      GameEngine();
      GameEngine(int sw, int sh, int gs); //screen width, screen height, game speed
      bool init();
      void handleEvents();
      void updateMechanics();
      void render();
      void quit();

      bool isRunning();

   private:
      SDL_Window* window_p;
      SDL_Renderer* renderer_p;
      SDL_Event input;

      int screen_width;
      int screen_height;
      int game_speed;

      bool game_is_running;

      Mix_Music* music; //note: create mixer class
      Mix_Chunk* jump_sfx;
};

#endif
