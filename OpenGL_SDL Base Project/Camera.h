#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include <SDL.h>

class Camera
{

public:

	Camera();
	~Camera();
	static			Camera* GetInstance();
	void			Update(float deltaTime, SDL_Event e);
	void			Render();

private:

	Vector3D position = Vector3D(0, 0, 10);
	Vector3D forward = Vector3D();
	Vector3D up = Vector3D();
	Vector3D right = Vector3D();

	float yaw = 3.14f;											//Camera variables. The yaw uses pi due to being a spherical 'path'.
	float pitch = 0.0f;
};
#endif