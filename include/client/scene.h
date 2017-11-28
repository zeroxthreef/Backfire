#ifndef SCENE_H__
#define SCENE_H__

#ifdef __cplusplus
extern "C" {
#endif

//TODO make a physics struct

typedef struct Object_t{
  unsigned long ID;
  BACKFIRE_BOOL_t used;
  BACKFIRE_BOOL_t visible;
  BACKFIRE_BOOL_t physics;
  Physics physicsProperties;
  //need to add a texture thing
  SDL_Surface *texture;//set with IMG_Load_RW()
  unsigned long lifetime; //used for particles. Set to 0 for unlimited
  BACKFIRE_BOOL_t collisionType;//0 is rectangular and 1 is circular
  unsigned long type;
  float rotation;
  float angle;
  float magnitude;
  Backfire_rect collision;
  struct Object_t *next;
} Object;



BACKFIRE_BOOL_t Backfire_InitScene();

BACKFIRE_BOOL_t Backfire_DestroyScene();

BACKFIRE_BOOL_t Backfire_SceneAddObject(Object *object, unsigned long *ID);

Object *Backfire_SceneGetObject(unsigned long objectID);

Object *Backfire_GetHeadObject();

#ifdef __cplusplus
}
#endif

#endif /* SCENE_H__*/
