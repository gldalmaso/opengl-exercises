#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

void handleKeypress(unsigned char key, int x, int y) {
  switch(key) {
  case 27: //escape key
    exit(0);
    break;
  case 'l':
    if (glIsEnabled(GL_LIGHTING) == GL_TRUE) {
      glDisable(GL_LIGHTING);
    } else {
      glEnable(GL_LIGHTING);
    }
    break;
  }
}

void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = -70.0f;
float _lightXPos = -6.0f;
float _increment = 0.1f;

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glTranslatef(0.0f, 0.0f, -8.0f);
  
  GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
  
  GLfloat lightColor0[] = {0.0f, 0.0f, 1.0f, 1.0f};
  GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
  
  GLfloat lightColor1[] = {0.0f, 1.0f, 0.0f, 1.0f};
  GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
  
  GLfloat lightColor2[] = {1.0f, 0.0f, 0.0f, 1.0f};
  GLfloat lightPos2[] = {_lightXPos, 0.0f, 5.0f, 0.0f};
  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
  glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
  
  glRotatef(_angle, 1.0f, 1.0f, 1.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  
  //Front
  //glNormal3f(0.0f, 0.0f, 1.0f);
  glNormal3f(-1.0f, 0.0f, 1.0f);
  glVertex3f(-1.5f, -1.0f, 1.5f);
  glNormal3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.5f, -1.0f, 1.5f);
  glNormal3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.5f, 1.0f, 1.5f);
  glNormal3f(-1.0f, 0.0f, 1.0f);
  glVertex3f(-1.5f, 1.0f, 1.5f);
  
  //Right
  //glNormal3f(1.0f, 0.0f, 0.0f);
  glNormal3f(1.0f, 0.0f, -1.0f);
  glVertex3f(1.5f, -1.0f, -1.5f);
  glNormal3f(1.0f, 0.0f, -1.0f);
  glVertex3f(1.5f, 1.0f, -1.5f);
  glNormal3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.5f, 1.0f, 1.5f);
  glNormal3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.5f, -1.0f, 1.5f);
  
  //Back
  //glNormal3f(0.0f, 0.0f, -1.0f);
  glNormal3f(-1.0f, 0.0f, -1.0f);
  glVertex3f(-1.5f, -1.0f, -1.5f);
  glNormal3f(-1.0f, 0.0f, -1.0f);
  glVertex3f(-1.5f, 1.0f, -1.5f);
  glNormal3f(1.0f, 0.0f, -1.0f);
  glVertex3f(1.5f, 1.0f, -1.5f);
  glNormal3f(1.0f, 0.0f, -1.0f);
  glVertex3f(1.5f, -1.0f, -1.5f);
  
  //Left
  //glNormal3f(-1.0f, 0.0f, 0.0f);
  glNormal3f(-1.0f, 0.0f, -1.0f);
  glVertex3f(-1.5f, -1.0f, -1.5f);
  glNormal3f(-1.0f, 0.0f, 1.0f);
  glVertex3f(-1.5f, -1.0f, 1.5f);
  glNormal3f(-1.0f, 0.0f, 1.0f);
  glVertex3f(-1.5f, 1.0f, 1.5f);
  glNormal3f(-1.0f, 0.0f, -1.0f);
  glVertex3f(-1.5f, 1.0f, -1.5f);
  
  glEnd();
  
  glutSwapBuffers();
}

void update(int value) {
  _angle +=1.5f;
  if (_angle > 360) {
    _angle -= 360;
  }
  
  _lightXPos += _increment;
  if (_lightXPos <= -6.0f || _lightXPos >= 6.0f) {
    _increment = _increment * -1.0f;
  }
  
  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  
  glutCreateWindow("Lighting");
  initRendering();
  
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  
  glutTimerFunc(25, update, 0);
  
  glutMainLoop();
  return 0;
}


