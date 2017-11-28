#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <client/backfire.h>




//==============================================================================
BACKFIRE_BOOL_t Backfire_Init()
{
  printf("===================START===================\n");
  gSettings.canExit = 0;
  gSettings.loopDelay = 0;

  if(Backfire_InitRenderer())
    exit(1);

    gSettings.state = 0;
    gSettings.cameraEnabled = 1;
    gSettings.cameraAngle = 0.0f;

  return 0;
}

BACKFIRE_BOOL_t Backfire_AddEventCB(void(*callback)(void))
{
  EventCB = callback;
  if(EventCB == NULL)
  {
    return 1;
  }
  //EventCB(NULL);
  return 0;
}

BACKFIRE_BOOL_t Backfire_AddLogicCB(void(*callback)(SDL_Event *))
{
  LogicCB = callback;
  if(LogicCB == NULL)
  {
    return 1;
  }
  //LogicCB();
  return 0;
}

BACKFIRE_BOOL_t Backfire_Close()
{
  printf("====================END====================\n");
  gSettings.canExit = 1;
  if(Backfire_DestroyRenderer)
    exit(1);
  return 0;
}

void Backfire_Start(int tickRate, int maxFramerate, int maxFrameskip)
{
  static SDL_Event event;
  int tickrate = 1000 / tickRate, lastTime = SDL_GetTicks(), lagFrames = 0, currentTime = 0, skipTime = 0;
  float fps = 0.0f;

  while(!gSettings.canExit)
  {
    BInternal_UpdateStates();
    while (SDL_PollEvent(&event))
    {
      EventCB(&event);
      BInternal_UpdateEvent(&event);
      /*call the event callback.
      Everything the game does when looking for SDL events will be all sent through
      here.
      */
    }


    LogicCB();
    BInternal_UpdateLogic();
    /*call the logic callback.
    This is the last callback needed in the loop because it deals with all of
    the games logic. Renderer isnt handled by the game to add simplicity.
    */

    if(skipTime >= 0)
    {
      BRender();
      //printf("Rendering frame\n");
      /*this is an internal function not to be used by the game. All rendering
      and handling of opengl and windows goes on through here.
      */
      SDL_Delay(skipTime);
    } else if(lagFrames < maxFrameskip)
    {
      //printf("Skipping frame\n");
      lagFrames++;
    } else
    {
      printf("Too many skipped frames\n");
      lagFrames = 0;
    }

    lastTime += tickrate;
    currentTime = SDL_GetTicks();

    skipTime = lastTime - currentTime;
  }

}
