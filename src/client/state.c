#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <client/types.h>
#include <client/state.h>

unsigned long previousState = 0, statecount = 0;

State *states = NULL;

void BInternal_UpdateStates()
{
  static unsigned long previous = 0;
  static BACKFIRE_BOOL_t first = 1;

  if(first)//do not destroy any states when at 0
  {
    printf("First state setup\n");
    states[gSettings.state].Init();
    first--;
  }
  else
  {
    if(previous != gSettings.state)
    {
      if(gSettings.state < statecount)
      {
        printf("changing states from %lu to %lu\n", previous, gSettings.state);
        states[previous].Destroy();
        states[gSettings.state].Init();
        previous = gSettings.state;
      }
      else{
        gSettings.state = statecount - 1;
      }
    }
  }
}


void BInternal_UpdateLogic()
{
  //call only current
  if(gSettings.state < statecount)
  {
    states[gSettings.state].Logic();
  }
  else
  {
    printf("State not existent\n");
  }
}

void BInternal_UpdateEvent(SDL_Event *event)
{
  if(gSettings.state < statecount)
  {
    states[gSettings.state].Event(event);
  }
  else
  {
    printf("State not existent\n");
  }
}

BACKFIRE_BOOL_t Backfire_AddState(StateInitCB *stateinit, StateEventCB *stateevent, StateLogicCB *statelogic, StateDestroyCB *statedestroy)
{
  static int firstcall = 0;
  if(firstcall)
  {
    if((states = malloc(sizeof(State))) == NULL)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Memory Error", "Could not allocate memmory for crucial component.", NULL);
      return 1;
    }
    firstcall++;
  }
  else
  {
    if((states = realloc(states, sizeof(State) * (statecount + 1))) == NULL)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Memory Error", "Could not rellocate memmory for crucial component.", NULL);
      return 1;
    }
  }
  //============================================================================

  states[statecount].Init = stateinit;
  states[statecount].Event = stateevent;
  states[statecount].Logic = statelogic;
  states[statecount].Destroy = statedestroy;


  statecount++;
  return 0;
}
