#ifndef TYPES_H__
#define TYPES_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint8_t BACKFIRE_BOOL_t;

typedef struct{
  float x;
  float y;
  float w;
  float h;
} Backfire_rect;

typedef struct{
  BACKFIRE_BOOL_t canExit;
  unsigned loopDelay;
  unsigned long state;
  BACKFIRE_BOOL_t cameraEnabled;
  float cameraAngle;
  Backfire_rect camera;
  BACKFIRE_BOOL_t debug;
} GlobalSettings;

GlobalSettings gSettings;


#ifdef __cplusplus
}
#endif


#endif /* TYPES_H__*/
