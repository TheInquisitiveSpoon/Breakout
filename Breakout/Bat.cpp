#include "Bat.h"
#include <TL-Engine.h>


Bat::Bat(ISprite* sprite)
{
	Sprite = sprite;
	Movement = Vector{ 0.0f,0.0f };
}


Bat::~Bat()
{
}

float Bat::GetMovementSpeed()
{
	return batMovementSpeed;
}

ISprite* Bat::GetSprite()
{
	return Sprite;
}

void Bat::SetSprite(ISprite* Sprite)
{
	Sprite = Sprite;
	return;
}

Vector Bat::GetMovement()
{
	return Movement;
}

void Bat::SetMovement(Vector movement)
{
	Movement = movement;
	return;
}

Vector Bat::GetPosition()
{
	return Vector(Sprite->GetX(), Sprite->GetY());
}



void Bat::Move(float frameTime)
{
	Sprite->Move(Movement.X*frameTime, Movement.Y*frameTime);
}

void Bat::AccelerateLeft()
{
	if (Movement.X > -maxSpeed)
	{
		Movement.X -= batMovementSpeed;
	}
	
	return;
}

void Bat::AccelerateRight()
{
	if (Movement.X < maxSpeed)
	{
		Movement.X += batMovementSpeed;
	}

	return;
}

void Bat::ReverseX()
{
	Movement.X = -Movement.X;
}

void Bat::ApplyDrag()
{
	Movement = Vector(Movement.X - Movement.X*dragCoefficient, Movement.Y*dragCoefficient);
	return;
}
