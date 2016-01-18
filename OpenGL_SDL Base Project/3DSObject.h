#ifndef _3DSOBJECT_H_
#define _3DSOBJECT_H_

#include "Commons.h"
#include <string>

using std::string;

class Object3DS
{

public:

	Object3DS(Vector3D startPosition, string modelFileName, int texID);
	~Object3DS(){}

	void			Update(float deltaTime);
	void			Render();

	void			loadModel();						//Load 3DS file
	void			loadTexture();						//Load texture for the model

private:

	Vector3D		mPosition;

	char			fileName[20];
	char			textureName[20];

	obj_type		object;

};
#endif