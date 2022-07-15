/************************************************************************/
/*       Program�@�@"c9-1.c"                                            */
/*                                                                      */
/*       Copyright (c) 2003 by Kiyotaka Kato and Takefumi Hayashi       */
/*                       All rights reserved                            */
/*       And modified by Miyachi 2016                                   */
/*                                                                      */
/************************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "read_bitmap.h"
#define KEY_ESC 27
#define imageWidth 8
#define imageHeight 8
//#define ymove 10
//#define size 5

int ReadBitMapData();
void polarview( void );
void resetview( void );
void read_file1( void );
void read_file2(void);
unsigned char *image;

int xBegin = 0, yBegin = 0;
int mButton;
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 200.0, fovy = 60.0;
int tnum;
unsigned char *r1,*g1,*b1;
float* x, * y, * z;
float* nx, * ny, * nz;
int width,height;
float xpoint = 7.5, ypoint = 7.5, zpoint = 7.5;
float xmove = -23.0, xmove2 = -8, xmove3 = 7, xmove4 = 22;
float ymove = -5.5, ymove2 = 9.5 ;
float zmove = 4.9;
FILE *fp1;
FILE* fp2;


void initTexture(void);

void display(void)
{
    float diffuse[] = {(double)132/256, (double)51/256, (double)31/256, 1.0};  //�g�U���ː���
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	int i;
				 
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	polarview();
    glEnable( GL_DEPTH_TEST );
	glEnable(GL_TEXTURE_2D);

	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
    glEnable( GL_LIGHTING );
	glBindTexture(GL_TEXTURE_2D,3);
	/*��������1��(����)*/
	glBegin(GL_QUADS);
		glTexCoord2f(0.33,0.0); glVertex3f(-xpoint + xmove, -ypoint + ymove,-zpoint + zmove);
		glTexCoord2f(0.33,0.5); glVertex3f(-xpoint + xmove, ypoint + ymove,-zpoint + zmove);
		glTexCoord2f(0.0,0.5); glVertex3f(xpoint + xmove, ypoint + ymove,-zpoint + zmove);
		glTexCoord2f(0.0,0.0); glVertex3f(xpoint + xmove, -ypoint + ymove,-zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(1.0,0.5); glVertex3f(-xpoint + xmove,-ypoint + ymove,zpoint + zmove);
		glTexCoord2f(1.0,1.0); glVertex3f(-xpoint + xmove,ypoint + ymove,zpoint + zmove);
		glTexCoord2f(0.68,1.0); glVertex3f(xpoint + xmove, ypoint + ymove, zpoint + zmove);
		glTexCoord2f(0.68,0.5); glVertex3f(xpoint + xmove,-ypoint + ymove, zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.34,0.0); glVertex3f(-xpoint + xmove,-ypoint + ymove,-zpoint + zmove);
		glTexCoord2f(0.66,0.0); glVertex3f(-xpoint + xmove,-ypoint + ymove, zpoint + zmove);
		glTexCoord2f(0.66,0.5); glVertex3f(xpoint + xmove,-ypoint + ymove, zpoint + zmove);
		glTexCoord2f(0.34,0.5); glVertex3f(xpoint + xmove,-ypoint + ymove,-zpoint + zmove);
	glEnd();

	/*glBegin(GL_QUADS);
		glTexCoord2f(0.33,1.0); glVertex3f(-xpoint + xmove, ypoint + ymove,-zpoint + zmove);
		glTexCoord2f(0.33,0.5); glVertex3f(-xpoint + xmove, ypoint + ymove, zpoint + zmove);
		glTexCoord2f(0.66,0.5); glVertex3f(xpoint + xmove, ypoint + ymove, zpoint + zmove);
		glTexCoord2f(0.66,1.0); glVertex3f(xpoint + xmove, ypoint + ymove,-zpoint + zmove);
	glEnd();*/

	/*glBegin(GL_QUADS);//����(�E)
		glTexCoord2f(1.0,0.0); glVertex3f(xpoint + xmove,-ypoint + ymove,-zpoint + zmove);//�E��
		glTexCoord2f(1.0,0.5); glVertex3f(xpoint + xmove, ypoint + ymove,-zpoint + zmove);//�E��
		glTexCoord2f(0.69,0.5); glVertex3f(xpoint + xmove, ypoint + ymove, zpoint + zmove);//����
		glTexCoord2f(0.69,0.0); glVertex3f(xpoint + xmove,-ypoint + ymove, zpoint + zmove);//����
	glEnd();*/

	glBegin(GL_QUADS);//���ʔ�
		glTexCoord2f(0.663,0.5); glVertex3f(-xpoint + xmove,-ypoint + ymove,-zpoint + zmove);//�E��
		glTexCoord2f(0.663,1.0); glVertex3f(-xpoint + xmove, ypoint + ymove,-zpoint + zmove);//�E��
		glTexCoord2f(0.333,1.0); glVertex3f(-xpoint + xmove, ypoint + ymove, zpoint + zmove);//����
		glTexCoord2f(0.333,0.5); glVertex3f(-xpoint + xmove,-ypoint + ymove, zpoint + zmove);//����
	glEnd();
	/*�����܂�1��(����)*/

	/*��������2��(�E��)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove, -ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove, -ypoint + ymove2, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove, -ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove, -ypoint + ymove2, zpoint + zmove);
	glEnd();

	//glBegin(GL_QUADS);
	//glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove, -ypoint + ymove2, -zpoint + zmove);
	//glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove, -ypoint + ymove2, -zpoint + zmove);
	//glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove, ypoint + ymove2, -zpoint + zmove);
	glEnd();

	/*glBegin(GL_QUADS);//����(�E)
	glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();*/

	glBegin(GL_QUADS);//���ʔ�
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();
	/*�����܂�2��(�E��)*/

	/*��������3��(���㒆)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove2, -ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove2, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove2, -ypoint + ymove, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove2, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove2, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove2, -ypoint + ymove, zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove2, -ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove2, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove2, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove2, -ypoint + ymove, -zpoint + zmove);
	glEnd();

	/*glBegin(GL_QUADS);
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove2, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 1.0); glVertex3f(xpoint + xmove2, ypoint + ymove, -zpoint + zmove);
	glEnd();*/

	//glBegin(GL_QUADS);//����(�E)
	//glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove2, -ypoint + ymove, -zpoint + zmove);//�E��
	//glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove, -zpoint + zmove);//�E��
	//glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove, zpoint + zmove);//����
	//glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove2, -ypoint + ymove, zpoint + zmove);//����
	//glEnd();

	//glBegin(GL_QUADS);//���ʔ�
	//glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove2, -ypoint + ymove, -zpoint + zmove);//�E��
	//glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove, -zpoint + zmove);//�E��
	//glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove, zpoint + zmove);//����
	//glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove2, -ypoint + ymove, zpoint + zmove);//����
	//glEnd();
	/*�����܂�3��(���㒆)*/

	/*��������4��(�E�㒆)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove2, -ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove2, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove2, -ypoint + ymove2, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove2, -ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove2, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove2, -ypoint + ymove2, zpoint + zmove);
	glEnd();

	//glBegin(GL_QUADS);
	//glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove2, -ypoint + ymove2, -zpoint + zmove);
	//glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove2, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove2, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove2, -ypoint + ymove2, -zpoint + zmove);
	//glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove2, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove2, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove2, -zpoint + zmove);
	glEnd();

	//glBegin(GL_QUADS);//����(�E)
	//glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove2, -ypoint + ymove2, -zpoint + zmove);//�E��
	//glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove2, -zpoint + zmove);//�E��
	//glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove2, ypoint + ymove2, zpoint + zmove);//����
	//glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove2, -ypoint + ymove2, zpoint + zmove);//����
	//glEnd();

	/*glBegin(GL_QUADS);//���ʔ�
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove2, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove2, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove2, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();*/
	/*�����܂�4��(�E�㒆)*/

	/*��������5��(������)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove3, -ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove3, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove3, -ypoint + ymove, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove3, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove3, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove3, -ypoint + ymove, zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove3, -ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove3, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove3, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove3, -ypoint + ymove, -zpoint + zmove);
	glEnd();

	/*glBegin(GL_QUADS);
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove3, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 1.0); glVertex3f(xpoint + xmove3, ypoint + ymove, -zpoint + zmove);
	glEnd();*/

	/*glBegin(GL_QUADS);//����(�E)
	glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove3, -ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove, zpoint + zmove);//����
	glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove3, -ypoint + ymove, zpoint + zmove);//����
	glEnd();

	glBegin(GL_QUADS);//���ʔ�
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove3, -ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove, zpoint + zmove);//����
	glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove3, -ypoint + ymove, zpoint + zmove);//����
	glEnd();*/
	/*�����܂�5��(������)*/

	/*��������6��(�E����)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove3, -ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove3, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove3, -ypoint + ymove2, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove3, -ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove3, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove3, -ypoint + ymove2, zpoint + zmove);
	glEnd();

	//glBegin(GL_QUADS);
	//glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove3, -ypoint + ymove2, -zpoint + zmove);
	//glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove3, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove3, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove3, -ypoint + ymove2, -zpoint + zmove);
	//glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove3, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove3, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove2, -zpoint + zmove);
	glEnd();

	/*glBegin(GL_QUADS);//����(�E)
	glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove3, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove3, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove3, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();

	glBegin(GL_QUADS);//���ʔ�
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove3, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove3, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove3, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();*/
	/*�����܂�6��(�E����)*/

	/*��������7��(����)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove4, -ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove4, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove4, -ypoint + ymove, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove4, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove4, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove4, -ypoint + ymove, zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove4, -ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove4, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove4, -ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove4, -ypoint + ymove, -zpoint + zmove);
	glEnd();

	/*glBegin(GL_QUADS);
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove4, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove, zpoint + zmove);
	glTexCoord2f(0.66, 1.0); glVertex3f(xpoint + xmove4, ypoint + ymove, -zpoint + zmove);
	glEnd();*/

	glBegin(GL_QUADS);//����(�E)
	glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove4, -ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove, zpoint + zmove);//����
	glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove4, -ypoint + ymove, zpoint + zmove);//����
	glEnd();

	/*glBegin(GL_QUADS);//���ʔ�
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove4, -ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove, -zpoint + zmove);//�E��
	glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove, zpoint + zmove);//����
	glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove4, -ypoint + ymove, zpoint + zmove);//����
	glEnd();*/
	/*�����܂�7��(����)*/

	/*��������8��(�E��)*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.33, 0.0); glVertex3f(-xpoint + xmove4, -ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove4, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.0, 0.0); glVertex3f(xpoint + xmove4, -ypoint + ymove2, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.5); glVertex3f(-xpoint + xmove4, -ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(1.0, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 1.0); glVertex3f(xpoint + xmove4, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.68, 0.5); glVertex3f(xpoint + xmove4, -ypoint + ymove2, zpoint + zmove);
	glEnd();

	//glBegin(GL_QUADS);//��
	//glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove4, -ypoint + ymove2, -zpoint + zmove);
	//glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove4, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove4, -ypoint + ymove2, zpoint + zmove);
	//glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove4, -ypoint + ymove2, -zpoint + zmove);
	//glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.34, 0.0); glVertex3f(-xpoint + xmove4, ypoint + ymove2, -zpoint + zmove);
	glTexCoord2f(0.66, 0.0); glVertex3f(-xpoint + xmove4, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.66, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove2, zpoint + zmove);
	glTexCoord2f(0.34, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove2, -zpoint + zmove);
	glEnd();

	glBegin(GL_QUADS);//����(�E)
	glTexCoord2f(1.0, 0.0); glVertex3f(xpoint + xmove4, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(1.0, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.69, 0.5); glVertex3f(xpoint + xmove4, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.69, 0.0); glVertex3f(xpoint + xmove4, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();

	/*glBegin(GL_QUADS);//���ʔ�
	glTexCoord2f(0.33, 0.5); glVertex3f(-xpoint + xmove4, -ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.33, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove2, -zpoint + zmove);//�E��
	glTexCoord2f(0.0, 1.0); glVertex3f(-xpoint + xmove4, ypoint + ymove2, zpoint + zmove);//����
	glTexCoord2f(0.0, 0.5); glVertex3f(-xpoint + xmove4, -ypoint + ymove2, zpoint + zmove);//����
	glEnd();*/
	/*�����܂�8��(�E��)*/


	glDisable(GL_TEXTURE_2D);

	for (i = 0;i < tnum;i++) {
		glBegin(GL_POLYGON);
		glNormal3f(nx[i], ny[i], nz[i]);
		glVertex3f(x[3 * i + 0], y[3 * i + 0], z[3 * i + 0]);
		glVertex3f(x[3 * i + 1], y[3 * i + 1], z[3 * i + 1]);
		glVertex3f(x[3 * i + 2], y[3 * i + 2], z[3 * i + 2]);
		glEnd();
	}
	
	glPopMatrix();
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	glutSwapBuffers();
}

void idle(void)  //�v���[����ǉ�
{
	elevation += 0.1;
	glutPostRedisplay();
}

void myKbd(unsigned char key, int x, int y)
{
	switch(key) {
    case KEY_ESC:
        exit( 0 );
  	default:
   		break;
	}
}

void makeImage(void)
{
	int i,j;
//	printf("width, height = %d %d\n",width,height);
	for (i = 0; i < height; i++) {
   		for (j = 0; j < width; j++) {
        	image[0+4*(j+i*width)] = (unsigned char) r1[j+width*i];			// bitmap2�ɕς�����
        	image[1+4*(j+i*width)] = (unsigned char) g1[j+width*i];			// bitmap1�̓��e��ς��Ă݂�
        	image[2+4*(j+i*width)] = (unsigned char) b1[j+width*i];
        	image[3+4*(j+i*width)] = (unsigned char) 50;
//		printf(" %d %d\n", image[i+j*width+0*width*height] ,image[i+j*width+1*width*height]); 
     	}
	}
}


void initTexture3( void)
{
unsigned char *image3[1];
int imageHeightb, imageWidthb;

	makeImage();

	glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4,width ,height,0,
								GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}


void myInit (char *progname)
{
    glutInitWindowPosition(0, 0);
	glutInitWindowSize( 500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor ((double)144/256, (double)215/256, (double)236/256, 1.0);
    glutKeyboardFunc(myKbd);
		
	resetview();
	initTexture3();
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHT0 );
}


void myReshape(int width, int height)
{
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);  //���̐ς̐ݒ�
    glMatrixMode(GL_MODELVIEW);
}


void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
	glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}


void resetview( void )
{
	distance = 12.5;//20,5
    twist = 0.0;
    elevation = -170.0;
    azimuth = -90.0;
}

void myMouse( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN) {
		mButton = button;
        xBegin = x;
        yBegin = y;
	}
}


void myMotion(int x, int y)
{
    int xDisp, yDisp;

    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch(mButton){
    case GLUT_LEFT_BUTTON:
       azimuth += (float) xDisp/2.0;
//        elevation -= (float) yDisp/2.0;
        break;
    case GLUT_MIDDLE_BUTTON:
        elevation -= (float) yDisp/2.0;
//       twist = fmod (twist + xDisp, 360.0);
        break;
    case GLUT_RIGHT_BUTTON:
        distance -= (float) yDisp/40.0;
        break;
    }
    xBegin = x;
    yBegin = y;
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);


	printf(" argc = %d\n", argc);
	if( argc < 2 ) {
		fprintf(stderr," Usage: command <bitmap filename>\n");
		exit(-1);
	}

	fp1 = fopen(argv[1],"rb");
	fp2 = fopen(argv[2], "r");
	printf(" file = %s\n", argv[1]);
	if( fp1 == 0 ) { // �t�@�C�����J���̂Ɏ��s
		fprintf(stderr," File open error : %s\n",argv[1]);
		exit(-1);
	} else { // ������͐���
		fprintf(stderr,"File open success : %s\n",argv[1]);
	}
	read_file1();
	read_file2();

	myInit(argv[0]);
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(myMouse);
	glutMotionFunc( myMotion );
	glutMainLoop();
}

void read_file1(){
	int i,j,k;
	unsigned int width1, height1;
	unsigned short color;
	unsigned int dumlong;
	unsigned char buf10[10];
	unsigned char buf2[2];
	unsigned char buf20[20];
	unsigned int image_start_point,header_size;
	unsigned char pad[4];

/* �P�D�w�b�_���̓ǂݎ��
	  1.1  �t�@�C���w�b�_�@14�o�C�g�̓ǂݎ�� */

// �o�C�i���̃t�@�C����ǂݎ��Ƃ��́@fread �֐����g���܂��B
//                     �������ނƂ��́@fwrite�֐����g���܂��B
// �A�X�L�[�̃t�@�C����ǂݎ��Ƃ��́@fgets�֐����g���܂��B
//  �@�@�@�@�@�@�@�@�@ �������ނƂ��́@fprintf ���������ȁA���g���܂��B
//
	fread(buf10,sizeof(unsigned char),10,fp1);  // 10byte
	fread(&image_start_point,sizeof(unsigned int),1,fp1); // 14byte
	fprintf(stderr," image start point = %d\n", image_start_point);
	//  1.2 �摜�w�b�_�̓ǂݎ��@�iimage_start_point - 14�j�o�C�g
	//  (1) �w�b�_�T�C�Y
	fread(&header_size,sizeof(unsigned int),1,fp1); //18byte
        fprintf(stderr," header_size = %ld\n", header_size);
	if( image_start_point == (14 + header_size) ) {
		fprintf(stderr," header size OK! \n");
	} else {
		fprintf(stderr," header size error \n");
		exit(-1);
	} 
	//  (2) �摜�T�C�Y�@�i���ƍ����j
	fread(&width1,sizeof(unsigned int),1,fp1); // 22byte
	fread(&height1,sizeof(unsigned int),1,fp1); //26byte
	fprintf(stderr," Width, Height = %d %d\n", width1, height1);

	r1 = (unsigned char *) malloc(width1*height1);
	g1 = (unsigned char *) malloc(width1*height1);
	b1 = (unsigned char *) malloc(width1*height1);
	image = (unsigned char *) malloc(4*width1*height1);

	width = width1;
	height = height1;

	//  (3) �Q�o�C�g��΂��i�v���[�����j
 	fread(buf2,sizeof(char),2,fp1); //28byte
	//  (4) Color �T�C�Y�@�i���̃v���O������24bit true color �̂݁j
	fread(&color,sizeof(unsigned short),1,fp1); //30byte
	if( color == 24 ) {  // 24bit true color
		fprintf(stderr," It's 24bit true color. OK! \n");
	} else {
		fprintf(stderr," Oh! No. It's not 24bit color. I hate it.\n");
		exit(-1);
	}
	//  (5) ���k�`��
	fread(&dumlong,sizeof(unsigned int),1,fp1); //34byte
	if( dumlong == 0 ) {  // �����k
		fprintf(stderr," It's non compress data. OK! \n");
	} else {
		fprintf(stderr," Oh! No. Why did you compress the image ? %d\n",dumlong);
		exit(-1);
	}

 	fread(buf20,sizeof(char),20,fp1);

	k=0;
	for(j=0;j<height1;j++){
	    for(i=0;i<width1;i++){
		fread(&b1[k],sizeof(unsigned char),1,fp1);
		fread(&g1[k],sizeof(unsigned char),1,fp1);
		fread(&r1[k],sizeof(unsigned char),1,fp1);
		k++;
	    }
	    if( (3*width)%4 != 0 ) fread(pad,sizeof(unsigned char), (4-(3*width)%4),fp1);
	}
}

void read_file2() {  //����������stl�t�@�C���ɂ��Ă̓ǂݍ��݂��s��
	int i, j, k;
	int maxi = 100000;
	char buf[10000];
	char key[64], key2[64];;
	unsigned int width1, height1;
	float xx, yy, zz;
	float nxx, nyy, nzz;

	nxx = nyy = nzz = 0.;
	tnum = 0;

	fgets(buf, 10000, fp2); // title // ��
	printf(" buf = %s\n", buf);
	sscanf(buf, "%s", key);
	if (strcmp(key, "solid") == 0) {
		printf("OK 1\n");
	}
	else {
		printf("NG 1: %s\n", key);
	}
	for (i = 0;i < maxi;i++) {
		fgets(buf, 10000, fp2); // title // ��
		sscanf(buf, "%s", key);
		if (strcmp(key, "facet") == 0) {
			//			printf("OK: %d\n",i);
		}
		else 	if (strcmp(key, "endsolid") == 0) {
			printf("Normal termination: %s\n", key);
			break;
		}
		else {
			printf("NG: %d, %s\n", i, key);
			exit(-1);
		}
		fgets(buf, 10000, fp2); // outer loop ��
		fgets(buf, 10000, fp2); // point1 ��
		fgets(buf, 10000, fp2); // point2 ��
		fgets(buf, 10000, fp2); // point3 ��
		fgets(buf, 10000, fp2); // end loop ��

		fgets(buf, 10000, fp2); // title // ��
		sscanf(buf, "%s", key);
		if (strcmp(key, "endfacet") == 0) {
			//			printf("OK end \n");
		}
		else {
			printf("NG end: %s\n", key);
			exit(-1);
		}

	}
	tnum = i;
	printf(" tnum = %d\n", tnum);
	x = (float*)malloc(3 * tnum * sizeof(float));
	y = (float*)malloc(3 * tnum * sizeof(float));
	z = (float*)malloc(3 * tnum * sizeof(float));
	nx = (float*)malloc(tnum * sizeof(float));
	ny = (float*)malloc(tnum * sizeof(float));
	nz = (float*)malloc(tnum * sizeof(float));
	rewind(fp2); // ��

	fgets(buf, 10000, fp2); // title //   // ��
	printf(" buf = %s\n", buf);
	sscanf(buf, "%s", key);
	if (strcmp(key, "solid") == 0) {
		printf("OK 1\n");
	}
	else {
		printf("NG 1: %s\n", key);
	}
	for (i = 0;i < tnum;i++) {
		fgets(buf, 10000, fp2); // title //  // ��
		sscanf(buf, "%s %s %f %f %f", key, key2, &nxx, &nyy, &nzz);
		if (strcmp(key, "facet") == 0) {
			//			printf("OK: %d\n",i);
			nx[i] = nxx;
			ny[i] = nyy;
			nz[i] = nzz;
		}
		else 	if (strcmp(key, "endsolid") == 0) {
			printf("Normal termination: %s\n", key);
			break;
		}
		else {
			printf("NG: %d, %s\n", i, key);
			exit(-1);
		}
		fgets(buf, 10000, fp2); // outer loop  // ��
		fgets(buf, 10000, fp2); // point1  // ��
		sscanf(buf, "%s %f %f %f", key, &xx, &yy, &zz);
		x[3 * i + 0] = xx;
		y[3 * i + 0] = yy;
		z[3 * i + 0] = zz;
		fgets(buf, 10000, fp2); // point2  ��
		sscanf(buf, "%s %f %f %f", key, &xx, &yy, &zz);
		x[3 * i + 1] = xx;
		y[3 * i + 1] = yy;
		z[3 * i + 1] = zz;
		fgets(buf, 10000, fp2); // point3  ��
		sscanf(buf, "%s %f %f %f", key, &xx, &yy, &zz);
		x[3 * i + 2] = xx;
		y[3 * i + 2] = yy;
		z[3 * i + 2] = zz;
		fgets(buf, 10000, fp2); // end loop  ��

		fgets(buf, 10000, fp2); // title //  ��
		sscanf(buf, "%s", key);
		if (strcmp(key, "endfacet") == 0) {
			//			printf("OK STL data was stored \n");
		}
		else {
			printf("NG end: %s\n", key);
			exit(-1);
		}

	}
	printf("OK STL data was stored \n");

}

