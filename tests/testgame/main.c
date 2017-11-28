#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <client/backfire.h>

#include "menustate.h"
#include "level1.h"
#include "main.h"

Object *testthing1_object;

void eventcallback(SDL_Event *event)
{
  //printf("Yoyo comming from the events\n");
  switch(event->type)
  {
    case SDL_QUIT:
      gSettings.canExit = 1;
    break;
    //==========================================================================
    case SDL_KEYDOWN:
      switch (event->key.keysym.sym)
      {
        case SDLK_w:
          gSettings.cameraAngle += 2.3f;
        break;
        case SDLK_a:
          testthing1_object->collision.x-= 6.5f;
        break;
        case SDLK_s:
          testthing1_object->rotation += 3.30;
          testthing1_object->collision.y+= 6.5f;
        break;
        case SDLK_d:
          testthing1_object->collision.x+= 6.5f;
        break;

        //============================DEBUG=====================================

        case SDLK_KP_PLUS:
          gSettings.state++;
          printf("Changin up scene to %lu\n", gSettings.state);
        break;
        case SDLK_KP_MINUS:
          gSettings.state--;
          printf("Changin down scene to %lu\n", gSettings.state);
        break;
      }
    break;
    //==========================================================================
    case SDL_KEYUP:
      switch (event->key.keysym.sym)
      {
        case SDLK_w:

        break;
        case SDLK_a:

        break;
        case SDLK_s:

        break;
        case SDLK_d:

        break;
      }
    break;

  }

}
void logiccallback()
{
  //printf("heyhey comming from the logic\n");
  //testthing1_object->rotation += 3.0f;
}
/*void postrendercallback() Maybe. Not going to be very fun.
{

}*/

void init()
{
  Backfire_Init();
  Backfire_AddEventCB(eventcallback);
  Backfire_AddLogicCB(logiccallback);
  Backfire_AddState(menuinit, menuevent, menulogic, menudestroy);
  Backfire_AddState(level1init, level1event, level1logic, level1destroy);

  //gSettings.state = 4;

  Backfire_CreateMainWindowOpenGL("test game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720);
  //================================TEST========================================


  unsigned long testthing1;
  Backfire_SceneAddObject(NULL, &testthing1);

  //Object *testthing1_object = Backfire_SceneGetObject(testthing1);
  testthing1_object = Backfire_GetHeadObject();

  testthing1_object->collision.x = 0;
  testthing1_object->collision.y = 100;
  testthing1_object->collision.w = 100;
  testthing1_object->collision.h = 300;

  testthing1_object->texture = IMG_Load("res/levelMap.png");


  Backfire_SceneAddObject(testthing1_object, &testthing1);

  Object *gotten_thing = Backfire_SceneGetObject(testthing1);

  gotten_thing->collision.x = 500;
  gotten_thing->collision.y = 500;
  gotten_thing->collision.w = 200;
  gotten_thing->collision.h = 90;

  gotten_thing->texture = IMG_Load("res/alphatest.png");


  printf("Image settings: %u\n", testthing1_object->texture->format->BytesPerPixel);



}

void destroy()
{
  Backfire_Close();
}

int main(int argc, char **argv)
{
  init();

  Backfire_Start(60, 0, 5000);//60 ticks a second and 0 = unlimited framerate and a max frameslip of 5000

  destroy();
  return 0;
}
