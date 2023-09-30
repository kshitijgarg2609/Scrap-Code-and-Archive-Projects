#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
void polygon()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,1,1);
glBegin(GL_POLYGON);
glVertex2f(0,0);
glVertex2f(0.5,0);
glVertex2f(0.5,0.5);
glVertex2f(0,0.5);
glEnd();
glFlush();
}
void main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
glutInitWindowPosition(100,100);
glutInitWindowSize(400,400);
glutCreateWindow("polygon");
glutDisplayFunc(polygon);
glutMainLoop();
}
