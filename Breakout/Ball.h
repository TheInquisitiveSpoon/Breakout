#pragma once
#include <TL-Engine.h>
#include "Vector.h"

using namespace tle;

class Ball
{
private:
	ISprite* Sprite;
	Vector Movement; 
	const float maxSpeed = 800.0f;
	const float ballMovementSpeed = 20.0f;
	const float dragCoefficient = 0.005f;


	const float batBaseLaunchSpeed = -240.0f;


public:
	Ball(ISprite* sprite);
	~Ball();

	void Move(float frameTime);

	ISprite* GetSprite();
	void SetSprite(ISprite* Sprite);

	Vector GetMovement();
	void SetMovement(Vector movement);

	Vector GetPosition();
	void SetPosition(Vector position);

	void Launch();
	void ReverseX();
	void ReverseY();
	void Stop();
	void BounceOffBlock();
	void BounceOffBat();
	void BounceAtAngle(Vector colEntityPos, float height, float width);
	void CheckBatCollision(Vector batPosition);

	void AccelerateLeft();
	void AccelerateRight();
	void ApplyDrag();
};

