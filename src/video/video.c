
/************************************************************
 * cp: video.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "video.h"
#include "renders.h"
#include "../demo/demo.h"
#include "../core/core.h"
#include <GL/glut.h>

int video_w = 640;
int video_h = 480;

static int win;

static void init();
static void idle();
static void display();
static void resize(int w, int h);
static void keypress(unsigned char key, int x, int y);
static int inited;

void video_init()
{
	// init glut
	int argc = 1;
	char * argv[] = {""};	// this sucks!!!
	glutInit(&argc, argv);

	// create render window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(video_w, video_h);
	win = glutCreateWindow("Procedural Synthesizer & Sequencer");
#ifdef __FULL_SCREEN
	glutGameModeString("800x600x24@60");
	glutEnterGameMode();
	glutSetCursor(GLUT_CURSOR_NONE);
#endif

	// bind events
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keypress);
	glutDisplayFunc(&display);
	glutIdleFunc(&init);

	// setup blank color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// setup anti-aliasing for points and lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glutMainLoop();
}

void video_close()
{
	demo_close();
#ifdef __FULL_SCREEN
	glutLeaveGameMode();
#endif
	glutDestroyWindow(win);
}

void video_view2d(float x, float y, float w, float h)
{
	glViewport(x, y, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

static void init()
{
	time_adjust(0.0f);
	glutIdleFunc(&idle);
	glutPostRedisplay();
}

static void idle()
{
	glutPostRedisplay();
}

static void display()
{
	if (ticks() > 2000 && !inited) {
		inited = 1;
		demo_init();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render_score();
	glutSwapBuffers();
	glutPostRedisplay();
}

static void resize(int w, int h)
{
	video_w = w;
	video_h = h;
}

static void keypress(unsigned char key, int x, int y)
{
	if (key == '\e') video_close();
}

