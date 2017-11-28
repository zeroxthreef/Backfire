#ifndef STATE_H__
#define STATE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*StateInitCB)(void);//the initialize callback for the state
typedef void(*StateLogicCB)(void);//the loop callback for the state
typedef void(*StateEventCB)(SDL_Event *);//the event callback for the state
typedef void(*StateDestroyCB)(void);//the destroy callback for the state


typedef struct{
  StateInitCB Init;
  StateEventCB Event;
  StateLogicCB Logic;
  StateDestroyCB Destroy;
} State;

void BInternal_UpdateStates();

void BInternal_UpdateLogic();

void BInternal_UpdateEvent(SDL_Event *event);

BACKFIRE_BOOL_t Backfire_AddState(StateInitCB *stateinit, StateEventCB *stateevent, StateLogicCB *statelogic, StateDestroyCB *statedestroy);

#ifdef __cplusplus
}
#endif

#endif /* STATE_H__*/
