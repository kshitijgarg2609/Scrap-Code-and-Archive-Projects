#include<GL/glut.h>
void display()
{
glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1,0,0);
glBegin(GL_TRIANGLES);
glVertex2f(-0.1,-0.5);
glVertex2f(-0.3,0.1);
glVertex2f(0.1,0.1);
glEnd();

glColor3f(0.4,0.5,0);
glBegin(GL_QUADS);
glVertex2f(-0.1,0.5);
glVertex2f(0.5,0.5);
glVertex2f(0.1,0.1);
glVertex2f(0.6,0.1);
glEnd();

glColor3f(0,0.75,0.34);
glBegin(GL_QUADS);
glVertex2f(0.1,0.1);
glVertex2f(0.6,0.1);
glVertex2f(0.1,-0.5);
glVertex2f(0.7,-0.5);
glEnd();

glColor3f(1,0,1);
glBegin(GL_QUADS);
glVertex2f(-0.3,0.1);
glVertex2f(0.1,0.1);
glVertex2f(-0.3,-0.5);
glVertex2f(0.1,-0.5);
glEnd();
glFlush();
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,400);
glutInitWindowPosition(0,0);
glutCreateWindow("GREEN TRIANGLE");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}