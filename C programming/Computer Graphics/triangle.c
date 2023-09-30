#include<GL/glut.h>

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.5,0,0.7);
glBegin(GL_TRIANGLES);
glVertex2f(-0.5,-0.5);
glVertex2f(0.5,-0.5);
glVertex2f(0,0.5);
glEnd();
glFlush();
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(0,0);
glutCreateWindow("GREEN TRIANGLE");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}