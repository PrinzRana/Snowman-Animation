#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glut.h"

float theta = -45.0;
int sign = 0;
int frame = 0;

class wcPt2D {
public:
	float x, y;
};

wcPt2D square[15] = { { 100,100 },{ 100,200 },{ 100,300 },{ 100,400 },{ 100,500 },{ 500,500 },{ 500,400 },{ 500,300 },
{ 500,200 },{ 500,100 },{ 400,100 },{ 300,100 },{ 200,100 },{ 100,100 },{ 100,500 } };

wcPt2D star[15] = { { 300,600 },{ 250,460 },{ 100,520 },{ 240,400 },{ 140,220 },{ 180,240 },{ 220,260 },{ 260,280 },
{ 300,300 },{ 354,274 },{ 408,248 },{ 460,220 },{ 360,400 },{ 500,520 },{ 340,460 } };

wcPt2D tweenPoly[20];
float proportion = 0.0;

int numPoints = 15;

float fTranslate = 0.0; 	// Speed Of The  Translation
float  fRotate = 0.0;   	// Speed Of The Rotation
float fScale = 0.0; 	// Speed Of The Scaling

int mode;

void tween(wcPt2D source[20], wcPt2D destination[20], double proportion, wcPt2D tweenPoly[20])
{

	for (int i = 0; i < numPoints; i++)
	{
		// get the source point
		double sourceX = source[i].x;
		double sourceY = source[i].y;

		// get the destination point
		double destinationX = destination[i].x;
		double destinationY = destination[i].y;

		// get the difference between source and destination
		double differenceX = (destinationX - sourceX);
		double differenceY = (destinationY - sourceY);

		// tween point is source position + proportion
		// of distance between source and destination
		double tweenX = sourceX + (differenceX * proportion);
		double tweenY = sourceY + (differenceY * proportion);

		// create point with tween co-ordinates in tween array
		tweenPoly[i].x = tweenX;
		tweenPoly[i].y = tweenY;
	}
}

void draw_flag()
{
	glColor3f(1.0, 0.4, 0.4);
	glLineWidth(10.0);
	glBegin(GL_LINES);				//flag holder
	glVertex2i(100, 10);
	glVertex2i(100, 200);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);				//flag
	glColor3f(0, 0, 0);
	glVertex2i(100, 100);
	glColor3f(0, 1, 0);
	glVertex2i(100, 200);
	glColor3f(1, 0, 1);
	glVertex2i(200 + rand() % 20, 200 + rand() % 20);
	glColor3f(1, 1, 0);
	glVertex2i(200 + rand() % 20, 100 + rand() % 20);
	glEnd();
}

void draw_square()
{
	int i;

	glColor3f(0.0, 1.0, 0.0);	//X colour

	glBegin(GL_LINES);
	for (i = 0;i<numPoints;i++)
	{
		glVertex2i(square[i].x, square[i].y);
	}
	glEnd();
}

void draw_star()
{
	int i;
	int red = rand() % 255;
	int green = rand() % 255;
	int blue = rand() % 255;
	glColor3f(float(red) / 255.0, float(green) / 255.0, float(blue) / 255.0); //flashing colours

	glBegin(GL_LINE_LOOP);
	for (i = 0;i<numPoints;i++)
	{
		glVertex2i(star[i].x, star[i].y);
	}
	glEnd();
}

void morph_Square2Star()
{
	int i;
	int red = rand() % 255;
	int green = rand() % 255;
	int blue = rand() % 255;
	//glColor3f (float(red)/255.0, float(green)/255.0, float(blue)/255.0); //flashing colours

	glColor3f(1.0, 0.0, 0.0);
	tween(square, star, proportion, tweenPoly);

	glBegin(GL_LINE_LOOP);
	for (i = 0;i<numPoints;i++)
	{
		glVertex2i(tweenPoly[i].x, tweenPoly[i].y);
	}
	glEnd();

	proportion += 0.01;

	if (proportion >1.0) proportion = 0.0;
}

void circle(double radius, double xc, double yc)
{
	int i;
	double angle = 2 * 3.1415 / 20;	// circle is drawn using 20 line.
	double x, y;

	glBegin(GL_POLYGON);
	for (i = 0;i<20;i++)
	{
		x = radius * cos(i *angle) + xc;
		y = radius * sin(i * angle) + yc;
		glVertex2f(x, y);
	}
	glEnd();
}
void circle2(double radius, double xc, double yc)
{
	int i;
	double angle = 2 * 3.1415 / 20;	// circle is drawn using 20 line.
	double x, y;

	glBegin(GL_LINES);
	for (i = 0;i<20;i++)
	{
		x = radius * cos(i *angle) + xc;
		y = radius * sin(i * angle) + yc;
		glVertex2f(x, y);
	}
	glEnd();
}
void snowman()
{
	glColor3f(1, 1, 1);	//white colour
	circle(100, 0, 0);	//body
	circle(80, 0, 130);	//body

	glColor3f(1, 1, 1);	//white colour
	circle(50, 0, 250);	// head

	glColor3f(0, 0, 0);
	circle(10, -25, 260);	//left eye
	circle(10, 25, 260);	//right eye
	glColor3f(1.0, 0.5, 0.0);
	circle(15, 0, 240);	//nose
	glColor3f(0.3, 0.3, 0.0);
	glBegin(GL_LINE_STRIP);	//month
	glVertex2i(-25, 235);
	glVertex2i(-15, 220);
	glVertex2i(0, 215);
	glVertex2i(15, 220);
	glVertex2i(25, 235);
	glEnd();
	
	glColor3f(8.0, 8.0, 0.0);
	circle(15, 0, 180);	//buttons
	circle(15, 0, 130);
	}

void snowman2()
{
	glColor3f(1, 1, 1);	//white colour
	circle2(150, 0, 0);	//body
	circle2(80, 0, 150);	//body

	glColor3f(1, 1, 1);	//white colour
	circle2(60, 0, 260);	// head

	glColor3f(0, 0, 0);
	circle2(10, -25, 280);	//left eye
	circle2(10, 25, 280);	//right eye
	glColor3f(1.0, 0.5, 0.0);
	circle2(15, 0, 260);	//nose
	glColor3f(0.3, 0.3, 0.0);
	glBegin(GL_LINE_STRIP);	//month
	glVertex2i(-25, 255);
	glVertex2i(-15, 240);
	glVertex2i(0, 235);
	glVertex2i(15, 240);
	glVertex2i(25, 255);
	glEnd();
	glColor3f(0.5, 0.0, 0.2);
	circle2(7, -25, 255);		///left cheek
	circle2(7, 25, 255);		//right cheek

	glColor3f(0.3, 0.3, 0.0);
	circle2(15, 0, 180);	//buttons
	circle2(15, 0, 130);
}

void init(void)
{
	glClearColor(0.5, 0.0, 1.0, 0.0);

	/* initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200.0, 800, -200.0, 800);

}

void renderSpacedBitmapString(float x, float y, void *font, char *string) {
	char *c;
	int x1 = x;
	for (c = string; *c != '\0'; c++) {
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c);
	}
}

void draw_text()
{
	int red = rand() % 255;
	int green = rand() % 255;
	int blue = rand() % 255;
	glColor3f(float() / 255.0, 255.0, 255.0); //flashing colours

	renderSpacedBitmapString(70, 600, GLUT_BITMAP_TIMES_ROMAN_24, "Artificial Snow Available");
	renderSpacedBitmapString(100, 300, GLUT_BITMAP_TIMES_ROMAN_24, "At Snow Supermarket");
}

void snowing()
{
	glColor3f(0.9, 0.9, 0.9);

	glPointSize(7);
	glBegin(GL_POINTS);
	glVertex2i(rand() % 500, rand() % 500);
	glVertex2i(rand() % 500, rand() % 500);
	glVertex2i(rand() % 500, rand() % 500);
	glVertex2i(rand() % 500, rand() % 500);
	glEnd();
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glEnd();
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glVertex2i(rand() % 1000, rand() % 1000);
	glEnd();
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(rand() % 1000 - 200, rand() % 1000 - 200);
	glVertex2i(rand() % 1000 - 200, rand() % 1000 - 200);
	glVertex2i(rand() % 1000 - 200, rand() % 1000 - 200);
	glVertex2i(rand() % 1000 - 200, rand() % 1000 - 200);
	glEnd();

}

void display(void)
{
	/* clear all pixels  */
	int red = rand() % 255;
	int green = rand() % 255;
	int blue = rand() % 255;

	glClear(GL_COLOR_BUFFER_BIT);

	frame++;
	glLineWidth(20.0);
	snowing();
	
	if ((frame >= 0) && (frame<50))	// Scene 1.
	{
		draw_text();
	}

	if ((frame>=50) && (frame <= 150))	// Scene 2,
	{
		snowman();
	}

	if ((frame>150) && (frame <= 350))	// Scene 3
	{
		glPushMatrix();
		glScalef(fScale, fScale, 1);
		glTranslatef(500, 500, 0);
		snowman2();				//Scaling flag.
		draw_flag();
		glPopMatrix();
		
	}
	if ((frame>350) && (frame <= 550))	// Scene 4
	{
		morph_Square2Star();
	}

	// Scene 5

	if ((frame>550))
	{
		glPushMatrix();

		glTranslatef(fTranslate, 0, 0);
		glTranslatef(-200, -500, 0);	//scaling with reference to centre(0,400).
		glScalef(2.0, 2.0, 0);
		draw_text();
		glPopMatrix();

		glPushMatrix();
		glScalef(fScale, fScale, 1);
		glTranslatef(500, 500, 0);
		snowman2();				//Scaling flag.
		draw_flag();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(500,100, 1);
		glScalef(0.3, 0.3, 1.0);
		draw_star();
		glPopMatrix();

		if (theta >= 40.0) sign = 1;	//deciding snowman left or right to wobbling.
		if (theta <= -4500) sign = 0;

		if (sign == 0) theta = theta + 2.0;
		if (sign == 1) theta = theta - 2.0;


		glPushMatrix();
		glRotatef(theta, 0, 0, 1.0);
		snowman();

		glPopMatrix();

	}


	fTranslate += 2.0;
	fRotate += 5.0f;   	// Speed Of The Rotation
	fScale -= 0.005f;
	if (fTranslate > 250.0f) fTranslate = 0.0f;   // Reset Translation
	if (fScale < 0.5f)     fScale = 1.0f;   // Reset Scaling to 1.0f
											//if(fRotate>45.0f) fRotate=0.0f;
		glFlush();
}

void Timer(int value)
{
	if (value) glutPostRedisplay();
	glutTimerFunc(40, Timer, value);
}

void visibility(int state)
{
	switch (state)
	{
	case GLUT_VISIBLE:
		Timer(1);
		break;
	case GLUT_NOT_VISIBLE:
		Timer(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(650, 650);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Artificial Snow Advert");

	init();
	glutDisplayFunc(display);
	glutVisibilityFunc(visibility);

	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}