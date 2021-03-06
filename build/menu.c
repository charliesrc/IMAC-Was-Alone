#include "menu.h"


int afficherMenu(int select, GLuint textureId){


  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glBegin(GL_QUADS);

  glColor3f(1, 1, 1);

  glTexCoord2f(0, 1);
  glVertex2f(-40, -15);

  glTexCoord2f(1, 1);
  glVertex2f(40, -15);

  glTexCoord2f(1, 0);
  glVertex2f(40, 45);

  glTexCoord2f(0, 0);
  glVertex2f(-40, 45);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);

  switch (select) {
    case 0 :
    glPointSize(30.0);

    glBegin(GL_POINTS);

    glColor3ub(255, 0, 0);

    glVertex2f(-19, -10);

    glEnd();
    break;

    case 1 :
    glPointSize(30.0);

    glBegin(GL_POINTS);

    glColor3ub(255, 255, 0);

    glVertex2f(0, -10);

    glEnd();
    break;

    case 2 :
    glPointSize(30.0);

    glBegin(GL_POINTS);

    glColor3ub(0, 0, 255);

    glVertex2f(19, -10);

    glEnd();
    break;

    default : break;

  }

  SDL_GL_SwapBuffers();

  return 0;
}
