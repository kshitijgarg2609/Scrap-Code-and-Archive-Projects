#include<GL/glut.h>

void display()
{
glClear(GL_COLOR_BUFFER_BIT);

glColor3f(0,1,0);
glBegin(GL_LINE_LOOP);
glVertex2f(-0.8,0.5);
glVertex2f(0.83,0.23);
glVertex2f(-0.823,0.98);
glVertex2f(0.3,0.2);
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