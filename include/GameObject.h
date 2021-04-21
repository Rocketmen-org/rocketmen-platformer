/*
 * Abstract Class responsible for initialization, storage and functionality of a single game object,
 * including event handling, mechanics, and rendering.
 * e.g. player, enemy, prop
 */
#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_image.h> 

class GameObject {
   public:
      GameObject(SDL_Renderer* ren);
      virtual ~GameObject();
      virtual bool init() = 0;
      virtual void update() = 0;
      virtual void render() = 0;
      void quit();


   protected:
      SDL_Renderer* obj_renderer_p;
      std::vector<SDL_Texture*> obj_texture_p;
};

#endif
