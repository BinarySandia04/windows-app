#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

float rotationSpeed = 0.2f;
GLfloat rtri = 0, rquad = 0;

int DrawGLScene(GLvoid)                             // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
	glLoadIdentity();                           // Reset The Current Modelview Matrix


	glTranslatef(1.5f, 0.0f, -7.0f);              // Move Right And Into The Screen

	glRotatef(rquad, 1.0f, 1.0f, 1.0f);            // Rotate The Cube On X, Y & Z 

	glBegin(GL_QUADS);                      // Draw A Quad
	glColor3f(0.0f, 1.0f, 0.0f);          // Set The Color To Green
	glVertex3f(1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
	glVertex3f(1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)
	glColor3f(1.0f, 0.5f, 0.0f);          // Set The Color To Orange
	glVertex3f(1.0f, -1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Bottom)
	glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Bottom)
	glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
	glVertex3f(1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
	glVertex3f(1.0f, -1.0f, 1.0f);          // Bottom Right Of The Quad (Front)
	glColor3f(1.0f, 1.0f, 0.0f);          // Set The Color To Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Back)
	glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Back)
	glVertex3f(1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Back)
	glColor3f(0.0f, 0.0f, 1.0f);          // Set The Color To Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Bottom Right Of The Quad (Left)
	glColor3f(1.0f, 0.0f, 1.0f);          // Set The Color To Violet
	glVertex3f(1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Right)
	glEnd();                            // Done Drawing The Quad

	rquad -= rotationSpeed;                       // Decrease The Rotation Variable For The Quad     ( NEW )
	return TRUE;                                // Everything Went OK
}