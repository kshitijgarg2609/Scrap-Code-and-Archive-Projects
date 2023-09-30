#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float b[3];
float c1[3];
float c2[3];

void set()
{
b[0]=0;
b[1]=1;
b[2]=0;

c1[0]=0;
c1[1]=1;
c1[2]=1;


c2[0]=1;
c2[1]=0;
c2[2]=1;
}

int matchPix(float x[],float y[])
{
if(x[0]==y[0]&&x[1]==y[1]&&x[2]==y[2])
{
return 1;
}
else
{
return 0;
}
}

void boundaryFill(int x,int y)
{
float c[3];
glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,c);  
printf("(x,y)=(%d,%d), (R,G,B)=(%d,%d,%d)\n",x,y,c[0],c[1],c[2]);
//printf("Function entered !!!\n");
if(matchPix(c,c2)||matchPix(c,b))
{
return;
}
if(matchPix(c,c1))
{
printf("Condition entered !!!\n");
glBegin(GL_POINTS);
glColor3f(c2[0],c2[1],c2[2]);
glVertex2f(x,y);
glEnd();
glFlush();
boundaryFill(x,y+1);
boundaryFill(x-1,y);
boundaryFill(x,y-1);
boundaryFill(x+1,y);
}
}

void display()
{
printf("Display entered !!!\n");
/*glBegin(GL_POLYGON);
glColor3f(c1[0],c1[1],c1[2]);
glVertex2f(200,200);
glVertex2f(200,400);
glVertex2f(400,400);
glVertex2f(400,200);
glEnd();
glFlush();*/
for(int x=300;x<=350;x++)
{
for(int y=300;y<=350;y++)
{
float c[3];
//float *c;
//c=(float*)malloc(3*sizeof(float));
glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,c);
printf("(x,y)=(%d,%d), (R,G,B)=(%d,%d,%d)\n",x,y,c[0],c[1],c[2]);
}
}
//boundaryFill(300,300);
}

void mouse(int btn, int state, int x, int y)   
       {   
             if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)    
            {   
                     boundaryFill(x,y);
             }   
       }

int main(int argc,char **argv)
{
printf("main entered !!!\n");
set();
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(0,0);
glutCreateWindow("Boundary Fill Algorithm");
glOrtho(0,500,0,500,-1.0, 1.0);
glClearColor(b[0],b[1],b[2],0);
glClear(GL_COLOR_BUFFER_BIT);
glutDisplayFunc(display);
glutMouseFunc(mouse);
glutMainLoop();
//boundaryFill(200,200);
return 0;
}