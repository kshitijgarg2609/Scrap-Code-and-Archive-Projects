#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

void display()
{
glColor3f(0, 1, 1);

int x1 = 2;
int y1 = 4;
int x2 = 80;
int y2 = 70;

int dy, dx,d,dE,dNE;

dy = (y2 - y1);
dx = (x2 - x1);
d = 2 * dy - dx ;
dE = 2 * dy;
dNE= 2 * (dy-dx);

glBegin(GL_POINTS);
glVertex2f(x1, y1);
while(x1 < x2)
{
if(d<=0)
{
d = d + dE;
}
else
{
d = d + dNE;
y1 = y1 + 1;
}
x1 = x1 + 1;
glVertex2f(x1, y1);
}

glEnd();
glFlush();
}


int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(0,0);
glutCreateWindow("Bresenhem's Line Algorithm");
glOrtho(-100,100,-100,100,-1.0, 1.0);
glClearColor(0, 0, 0, 1);
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
