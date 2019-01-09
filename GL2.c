//gcc GL2.c -o 2 -I /usr/include -lglut -lGL -lGLU -lm
#include <stdio.h>
#include <GL/glut.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>


int a = 90;
double z_step = -200;
double x_step = 100;
double z_turn = 1;
double x_turn = 0;


void normalKeys(unsigned char key, int x, int y)
{
	if(key == 'a') a += 3;	
	
	else if(key == 'd') a -= 3;
	
	else if(key == 'w')
	{
		z_step += z_turn * 5; 
		x_step -= x_turn * 5;
	}
	
	else if(key == 's')
	{
		z_step -= z_turn * 5; 
		x_step += x_turn * 5;
	}
		
	
	z_turn = sin(a * M_PI / 180);
	x_turn = cos(a * M_PI / 180);

	glutPostRedisplay();
}


void reshpe(int x, int y)
{	
	int z = x;
	 
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, x/y, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void pl(void)
{	
	glLoadIdentity();
	
	gluLookAt(x_step, -250,  z_step,
			  x_step - x_turn, -250,  z_step + z_turn,
			  0, 1, 0
	);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
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
	
	glTranslatef(-60, 0, -400);
	
	
	glBegin(GL_POLYGON);
	  glColor3f(0.0, 0.1, 0.8);
	  glVertex3f(-80, -250,  400);
	  glVertex3f(-80, -300,  400);
	  glVertex3f(-70, -300,  400);
	  glVertex3f(-70, -250,  400);
	glEnd();
	
	glutSwapBuffers();
}


int main(int argc, char* argv[])
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Awesome Cube");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(pl);
	glutReshapeFunc(reshpe);
	glutKeyboardFunc(normalKeys);
	
	glutMainLoop();

	int s;
}
