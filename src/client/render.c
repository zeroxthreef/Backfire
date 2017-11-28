#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include <client/physics.h>
#include <client/types.h>
#include <client/scene.h>
#include <client/render.h>

SDL_Window *window = NULL;

SDL_GLContext context;

BACKFIRE_BOOL_t Backfire_CreateMainWindowOpenGL(const char *title, int x, int y, int w, int h)
{
  if((window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_OPENGL)) == NULL)
  {
    printf("Unable to create window\n");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetSwapInterval(1);

  context = SDL_GL_CreateContext(window);

  //glEnable(GL_DEPTH_TEST);
  glDisable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, (GLdouble)w, (GLdouble)h, 0.0f, 0.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



  return 0;
}

BACKFIRE_BOOL_t Backfire_InitRenderer()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    return 1;

  return 0;
}

BACKFIRE_BOOL_t Backfire_DestroyRenderer()
{
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  return 0;
}

void BRender()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //============================================================================

  Object *current = NULL;
  GLuint textures;

  //do camera stuff
  glTranslatef(gSettings.camera.x, gSettings.camera.y, 0);
  glRotatef(gSettings.cameraAngle, 0, 0, 1);

  for(current = Backfire_GetHeadObject(); current; current = current->next)
  {

    if(current->texture)
    {

      ////glBegin(GL_TEXTURE);//can I do this?

      glPushMatrix();

      glEnable(GL_TEXTURE_2D);
      glGenTextures(1, &textures);
      glBindTexture(GL_TEXTURE_2D, textures);
      glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, current->texture->w, current->texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, current->texture->pixels);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      //glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)

      ////glEnd();

      glTranslatef(current->collision.x, current->collision.y, 0);
      glRotatef(current->rotation, 0, 0, 1);
      glBegin( GL_QUADS );
        //glColor3b(255, 255, 255);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(current->collision.w, 0);
        glTexCoord2f(1, 1); glVertex2f(current->collision.w, current->collision.h);
        glTexCoord2f(0, 1); glVertex2f(0, current->collision.h);
      glEnd();


      glDisable(GL_TEXTURE_2D);

      glPopMatrix();
    }
  }


//debug=========================================================================
/*
  glBegin( GL_QUADS );
    glVertex2f(0 + 500, 0 + 500);
    glVertex2f(20 + 500, 0 + 500);
    glVertex2f(20 + 500, 20 + 500);
    glVertex2f(0 + 500, 20 + 500);
  glEnd();

  glBegin(GL_TRIANGLES);
    glColor3ub(255, 0, 0);
    glVertex2d(0, 0);

    glColor3ub(0, 255, 0);
    glVertex2d(100,0);

    glColor3ub(0, 0, 255);
    glVertex2d(50, 50);
    //glClear(GL_COLOR_BUFFER_BIT);
  glEnd();
  */
  //============================================================================
  //glFlush();
  SDL_GL_SwapWindow(window);
  //render code
  //printf("Rendering\n");
}
