//gcc GL2.c -o 2 -I /usr/include -lglut -lGL -lGLU -lm
#include <stdio.h>
#include <GL/glut.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#define WIDTH 400  //ширина
#define HEIGHT 400 //длинна
#define DEPTH 400  //глубина


int aY = 0; 		 	//угол поворота по y
int a = 90; 		 	//угол поворота по x z
double y_begin = -250;	//начало камеры y
double z_begin = -200;	//начало камеры z
double x_begin = 100;	//начало камеры x
double z_turn = 1;		//поворот камеры z
double x_turn = 0;		//поворот камеры z
double y_turn = 0;		//поворот камеры y



void drawing3D()
{
	//ось y
	glBegin(GL_LINES);
		glColor3f(0.4, 0.1, 0.8);
		glVertex3f(0,  400, 0);
		glVertex3f(0, -400, 0);
	glEnd();
	//ось x
	glBegin(GL_LINES);
		glColor3f(0.4, 0.1, 0.8);
		glVertex3f( 400, 0, 0);
		glVertex3f(-400, 0, 0);
	glEnd();
	//ось z
	glBegin(GL_LINES);
		glColor3f(0.4, 0.1, 0.8);
		glVertex3f(0, 0,  400);
		glVertex3f(0, 0, -400);
	glEnd();
	
	
	//плоскость пол
	glBegin(GL_POLYGON);
	  glColor3f(0.9, 1.0, 1.0);
	  glVertex3f( 200, -300,  200);
	  glVertex3f( 200, -300, -200);
	  glVertex3f(-200, -300, -200);
	  glVertex3f(-200, -300,  200);
	glEnd();
	//низ пола
	glBegin(GL_POLYGON);
	  glColor3f(0.4, 1.0, 1.0);
	  glVertex3f( 200, -300, -200);
	  glVertex3f( 200, -350, -200);
	  glVertex3f(-200, -350, -200);
	  glVertex3f(-200, -300, -200);
	glEnd();
	//
	glBegin(GL_POLYGON);
	  glColor3f(0.4, 0.5, 1.0);
	  glVertex3f(-200, -350, -200);
	  glVertex3f(-200, -300, -200);
	  glVertex3f(-200, -300,  200);
	  glVertex3f(-200, -350,  200);
	glEnd();
	//
	glBegin(GL_POLYGON);
	  glColor3f(0.3, 0.1, 1.0);
	  glVertex3f(-200, -300,  200);
	  glVertex3f(-200, -350,  200);
	  glVertex3f( 200, -350,  200);
	  glVertex3f( 200, -300,  200);
	glEnd();
	//
	glBegin(GL_POLYGON);
	  glColor3f(0.3, 0.1, 0.4);
	  glVertex3f( 200, -350,  200);
	  glVertex3f( 200, -300,  200);
	  glVertex3f( 200, -300, -200);
	  glVertex3f( 200, -350, -200);
	glEnd();
	
	
	//сыр
	glBegin(GL_POLYGON);
	  glColor3f(1.0, 0.0, 1.0);
	  glVertex3f( 80, -250, -80);
	  glVertex3f( 80, -300, -80);
	  glVertex3f(-80, -300, -80);
	  glVertex3f(-80, -250, -80);
	glEnd();
	//
	glBegin(GL_POLYGON);
	  glColor3f(0.2, 0.0, 0.7);
	  glVertex3f( 80, -250, -80);
	  glVertex3f( 80, -300, -80);
	  glVertex3f( 80, -300,  80);
	  glVertex3f( 80, -250,  80);
	glEnd();
	//
	glBegin(GL_POLYGON);
	  glColor3f(0.2, 0.5, 0.7);
	  glVertex3f( 80, -300,  80);
	  glVertex3f( 80, -250,  80);
	  glVertex3f(-80, -250, -80);
	  glVertex3f(-80, -300, -80);
	glEnd();
	//
	glBegin(GL_POLYGON);
	  glColor3f(0.1, 0.7, 0.2);
	  glVertex3f( 80, -250,  80);
	  glVertex3f( 80, -250, -80);
	  glVertex3f(-80, -250, -80);
	glEnd();
}


void keyboard_handling(unsigned char key, int x, int y)
{
	if(key == 'a')
	{ 
		a += 3;
		z_turn = sin(a * M_PI / 180);
		x_turn = cos(a * M_PI / 180);	
	}
	
	else if(key == 'd') 
	{
		a -= 3;
		z_turn = sin(a * M_PI / 180);
		x_turn = cos(a * M_PI / 180);
	}
	
	else if(key == 'w')
	{
		z_begin += z_turn * 5; 
		x_begin -= x_turn * 5;
	}
	
	else if(key == 's')
	{
		z_begin -= z_turn * 5; 
		x_begin += x_turn * 5;
	}
	
	else if(key == 'r')
	{
		aY += 3;
		y_turn = sin(aY * M_PI / 180);
		
		if(y_turn == sin(90 * M_PI / 180))
		{	
			aY -= 3;
			y_turn = sin(87 * M_PI / 180);
		}
	}
	
	else if(key == 'f')
	{
		aY -= 3;
		y_turn = sin(aY * M_PI / 180);
		
		if(y_turn == sin(-90 * M_PI / 180))
		{	
			aY += 3;
			y_turn = sin(-87 * M_PI / 180);
		}	
	}
	

	glutPostRedisplay();
}


void perspective(int w, int h)
{	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w/h, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void drawing_cursor(void)
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(0, 10, 10, 0, -1, 1); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	
	glBegin(GL_LINES);
		glColor3f(1, 1, 1); 
		glVertex2f(5, 4.8); 
		glVertex2f(5, 5.2);   
	glEnd();
	//
	glBegin(GL_LINES);
		glColor3f(1, 1, 1); 
		glVertex2f(4.8, 5); 
		glVertex2f(5.2, 5);   
	glEnd();  
}


void scene(void)
{	
	perspective(WIDTH, HEIGHT);

	glLoadIdentity();
	
	gluLookAt(x_begin, 			y_begin, 		   z_begin,
			  x_begin - x_turn, y_begin + y_turn, z_begin + z_turn,
			  0, 1, 0
	);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	drawing3D();
	
	drawing_cursor();
	
	glutSwapBuffers();
}


int main(int argc, char* argv[])
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Walk in 3D");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(scene);
	glutKeyboardFunc(keyboard_handling);
	
	glutMainLoop();
}
