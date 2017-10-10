#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(MessageHandler * instance, Camera * objectToFace, Object * objectToSpawnFrom) : Object(instance)
{
	spawnLocation = objectToSpawnFrom;
	billBoard = objectToFace;
	shader = "particles";
	instance->subscribe(UPDATEGROUP, this);
	instance->subscribe(RENDERGROUP, this);
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case UNKNOWN:
	{
		std::cout << "the message was unknown";
		break;
	}
	case PARTICLEQUE:
	{
		Matrix<float> rotateTo;
		Matrix<float> temp;
		rotateTo.rotation(billBoard->actualRot.y, Y);
		temp.rotation(billBoard->actualRot.x, X);
		rotateTo = rotateTo.multiplyByMatrix(temp);
		temp.rotation(-billBoard->actualRot.z, Z);
		rotateTo = rotateTo.multiplyByMatrix(temp);
		for (int i = 0; i < 10000; i++)
		{
			particles[i].pos = spawnLocation->pos;
			particles[i].vel = Vec3<float>(((float)rand() / (float)RAND_MAX * 2 - 1) * 0.1f, ((float)rand() / (float)RAND_MAX * 2 - 1) * 0.1f, ((float)rand() / (float)RAND_MAX * 2 - 1) * 0.1f);
			particles[i].vel = (particles[i].vel.product(20));
			particles[i].lifeTime = 0;
		}
		particleStorm = true;
		break;
	}
	case UPDATE:
	{
		UpdateMessage * umsg = (UpdateMessage *)msg;
		if (particleStorm)
		{
			Matrix<float> scale;
			Matrix<float> rotateTo;
			Matrix<float> temp;
			rotateTo.rotation(billBoard->actualRot.y, Y);
			temp.rotation(billBoard->actualRot.x, X);
			rotateTo = rotateTo.multiplyByMatrix(temp);
			temp.rotation(billBoard->actualRot.z, Z);
			rotateTo = rotateTo.multiplyByMatrix(temp);
			for (int i = 0; i < 10000; i++)
			{
				scale.scaleMatrix(Vec3<float>( 0.2 * (1 - particles[i].lifeTime / (float)140), 0.2 * (1 - particles[i].lifeTime / (float)140), 0.2 * (1 - particles[i].lifeTime / (float)140)));
				particles[i].pos = particles[i].pos.plus(particles[i].vel.product(umsg->dt));
				matrices[i].translateMatrix(particles[i].pos);
				matrices[i] = matrices[i].multiplyByMatrix(rotateTo);
				matrices[i] = matrices[i].multiplyByMatrix(scale);
				particles[i].lifeTime++;
				if (particles[i].lifeTime > 140)
				{
					particleStorm = false;
				}
			}
		}
		break;
	}
	case LATERENDER:
	{
		if (particleStorm)
		{
			RenderRequest * render_msg = (RenderRequest*)msg;
			render_msg->window->RequestRender(this);
		}
		
		break;
	}
	default:
		break;
	}
}

void ParticleSystem::renderRequest()
{
	GraphicResourceManagement::getInstance()->setTexture("part");
	GraphicResourceManagement::getInstance()->drawModelInstanced("particle", matrices, false, 10000);
}
