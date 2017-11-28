#ifndef PHYSICS_H__
#define PHYSICS_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  float friction;
  float mass;
  float dampening;
  float bouncyness;
} Physics;

#ifdef __cplusplus
}
#endif

#endif /* PHYSICS_H__*/
