#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

void handleKeypress(unsigned char key, int x, int y) {
  switch(key) {
  case 27: //escape key
    exit(0);
  }
}

void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 30.0f;

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);

  glPushMatrix();
  glTranslatef(0.0f, -1.0f, 0.0f);
  glRotatef(_angle, 0.0f, 0.0f, 1.0f);

  glBegin(GL_QUADS);
  //trapezoid
  glColor3f(0.5f, 0.0f, 0.8f);
  glVertex3f(-0.7f, -0.5f, 0.0f);
  glVertex3f(0.7f, -0.5f, 0.0f);
  glColor3f(0.0f, 0.5f, 0.8f);
  glVertex3f(0.4f, 0.5f, 0.0f);
  glVertex3f(-0.4f, 0.5f, 0.0f);
  glEnd();

  glPopMatrix();
  glPushMatrix();
  glTranslatef(1.0f, 1.0f, 0.0f);
  glRotatef(_angle, 0.0f, 1.0f, 0.0f);

  glBegin(GL_TRIANGLES);
  //pentagon
  glColor3f(0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.0f);
  glVertex3f(-0.5f, 0.0f, 0.0f);

  glColor3f(1.0f, 0.5f, 1.0f);
  glVertex3f(-0.5f, 0.0f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.0f);
  glVertex3f(0.5f, 0.0f, 0.0f);

  glColor3f(0.5f, 1.0f, 0.5f);
  glVertex3f(-0.5f, 0.0f, 0.0f);
  glVertex3f(0.5f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.5f, 0.0f);

  glEnd();

  glPopMatrix();
  glPushMatrix();
  glTranslatef(-1.0f, 1.0f, 0.0f);
  glRotatef(_angle, 1.0f, 2.0f, 3.0f);

  glBegin(GL_TRIANGLES);
  //triangle
  glColor3f(0.2f, 0.2f, 0.2f);
  glVertex3f(0.5f, -0.5f, 0.0f);
  glColor3f(0.5f, 0.5f, 0.5f);
  glVertex3f(0.0f, 0.5f, 0.0f);
  glColor3f(0.8f, 0.8f, 0.8f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glEnd();
  
  glPopMatrix();

  glutSwapBuffers();
}

void update(int value) {
  _angle += 2.0f;
  if (_angle > 360) {
    _angle -= 360;
  }

  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);

  glutCreateWindow("Basic Shapes");
  initRendering();
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  glutTimerFunc(25, update, 0);
  glutMainLoop();
  return 0;
}

