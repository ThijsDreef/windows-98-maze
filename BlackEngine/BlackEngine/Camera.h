#pragma once
#include "MessageHandler.h"
#include "GameModel.h"
#include "Matrix.h"
#include "Window.h"

class Camera : public Object
{
private:
	float offset = 2;
	Vec3<float> oldAccel;
	Vec3<float> accel;
	Matrix<float> camera;
	Matrix<float> cameraRotation;
	Matrix<float> cameraTranslation;
public:
	Vec3<float> actualRot;
	Camera(MessageHandler * instance);
	~Camera();
	void handleMessage(Message * msg);
	void renderRequest();
};

