#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>

#include <client/backfire.h>

Object *thingy = NULL;

void menuinit()
{
  printf("init menu\n");
  thingy = Backfire_SceneGetObject(1);
}

void menudestroy()
{
  printf("destroy menu\n");
}

void menulogic()
{
  static float i = 0.0f;
  //printf("logic menu\n");

  thingy->rotation += -3.0f - sin(i) * 18.0f;

  thingy->collision.w = sin(i) + thingy->collision.w;

  i+=0.3f;
}
void menuevent(SDL_Event *event)
{
  //printf("event menu\n");
}
