#include<GL/glut.h>

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.7,0.7,0.3);
glBegin(GL_POLYGON);
glVertex2f(0.6,-0.6);
glVertex2f(-0.6,-0.6);
glVertex2f(-0.9,0.2);
glVertex2f(0,0.7);
glVertex2f(0.9,0.2);
glEnd();
glFlush();
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(0,0);
glutCreateWindow("POLYGON PENTAGON");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}