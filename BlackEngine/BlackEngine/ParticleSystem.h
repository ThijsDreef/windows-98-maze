#pragma once
#include "MessageHandler.h"
#include "Matrix.h"
#include "Window.h"
#include "Camera.h"
struct particle
{
	Vec3<float> pos;
	Vec3<float> vel;
	int lifeTime;
};
class ParticleSystem : public Object
{
private:
	bool particleStorm;
	particle particles[10000];
	Matrix<float> matrices[10000];
	Camera * billBoard;
	Object * spawnLocation;
public:
	ParticleSystem(MessageHandler * instance, Camera * objectToFace, Object * objectToSpawnFrom);
	~ParticleSystem();
	void handleMessage(Message * msg);
	void renderRequest();
};

