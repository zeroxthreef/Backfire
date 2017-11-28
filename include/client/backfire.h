#ifndef BACKFIRE_H__
#define BACKFIRE_H__

#include <client/types.h>
#include <client/tmx.h>
#include <client/render.h>
#include <client/physics.h>
#include <client/scene.h>
#include <client/state.h>

#ifdef __cplusplus
extern "C" {
#endif

void(*LogicCB)(void);//each of these takes care of all of its stuff in a loop outside of program
//use these for things like the pause menu and other global stuff like maybe HUD?
void(*EventCB)(SDL_Event *);//each of these takes care of all of its stuff in a loop outside of program


BACKFIRE_BOOL_t Backfire_Init();//init the client

BACKFIRE_BOOL_t Backfire_AddEventCB(void(*callback)(void));//add event callback

BACKFIRE_BOOL_t Backfire_AddLogicCB(void(*callback)(SDL_Event *));//add logic callback

BACKFIRE_BOOL_t Backfire_Close();//close and sestroy backfire





#ifdef __cplusplus
}
#endif

#endif /* BACKFIRE_H__*/
