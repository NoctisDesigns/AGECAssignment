#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "3DSObject.h"
#include "Camera.h"
#include "../gl/glut.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void		SetLight();
	void		SetMaterial();
	void		OutputLine(float x, float y, string text);

//--------------------------------------------------------------------------------------------------
private:
	
	float		mCurrentTime;
	float		rotation;
	Object3DS*	table;
	Object3DS*	cradle;
	Object3DS*	aniball;
	Camera*		newcamera;
};


#endif //_GAMESCREENLEVEL1_H