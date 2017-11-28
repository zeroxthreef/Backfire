#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <client/backfire.h>

void level1init()
{
  printf("init level1\n");
}

void level1destroy()
{
  printf("destroy level1\n");
}

void level1logic()
{
  //printf("logic level1\n");
  //testthing1_object->rotation += 18.0f;
}
void level1event(SDL_Event *event)
{
  //printf("event level1\n");
}
