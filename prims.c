#include "stdafx.h"

#include<stdlib.h>
#include<glut.h>
#include<iostream>
#include<math.h>

using namespace std;

int costmatrix[100][100];
int nodenum=1,load=0,found=0;
bool enterpressed=false,resdisplay=false;
char text[15]="Draw mode:NONE";
float sx=-1,sy=-1;
GLfloat width=900,height=600;


void reshape(int w, int h)
{
	width=w;
	height=h;
	glViewport(0, 0,(GLsizei) w,(GLsizei) h);
   glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
	if(w<=h) 
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 2.0* (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else 
		glOrtho(-2.0 * (GLfloat) w/ (GLfloat) h, 2.0* (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
}

void bitmap_output(int x, int y, char *string, void *font)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void delay(){
int i=190000000;
while(i--);
}

void loadpage(){
	delay();
	glLineWidth(20);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(100,300);
	glVertex2d(100+load,300);
	glEnd();
	load+=50;
	glFlush();//glutSwapBuffers();
	glutPostRedisplay();
}

void frontpage()
{
	glLineWidth(2);
	glColor3f(0.9,0.8,0.9);
	bitmap_output(width/3+50, height-height/10, "WELCOME! TO",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.9,0.8,0.0);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(width/3+30, height-height/9);
		glVertex2f(width/3+240, height-height/9);
	glEnd();
	glColor3f(0.9,0.8,0.9);
	bitmap_output(width/3+10, height-height/6, "Prims algorithm visualiser",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.9,0.8,0.0);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(width/3-10, height-height/5.5);
		glVertex2f(width/3+290, height-height/5.5);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	bitmap_output(width/3+100,height-height/3.5,"Made by",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(width/3+10,height-height/2.8,"Seetaram Naik - 4SU19CS088",GLUT_BITMAP_TIMES_ROMAN_24);
	glFlush();//glutSwapBuffers();
	delay();
	glColor3f(1,0.1,0.2);
	bitmap_output(width/2+150, 125, "Press Enter to Continue.......",GLUT_BITMAP_HELVETICA_18);
	glFlush();//glutSwapBuffers();
	delay();
	glutPostRedisplay();
}

void Instructions()
{
	glColor3f(1.0,1.0,0.0);
	bitmap_output(10, height-height/10, "Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(10, height-height/9);
		glVertex2f(130, height-height/9);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	bitmap_output(10, height-height/7, "->Press N to Create Nodes",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(10,height-height/5.8, "->Press E to draw Edges",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(10, height-height/4.9, "->Press D to draw spanning tree",GLUT_BITMAP_HELVETICA_18);
}

/*void drawpoint(){
	float angle=2.0f*3.1416f/360;
	int radius=25;
	for(int i=0;i<pointer;i++){
		glBegin(GL_POINTS);
	glColor3f(1,1,0);
	double angle1=0.0;
	glBegin(GL_POLYGON);
	glVertex2d(oldx[i][0]-radius*cos(0.0),radius*sin(0.0)+oldx[i][1]);
	for(int j=0;j<360;j++){

	glVertex2d(oldx[i][0]-radius*cos(angle1),radius*sin(angle1)+oldx[i][1]);
	angle1+=angle;
	
	}
	glEnd();
	}
	
	for(int i=0;i<pointer;i++){
	glColor3f(0,0,0);
	int_str(nodenum,num);
	nodenum++;
	bitmap_output(oldx[i][0]-5,oldx[i][1]-6,num,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}*/


void drawPointAt(float x,float y){
	glPointSize(25);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();

}



void display()
{
  nodenum=0;
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0,0.0,0.2,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,width,0,height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if(load<800 && found==0){
	  glColor3f(1,1,1.0);
	  bitmap_output(100,325,"LOADING",GLUT_BITMAP_HELVETICA_18);
	  loadpage();
  }else if(load<800 && found==1){
	        glColor3f(1,1,1.0);
			bitmap_output(100,325,"CALCULATING",GLUT_BITMAP_HELVETICA_18);
		    loadpage();
	}else{
	if(!enterpressed){
		glLineWidth(25); 
		frontpage();
	}
	/*else if(enterpressed){
			if(!found){
				Instructions();
				glColor3f(0.1,1,0.0);
				bitmap_output(width-width/2+200,height-height/9,text,GLUT_BITMAP_HELVETICA_18);
	 		}
	       glPointSize(40);
		   drawpoint();
	       if(sx!=-1&&sy!=-1){
	       drawPointAt(sx,sy);
	      }
	      if(!found)
	      drawline();
	if(found){
	output();
	blinking_lines();
	}
	}*/
	}
	glFlush();//glutSwapBuffers();
}


int main(int argc,char** argv){
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			if(i==j){
				costmatrix[i][j]=0;
			}
			else costmatrix[i][j]=999;
		}
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(250,50);
	glutInitWindowSize(width,height);
	glutCreateWindow("Prim's Algorithm");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
