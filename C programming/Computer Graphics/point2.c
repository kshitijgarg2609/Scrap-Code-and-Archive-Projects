#include<GL/glut.h>

void display()
{
glClear(GL_COLOR_BUFFER_BIT);

glColor3f(0.9,1,0.3);
glBegin(GL_POINTS);
glVertex2f(-0.8,0.7);
glVertex2f(-0.6,0.7);
glEnd();
glFlush();
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(0,0);
glutCreateWindow("POLYGON TRIANGLE");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}