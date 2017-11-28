#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include <client/types.h>
#include <client/tmx.h>//call createMap in the scene to assemble the map
#include <client/physics.h>
#include <client/scene.h>

Object *head = NULL, *current = NULL, *previous = NULL;

unsigned long objectIDCounter = 0;

BACKFIRE_BOOL_t Backfire_InitScene()
{


  return 0;
}

BACKFIRE_BOOL_t Backfire_DestroyScene()
{
  for(current = head; current; current = current->next)
  {
    previous = current;
    current = current->next;
    if(current != NULL)
    {
      SDL_FreeSurface(previous->texture);
      free(previous);
    }
  }

  return 0;
}

BACKFIRE_BOOL_t Backfire_SceneAddObject(Object *object, unsigned long *ID)//add ~100 objects then cycle through all of them and delete the unused ones. If its unused before then reuse them
{
  printf("Creating Object\n");

  if(head ==NULL)//for the first one
  {

    if((head = malloc(sizeof(Object))) == NULL)
      return 1;
    head->next = NULL;
    current = head;
  }
  else
  {
    for(current = head; current->next != NULL; current = current->next)
    {
      printf("oooof\n");
      previous = current;
    }
    if(current->next == NULL){
      //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Found Object List End", "Found Object List End", NULL);
      if((current->next = malloc(sizeof(Object))) == NULL)
      {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Error", "Critical Memory Error", NULL);
        return 1;
      }
    }
    current = current->next;
  }

  if(object == NULL)
  {
    current->used = 1;
    current->visible = 0;
    current->physics = 0;
    current->texture = NULL;
    current->physicsProperties.friction = 0;
    current->physicsProperties.mass = 0;
    current->physicsProperties.dampening = 0;
    current->physicsProperties.bouncyness = 0;
    current->lifetime = 0;
    current->collisionType = 0;
    current->type = 0;
    current->angle = 0.0f;
    current->rotation = 0.0f;
    current->magnitude = 0.0f;
  }
  else
  {
    if((memmove(current, object, sizeof(Object))) == NULL)
      return 1;
  }

  //these have to be set regardless
  current->ID = objectIDCounter;
  ID = objectIDCounter;
  current->next = NULL;




  objectIDCounter++; //count up object id and even if it loops, scan if the object is used and skip over used ones
  return 0;
}

Object *Backfire_SceneGetObject(unsigned long objectID)
{
  for(current = head; current; current = current->next)//->next != NULL
  {
    if(current->ID == objectID)
    {
      printf("found object\n");
      return current;
    }
  }

  return NULL;
}

BACKFIRE_BOOL_t Backfire_CleanObjects()
{
  for(current = head; current; current = current->next)
  {

    if(current->used == 0)
    {
      if(current == head)//if first object
      {
        head = current->next;
        SDL_FreeSurface(current->texture);
        free(current);
      }
      else//if not first object
      {
        //take the previous and attach it to the xurrent->next then free

        if(current->next == NULL)//for the end object
        {
          SDL_FreeSurface(current->texture);
          free(current);
        }
        else
        {
          previous->next = current->next;
          SDL_FreeSurface(current->texture);
          free(current);
        }
      }
    }
    previous = current;
  }
}

Object *Backfire_GetHeadObject()
{
  return head;
}
