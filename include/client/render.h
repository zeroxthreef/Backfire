#ifndef RENDER_H__
#define RENDER_H__

#include <client/types.h>

#ifdef __cplusplus
extern "C" {
#endif


BACKFIRE_BOOL_t Backfire_CreateMainWindowOpenGL(const char *title, int x, int y, int w, int h);

BACKFIRE_BOOL_t Backfire_InitRenderer();

BACKFIRE_BOOL_t Backfire_DestroyRenderer();

void BRender();

#ifdef __cplusplus
}
#endif

#endif /* RENDER_H__*/
