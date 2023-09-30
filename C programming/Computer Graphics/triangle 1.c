#include<GL/glut.h>
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0,1,1);
glBegin(GL_TRIANGLES);
glVertex2f(-0.5,-0.5);
glVertex2f(0.5,-0.5);
glVertex2f(0,0.5);
glEnd();
//glColor3f(1,0,0);
//glRasterPos2f(-0.90,-0.90);
//glutBitmapString(GLUT_BITMAP_HELVETICA_18,"ASHISH NEGI");
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