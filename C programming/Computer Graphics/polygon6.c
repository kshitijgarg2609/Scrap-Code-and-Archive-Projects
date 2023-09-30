#include<GL/glut.h>

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.1,0.1,1);
glBegin(GL_POLYGON);
glVertex2f(-0.3,0.5);
glVertex2f(0.3,0.5);
glVertex2f(0.7,0);
glVertex2f(0.3,-0.5);
glVertex2f(-0.3,-0.5);
glVertex2f(-0.7,0);
glEnd();
glFlush();
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(0,0);
glutCreateWindow("POLYGON HEXAGON");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}