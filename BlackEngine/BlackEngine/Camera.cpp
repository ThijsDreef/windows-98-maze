#include "Camera.h"



Camera::Camera(MessageHandler * instance) : Object(instance)
{
	shader = "none";
	tag = "camera";
	pos.x = -2;
	pos.y = 0;
	pos.z = -2;
	cameraTranslation.translateMatrix(pos);
	cameraRotation.rotation(rot.y, Y);
	camera = camera.multiplyByMatrix(cameraRotation);
	cameraRotation.rotation(rot.z, Z);
	camera = camera.multiplyByMatrix(cameraRotation);
	cameraRotation.rotation(rot.z, X);
	camera = camera.multiplyByMatrix(cameraRotation);
	camera = camera.multiplyByMatrix(cameraTranslation);
	instance->subscribe(KEYMESSAGEGROUP, this);
	instance->subscribe(UPDATEGROUP, this);
	instance->subscribe(RENDERGROUP, this);
	instance->subscribe(MOUSEMESSAGEGROUP, this);
}


Camera::~Camera()
{
}

void Camera::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case UNKNOWN:
	{
		std::cout << "the message was unknown";
		break;
	}
	case RESOLVE:
	{
		//pos.debug();
		pos = pos.minus(oldAccel);
		break;
	}
	case UPDATE:
	{
		UpdateMessage * umsg = (UpdateMessage *)msg;
		cameraRotation.rotation(actualRot.y, Y);

		accel = cameraRotation.multiplyByVector(accel);
		accel = accel.product(umsg->dt).product(5);
		pos = pos.plus(accel);
		oldAccel = accel;
		accel.reset();
		break;
	}
	case KEY:
	{
		KeyMessage * kmsg = (KeyMessage*)msg;
		switch (kmsg->key)
		{
		// esx
		case 27:
		{
			actualRot.debug();
			break;
		}
		//w
		case 87:
		{
			Vec3<float> forward(0, 0, 1);
			accel = accel.plus(forward);
			break;
		}
		//a
		case 65:
		{
			Vec3<float> left(1, 0, 0);
			accel = accel.plus(left);
			break;
		}
		//d
		case 68:
		{
			Vec3<float> right(-1, 0, 0);
			accel = accel.plus(right);
			break;
		}
		//s
		case 83:
		{
			Vec3<float> backward(0, 0, -1);
			accel = accel.plus(backward);
			break;
		}
		default:
			break;
		}
		break;
	}
	case MOUSEVELMESSAGE:
	{
		MouseVelocityMessage * mvmsg = (MouseVelocityMessage*)msg;
		actualRot.x += -mvmsg->yvel * 50;
		actualRot.y += mvmsg->xvel * 50;
		break;
	}
	case RENDER:
	{
		RenderRequest * render_msg = (RenderRequest*)msg;
		render_msg->window->RequestRender(this);
		break;
	}
	default:
		break;
	}
}

void Camera::renderRequest()
{
	camera.rotation(-actualRot.x, X);
	cameraRotation.rotation(-actualRot.y, Y);
	camera = camera.multiplyByMatrix(cameraRotation);
	cameraTranslation.translateMatrix(pos);
	camera = camera.multiplyByMatrix(cameraTranslation);


	GraphicResourceManagement::getInstance()->setCameraMatrix(camera);

}
