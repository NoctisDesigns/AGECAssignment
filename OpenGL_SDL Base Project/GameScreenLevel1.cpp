#include "GameScreenLevel1.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <string>					//For text input
#include <sstream>					//for the HUD.
#include "../gl/glut.h"
#include "Constants.h"
#include "Camera.h"
#include "Texture2D.h"


using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	newcamera = Camera::GetInstance();

	Texture2D* tableTexture = new Texture2D();
	Texture2D* cradleTexture = new Texture2D();
	Texture2D* aniballTexture = new Texture2D();

	//Table
	tableTexture->Load("wood.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, tableTexture->GetID());
	table = new Object3DS(Vector3D(0.0f, -50.0f, -100.0f), "table.3ds", tableTexture->GetID());

	//Cradle
	cradleTexture->Load("plastic.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, cradleTexture->GetID());
	cradle = new Object3DS(Vector3D(20.0f, -10.0f, -100.0f), "cradle.3ds", cradleTexture->GetID());

	//Ball
	aniballTexture->Load("metal.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, aniballTexture->GetID());
	aniball = new Object3DS(Vector3D(15.0f, -5.0f, -100.0f), "aniball.3ds", aniballTexture->GetID());

	//Set parameters so it renders okay
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::SetLight()
{
	lighting light = 
	{
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};

	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::SetMaterial()
{
	material material =
	{
		{ 0.50f, 0.50f, 0.50f, 1.0f },
		{ 0.50f, 0.50f, 0.50f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		0.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);												//Pos to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera::GetInstance()->Render();
	table->Render();

	glPushMatrix();
	aniball->Render();
	glRotatef(90.0f, 90.0f, 0.0f, 0.0f);
	glPopMatrix();

	SetLight();
	SetMaterial();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100); 
	OutputLine(5, 95, "Use the arrowkeys to move the camera.");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	Camera::GetInstance()->Update(deltaTime, e);

	mCurrentTime += deltaTime;
	table->Update(deltaTime);
	aniball->Update(deltaTime);
}

//--------------------------------------------------------------------------------------------------