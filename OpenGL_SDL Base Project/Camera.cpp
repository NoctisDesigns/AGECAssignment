#include "Camera.h"
#include "Constants.h"
#include <math.h>
#include "../gl/glut.h"

static Camera* instance = 0;
static float moveSpeed = 1.0f;
static float lookSpeed = 0.1f;

Camera::Camera()
{

}

Camera::~Camera()
{

}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}

	return instance;
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	forward = Vector3D
		(cos(pitch) * sin(yaw),
		 sin(pitch),
		 cos(pitch) * cos(yaw));

	right = Vector3D
		(sin(yaw - 3.14f / 2.0f),
		 0,
		 cos(yaw - 3.14f / 2.0f));

	up = Vector3D
		((right.y*forward.z) - (right.z*forward.y),
		 (right.z*forward.x) - (right.x*forward.z),
		 (right.x*forward.y) - (right.y*forward.x));

	if (e.type == SDL_KEYDOWN)							//Event handler for key presses
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			position += forward * moveSpeed;			//Move forwards
			break;
		case SDLK_s:
			position -= forward * moveSpeed;			//Move backwards
			break;
		case SDLK_d:
			position += right * moveSpeed;				//Strafe right
			break;
		case SDLK_a:
			position -= right * moveSpeed;				//Strafe left
			break;
		case SDLK_UP:
			pitch += lookSpeed;							//Look up
			break;
		case SDLK_DOWN:
			pitch -= lookSpeed;							//Look down
			break;
		case SDLK_LEFT:
			yaw -= lookSpeed;							//Look left
			break;
		case SDLK_RIGHT:
			yaw += lookSpeed;							//Look right
			break;
		}
	}
}

void Camera::Render()
{
	Vector3D lookatPos = position + forward;
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y, lookatPos.z, up.x, up.y, up.z);
}