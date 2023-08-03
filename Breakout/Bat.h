#pragma once
#include <TL-Engine.h>
#include "Vector.h"

using namespace tle;

class Bat
{
	const float batMovementSpeed = 20.0f;
	const float maxSpeed = 800.0f;
	const float dragCoefficient = 0.005f;
	ISprite* Sprite;
	Vector Movement;

public:
	Bat(ISprite* sprite);
	~Bat();

	float GetMovementSpeed();

	ISprite* GetSprite();
	void SetSprite(ISprite* Sprite);

	Vector GetMovement();
	void SetMovement(Vector movement);

	Vector GetPosition();

	void Move(float frameTime);

	void AccelerateLeft();
	void AccelerateRight();
	void ReverseX();

	void ApplyDrag();


};

