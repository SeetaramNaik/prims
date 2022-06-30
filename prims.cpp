// prims.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// prims.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include<stdlib.h>
#include<iostream>
#include<glut.h>
#include<math.h>
#include<cstring>

using namespace std;

void find_spanning_tree();
void bitmap_output(int x, int y, char *string, void *font);

//Global variables
int pointer=0,point=0,line=0,lpointer=0,upointer=-1,undo_cost_stack_pointer=-1;
int costmatrix[100][100],undo_cost_stack[100],lineundostack[100][100];
int undone=0,nf=0,f=0,found=0,nodenum=1,load=0;
int t[100][2],totalcost;
bool paused=false;
bool start=false,enterpressed=false,resdisplay=false,show_algorithm=false,back=false;
char undostack[100];
char num[2];
char text[15]="Draw mode:NONE";
float sx=-1,sy=-1;
float oldx[100][100],linepoints[2][2],linex[100][4];
float fade=0.1;
GLfloat width=900,height=600;

//This functions writes the integer into char array
void int_str(int rad,char r[])
{
	sprintf(r,"%d",rad);
}

//whenever undo function is called the cost is pushed into the stack
void push(int n){
	undo_cost_stack[++undo_cost_stack_pointer]=n;
}

//when redo function is called the cost is popped out
int pop(){
	if(undo_cost_stack_pointer>=0){
		return undo_cost_stack[undo_cost_stack_pointer--];
	}
	return 999;
}

//this function creates nodes using location stored in oldx[][] array
void drawpoint(){


	float angle=4.0f*3.1416f/360;
	int radius=5;
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
}

//This function prints text in graphics window
void bitmap_output(int x, int y, char *string, void *font)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

//this delays out execution of next instruction
void delay(){
//int i=190000000;
	int i=190000;
while(i--);
}



//this function displays staring window
void introduction_page()
{
glBegin(GL_POLYGON);
glColor3f(0.9,0.3,0.1);
glVertex2d(0,0);
glColor3f(0.0,0.0,0.0);
glVertex2d(0,height);
glColor3f(0.0,0.0,0.0);
glVertex2d(width,height);
glColor3f(1.0,0.4,0.0);
glVertex2d(width,0);
glEnd();
	 
	
	glLineWidth(2);
	glColor3f(1.0,1.0,1.0);
	
	bitmap_output(width/3, height-height/10, "SDM Institute of Technology, Ujire",GLUT_BITMAP_HELVETICA_18);
	//glColor3f(0.9,0.8,0.0);

	glColor3f(1.0,1.0,1.0);
	bitmap_output(width/4+50, height-height/6, "Computer Graphics Lab with Mini Project",GLUT_BITMAP_HELVETICA_18);
	glColor3f(1.0,1.0,1.0);
	bitmap_output(width/4+55, height-height/4, "****PRIMS ALGORITHM****",GLUT_BITMAP_TIMES_ROMAN_24);
	/*glColor3f(0.9,0.8,0.0);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(width/3-10, height-height/5.5);
		glVertex2f(width/3+290, height-height/5.5);
	glEnd();*/
	glColor3f(1.0,1.0,1.0);
	bitmap_output(width/15+55,height-height/1.87,"---Made by---",GLUT_BITMAP_HELVETICA_18);

	glColor3f(0.8,1.0,0.0);
	bitmap_output(width/15+10,height-height/1.62,"Seetaram Naik - 4SU19CS088",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(width/15+10,height-height/1.5,"Shamanth P     - 4SU19CS089",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(width/15+10,height-height/1.4,"Shivam Ravan  - 4SU19CS091",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(width/15+10,height-height/1.3,"Skanda Bhat    - 4SU19CS095",GLUT_BITMAP_HELVETICA_18);

	glColor3f(1.0,1.0,1.0);
	bitmap_output(width/15+580,height-height/1.6,"---Guided by---",GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.8,1.0,0.0);
	bitmap_output(width/15+595,height-height/1.4,"Mr. Arjun K.",GLUT_BITMAP_TIMES_ROMAN_24);
	glFlush();//glutSwapBuffers(); 
	delay();
	glColor3f(1.0,1.0,0.9);
	bitmap_output(width/5+150, 30, "Press 'ENTER' to continue",GLUT_BITMAP_TIMES_ROMAN_24);
	glFlush();//glutSwapBuffers();
	delay();
	//glutPostRedisplay();
}

void instruction_page()
{
	glBegin(GL_POLYGON);
//glColor3f(1.0,0.4,0.0);
glColor3f(0.65,0.65,0.65);
glVertex2d(0,0);
///glColor3f(0.0,0.0,0.0);
glColor3f(0.0,0.138,0.96);
glVertex2d(0,height);
glColor3f(0.0,0.138,0.96);
glVertex2d(width,height);
glColor3f(0.65,0.65,0.65);
glVertex2d(width,0);
glEnd();
	glColor3f(1.0,1.0,1.0);
	bitmap_output(300, height-100, "****PRIMS ALGORITHM****",GLUT_BITMAP_TIMES_ROMAN_24);
	//bitmap_output(10, height-120, "****INSTRUCTIONS****",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(300, height-200, "Press 'S'       -  To START ",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(300, height-250, "Press 'I'         -  To see Working of Prims algorithm ",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(300, height-300, "Press 'ESC'   -  To QUIT",GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,1.0);
	bitmap_output(500, height-570, "Press 'A' to go to INTRODUCTION PAGE",GLUT_BITMAP_HELVETICA_18);
}


//this function displays text instructions in grpahics windwow
void draw_instructions()
{
	glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex2d(0,0);
    glColor3f(0.0,0.0,0.0);
	glVertex2d(0,height);
	glColor3f(0.0,0.0,0.0);
	glVertex2d(width,height);
	glColor3f(1.0,1.0,1.0);
	glVertex2d(width,0);
	glEnd();
	glColor3f(1.0,1.0,0.0);
	bitmap_output(10, height-height/15, "Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(10, height-height/13);
		glVertex2f(130, height-height/13);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	bitmap_output(10, height-height/8.5, "-> Press N to Create Nodes",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(10,height-height/6.2, "-> Press E to draw Edges",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(10, height-height/4.9, "-> Press D to draw spanning tree",GLUT_BITMAP_HELVETICA_18);
}


void algorithm()
{ 
glBegin(GL_POLYGON);
//glColor3f(1.0,0.4,0.0);
glColor3f(0.9,0.3,0.1);
glVertex2d(0,0);
///glColor3f(0.0,0.0,0.0);
glColor3f(0.0,0.138,0.96);
glVertex2d(0,height);
glColor3f(0.0,0.138,0.96);
glVertex2d(width,height);
glColor3f(1.0,0.4,0.0);
glVertex2d(width,0);
glEnd();
glColor3f(1.0,1.0,1.0);
bitmap_output(width/6+25, height-50, "***PRIMS ALGORITHM WORKING STEPS***",GLUT_BITMAP_TIMES_ROMAN_24);
bitmap_output(width/15+25, height-150, "1.  Create a mstSet that keeps track of vertices already included in MST. ",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+25, height-190, "2.  Initialize all key values as INFINITE. Assign the key value as 0 for the first vertex so",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+45, height-230, "  that it is picked first.",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+25, height-270, "3.  While mstSet doesn't include all vertices ",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+45, height-310, "...a)  Pick a vertex u which is not there in mstSet and has a minimum key value. ",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+45, height-350, "...b)  Include u to mstSet. ",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+45, height-390, "...c)  Update key value of all adjacent vertices of u.  ",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+82, height-410, " To update the key values, iterate through all adjacent vertices. ",GLUT_BITMAP_HELVETICA_18); 
bitmap_output(width/15+82, height-450, " For every adjacent vertex v, if the weight of edge u-v is less than the previous ",GLUT_BITMAP_HELVETICA_18);
bitmap_output(width/15+82, height-490, " key value of v, update the key value as the weight of u-v. ",GLUT_BITMAP_HELVETICA_18);
glColor3f(0.0,0.0,0.0);
bitmap_output(width/15+600, height-570, "Press 'B' to go back",GLUT_BITMAP_HELVETICA_18);
}


//this function draws edges using location stored in linex array
void drawline(){
	glColor3f(0.9f,1.0f,0.8f);
	glLineWidth(4.0);
	char* cst = new char[5];
	int temp;
	glBegin(GL_LINES);
	for(int i=0;i<lpointer;i++){
	glVertex2i(linex[i][0],linex[i][1]);
	glVertex2i(linex[i][2],linex[i][3]);
	}
	glEnd();
	glColor3f(0.0,1.0,0.0);
	for(int i=0;i<lpointer;i++){
		temp=costmatrix[lineundostack[i][0]][lineundostack[i][1]];
		sprintf(cst, "%d", temp);
		bitmap_output((linex[i][0]+linex[i][2])/2-15,(linex[i][1]+linex[i][3])/2+15,cst,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	glFlush();//glutSwapBuffers();
}

//this function does animation of lines connecting after calculating spanning tree
void blinking_lines(){

	delay();
	glLineWidth(7.0);
	for(int i=0;i<pointer-1;i++){
		glColor3f(0.0,0.0,1.0);


	glBegin(GL_LINES);
	glVertex2i(oldx[t[i][0]][0],oldx[t[i][0]][1]);
	glVertex2i(oldx[t[i][1]][0],oldx[t[i][1]][1]);
	glEnd();
	delay();
	glFlush();//glutSwapBuffers();
	// glutPostRedisplay();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2i(oldx[t[i][0]][0],oldx[t[i][0]][1]);
	glVertex2i(oldx[t[i][1]][0],oldx[t[i][1]][1]);
	delay();
	glEnd();
	/*int temp;
	char* cst = new char[5];
	glColor3f(0.0,1.0,0.0);
	for(int i=0;i<lpointer-1;i++){
		temp=costmatrix[t[i][0]][t[i][1]];
		itoa(temp,cst,10);
		bitmap_output((oldx[t[i][0]][0]+oldx[t[i][1]][0])/2-15,(oldx[t[i][0]][1]+oldx[t[i][1]][1])/2+8,cst,GLUT_BITMAP_TIMES_ROMAN_24);
	}*/
	glFlush();//glutSwapBuffers();
	}   
}

//this displays a point when mouse clicked for first time in draw edge mode
void drawPointAt(float x,float y){
	glPointSize(15);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();

}

//this function mimics loading animation
void loadpage(){
	
	glBegin(GL_POLYGON);
//glColor3f(1.0,0.4,0.0);
//glColor3f(0.9,0.3,0.1);//orange
	glColor3f(0.5,0.4,0.9);
glVertex2d(0,0);
glColor3f(0.0,0.0,0.0);
glVertex2d(0,height);
glColor3f(0.0,0.0,0.0);
glVertex2d(width,height);
glColor3f(0.5,0.4,0.9);
glVertex2d(width,0);
glEnd();
glColor3f(1.0,1.0,1.0);
	bitmap_output(100,325,"LOADING",GLUT_BITMAP_HELVETICA_18);
	delay();
	glLineWidth(20);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(100,300);
	glVertex2d(100+load,300);
	glEnd();
	load+=100;
	glFlush();//glutSwapBuffers();
	glutPostRedisplay();
}

//this function displays text output after calculating spanning tree
void output(){
glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
glVertex2d(0,0);
glColor3f(0.0,0.0,0.0);
glVertex2d(0,height);
glColor3f(0.0,0.0,0.0);
glVertex2d(width,height);
glColor3f(1.0,1.0,1.0);
glVertex2d(width,0);
glEnd();

	//glColor3f(0.0,1.0,1.0);
    
    int xaxis = 10,yaxis=550;
	glColor3f(0.0,1.0,0.0);
	bitmap_output(650,520,"***OUTPUT***",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.658824,0.658824,0.658824);
	bitmap_output(xaxis,yaxis,"Costs of Minimum spanning tree :",GLUT_BITMAP_HELVETICA_18);
	char* buffer=new char[50];
	char* cst = new char[50];
	char* a=new char[50];
	char* b = new char[50];
	for(int i=0;i<pointer-1;i++){
		sprintf(a, "%d", t[i][0]);
		strcat(a,"->");
		sprintf(b, "%d", t[i][1]);
		strcat(a,b);
		sprintf(cst, "%d", costmatrix[t[i][0]][t[i][1]]);
		strcat(a," = ");
		strcat(a,cst);
		yaxis-=20;
		bitmap_output(xaxis,yaxis,a,GLUT_BITMAP_HELVETICA_18);
	}
	char sumchar[50];
	sprintf(buffer,"%d", totalcost);
	strcat(sumchar,"spanning tree cost=");
	strcat(sumchar,buffer);
	bitmap_output(xaxis,yaxis-20,sumchar,GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	//bitmap_output(600,50,"Press 'R' to draw the tree again",GLUT_BITMAP_HELVETICA_18);


	//output graph

	//Node Drawing

	float angle=4.0f*3.1416f/360;
	int radius=5;
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
	nodenum=0;  //added part
	for(int i=0;i<pointer;i++){
	glColor3f(0,0,0);
	int_str(nodenum,num);
	nodenum++;
	bitmap_output(oldx[i][0]-5,oldx[i][1]-6,num,GLUT_BITMAP_TIMES_ROMAN_24);
	}



	//EDGE DRAWING


	delay();
	glLineWidth(7.0);
	for(int i=0;i<pointer-1;i++){
	/*glColor3f(0.0,0.0,1.0);


	glBegin(GL_LINES);
	glVertex2i(oldx[t[i][0]][0],oldx[t[i][0]][1]);
	glVertex2i(oldx[t[i][1]][0],oldx[t[i][1]][1]);
	glEnd();
	delay();
	glFlush();//glutSwapBuffers();*/
	// glutPostRedisplay();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2i(oldx[t[i][0]][0],oldx[t[i][0]][1]);
	glVertex2i(oldx[t[i][1]][0],oldx[t[i][1]][1]);
	delay();
	glEnd();
	/*int temp;
	char* cst = new char[5];
	glColor3f(0.0,1.0,0.0);
	for(int i=0;i<lpointer-1;i++){
		temp=costmatrix[t[i][0]][t[i][1]];
		itoa(temp,cst,10);
		bitmap_output((oldx[t[i][0]][0]+oldx[t[i][1]][0])/2-15,(oldx[t[i][0]][1]+oldx[t[i][1]][1])/2+8,cst,GLUT_BITMAP_TIMES_ROMAN_24);
	}*/
	glFlush();//glutSwapBuffers();
	}   

	
}

//This is callback function called by OpenGL 
void display(){
	nodenum=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.2,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,width,0,height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(load<800 && found==0){
			//glColor3f(1.0,1.0,1.0);
			//bitmap_output(100,325,"LOADING",GLUT_BITMAP_HELVETICA_18);
		    loadpage();
		}
	else if(load<800 && found==1){
	        glColor3f(1,1,1.0);
			bitmap_output(100,325,"CALCULATING",GLUT_BITMAP_HELVETICA_18);
		    loadpage();
	}

	else if(!start){
		if(enterpressed)
		{
		   instruction_page();
		   if(show_algorithm){
		     algorithm();
		   /*  if(back){
				 show_algorithm=false;
			 }*/
		}
		}
		else{
		glLineWidth(25);
		introduction_page();
		}	
	}
	
	
	else if(start){
			if(!found){
				draw_instructions();
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
	//blinking_lines();
	}
	}
	
	glFlush();//glutSwapBuffers();
}

//this is reshape callback function called by OpenGL whenever window is resized
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


//this function takes cost input from user during edge drawing
void input(){
	int posi=-1,posj=-1;
	int cost;
	int center_difference_error = 100;
	for(int i=0;i<pointer;i++){
		if(oldx[i][0]>=(linepoints[0][0]-center_difference_error)&&oldx[i][0]<=(linepoints[0][0]+center_difference_error)){
			if(oldx[i][1]>=(linepoints[0][1]-center_difference_error)&&oldx[i][1]<=(linepoints[0][1]+center_difference_error)){
		       posi=i;
			   break;}
	    }
	}
	for(int i=0;i<pointer;i++){
		if(oldx[i][0]>=(linepoints[1][0]-center_difference_error)&&oldx[i][0]<=(linepoints[1][0]+center_difference_error)){
			if(oldx[i][1]>=(linepoints[1][1]-center_difference_error)&&oldx[i][1]<=(linepoints[1][1]+center_difference_error)){
		       posj=i;
			break;
			}
	    }
	}
	if((posi==posj)||posi==-1||posj==-1){
		glColor3f(1.0,0.0,0.0);
		bitmap_output(20,50,"Invalid node",GLUT_BITMAP_HELVETICA_18);
		glFlush();//glutSwapBuffers();
		delay();
		delay();
	lpointer--;
	}else{
	cout<<"Enter the cost:";
	cin>>cost;
	lineundostack[lpointer][0]=posi;
	lineundostack[lpointer][1]=posj;
	costmatrix[posi][posj]=costmatrix[posj][posi]=cost;
	}
}

//this is mouse callback function called by OpenGL whenever mouse event occurs
void mousefun(int button,int state,int x,int y){
	found=0;
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		if(start){
		glLoadIdentity();
		float xp=(float)x;
		float yp=height-(float)y;
		
		if(point){
		oldx[pointer][0]=xp;
		oldx[pointer++][1]=yp;
		undostack[++upointer]='p';
		}

		if(line){
			if(f==0){
			linex[lpointer][0]=xp;
			linex[lpointer][1]=yp;
			f=1;
			linepoints[0][0]=sx=xp;
			linepoints[0][1]=sy=yp;
			}
			else{
			linex[lpointer][2]=linepoints[1][0]=xp;
			linex[lpointer][3]=linepoints[1][1]=yp;
			input();
			lpointer++;
			f=0;
			sx=sy=-1;
			undostack[++upointer]='l';
			}
		}
		glutPostRedisplay();
	  }
	}
}

//this function will print matrix constructed
void printmatrix(){
	for(int i=0;i<pointer;i++){
		for(int j=0;j<pointer;j++){
		cout<<costmatrix[i][j]<<"  ";
		}
		cout<<endl;
	}
}

//this checks if the graph is connected or not
bool isconnected(){
	int count;
	for(int i=0;i<pointer;i++){
	count=0;
	for(int j=0;j<pointer;j++){
	if(costmatrix[i][j]==999)count++;
	}
	if(count>=pointer-1){
		return false;
	}
	}
	return true;
}

//this undo the drawing in the order the graph was drawn
void undo(){
	if(pointer>0&&undostack[upointer--]=='p'){
			 pointer--;
			 undone++;
	} else if(lpointer>0){
			 lpointer--;
			 push(costmatrix[lineundostack[lpointer][0]][lineundostack[lpointer][1]]);
			 costmatrix[lineundostack[lpointer][0]][lineundostack[lpointer][1]]=999;
			 costmatrix[lineundostack[lpointer][1]][lineundostack[lpointer][0]]=999;
		     undone++;
	}
}

//this redo the drawing in the order the graph was drawn
void redo(){
	if(undone){
	      if(undostack[++upointer]=='p'){
					 pointer++;
					 undone--;
		   }
		 else{
			 int  cost=pop();
		     costmatrix[lineundostack[lpointer][0]][lineundostack[lpointer][1]]=cost;
			 costmatrix[lineundostack[lpointer][1]][lineundostack[lpointer][0]]=cost;
			 lpointer++;
             undone--;
		   }
       }
}

//this will call find_spanning_tree function if graph is connected
void find(){
	if(isconnected()){
		load=0;
		find_spanning_tree();
	 }
	else
	 {
		 	glColor3f(1.0,0.0,0.0);
		bitmap_output(30,20,"Graph is not connected",GLUT_BITMAP_HELVETICA_18);
		glFlush();//glutSwapBuffers();
		delay();
		delay();
	//	cout<<"spanning tree doesn't exist"<<endl;
	 }
}

//this will select edge draw mode 
void selectedge(){
     strcpy(text,"Draw mode: Edge");
	 line=1;
     point=0;
}

//this will select node draw mode 
void selectnode(){
	strcpy(text,"Draw mode: Node");
    point=1;
	line=0;
}

//this is keyboard callback function called by OpenGL whenever keyboard event occurs
void keyboardfun(unsigned char key,int x,int y){
	sx=-1;sy=-1;
	switch(key){
	     case 13  : found=0;
			        enterpressed=true;
			        break;
	     case 's' :
		 case 'S' :found=0;
			       start=true;
			       break;
		 case 'a' :
		 case 'A' :enterpressed=false;
			       break;
	     case 'b' :
		 case 'B' :start=false;
			       show_algorithm=false;
			       back=true;
				   break;
		 
		 
		 case 'e':
		 case 'E':found=0;
			      selectedge();
			      break;
		 case 'N':
		 case 'n':found=0;
			      selectnode();
			      break;
		 
		 case 'Z':
		 case 'z':found=0;
			      undo();
				  break;
		 
		 case 'Y':
		 case 'y':found=0;
			      redo();
			      break;
		 
		 case 'D':
		 case 'd':found=0;
			      find();
			      break;
		 case 'i':
		 case 'I':
			      show_algorithm=true;
			      break;
		 case ' ':paused=!paused;
			      break;
		 case 27 :exit(0);
	}
		glutPostRedisplay();
}

//this is menu callback function called by OpenGL as menu function
void menu(int id){
	switch(id){
	case 0:find();
		   break;
	case 1:undo();
		   break;
    case 2:redo();
		   break;
    case 3:printmatrix();
		   break;
	case 4:point=1;
		   line=0;
		   strcpy(text,"Draw Mode: Node");
		   break;
    case 5:point=0;
		   line=1;
		   strcpy(text,"Draw Mode: Edge");
		   break;
	}
	glutPostRedisplay();

}

//this function calculates spanning tree using Prim's algorithm
void find_spanning_tree(){
	int k,u,v;
	int sum,min,source;
	int* p = new int[100];
	int* d = new int[100];
	int* s = new int[100];
	min=999;
	source=0;
	for(int i=0;i<pointer;i++){
	   for(int j=0;j<pointer;j++){
		   if(costmatrix[i][j]!=0 && costmatrix[i][j]<=min){
			   min=costmatrix[i][j];
			   source=i;
		   }
	}
	}

	for(int i=0;i<pointer;i++){
		d[i]=costmatrix[source][i];
		p[i]=source;
		s[i]=0;
	}
	s[source]=1;
	sum=0;
	k=0;
	for(int i=1;i<pointer;i++){
	min=999;
	u=-1;
	for(int j=0;j<pointer;j++){
		if(s[j]==0){
			if(d[j]<min){
			min=d[j];
			u=j;
			}
		}
	}
	if(u==-1)return;
	t[k][0]=u;
	t[k++][1]=p[u];
	sum=sum+costmatrix[u][p[u]];
	s[u]=1;
	for(v=0;v<pointer;v++){
		if(s[v]==0 && costmatrix[u][v]<d[v]){
		d[v]=costmatrix[u][v];
		p[v]=u;
		}
	}
	}
	if(sum>=999){
	cout<<"spanning tree doesn't exist\n";
	}else{
	totalcost=sum;
	found=1;
	}
}

//Program execution starts from here
int main(int argc,char** argv){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++)
		if(i==j){
		costmatrix[i][j]=0;
		}
		else costmatrix[i][j]=999;
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(250,50);
	glutInitWindowSize(width,height);
	glutCreateWindow("Prim's Algorithm");
	glutDisplayFunc(display);
	glutMouseFunc(mousefun);
	glutKeyboardFunc(keyboardfun);
	glutReshapeFunc(reshape);
	glutCreateMenu(menu);
	glutAddMenuEntry("Run",0);
	glutAddMenuEntry("Undo",1);
	glutAddMenuEntry("redo",2);
	glutAddMenuEntry("Draw node",4);
	glutAddMenuEntry("Draw Edge",5);
	glutAddMenuEntry("Print matrix",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}


