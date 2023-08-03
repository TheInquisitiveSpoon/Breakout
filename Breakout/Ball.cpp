#include "Ball.h"
#include <TL-Engine.h>
#include "Vector.h"

using namespace tle;


float kBallRadius = 8.0f;
float kBatWidth = 86.0f;
float kBatHeight = 26.0f;

Ball::Ball(ISprite* sprite)
{
	Sprite = sprite;
	Movement = Vector( 0.0f, 0.0f );
	return;
}


Ball::~Ball()
{
}


void Ball::Move(float frameTime)
{
	Sprite->Move(Movement.X*frameTime, Movement.Y*frameTime);
	return;
}

ISprite * Ball::GetSprite()
{
	return Sprite;
}

void Ball::SetSprite(ISprite* Sprite) 
{
	Sprite = Sprite;
}

Vector Ball::GetMovement()
{
	return Movement;
}

void Ball::SetMovement(Vector movement)
{
	Movement = movement;
	return;
}

Vector Ball::GetPosition()
{
	return Vector(Sprite->GetX(), Sprite->GetY());
}

void Ball::SetPosition(Vector position)
{
	Sprite->SetPosition(position.X, position.Y);
	return;
}

void Ball::Launch()
{
	Movement.Y = batBaseLaunchSpeed;
	return;
}

void Ball::ReverseX()
{
	Movement.X = -Movement.X;
	return;
}

void Ball::ReverseY()
{
	Movement.Y = -Movement.Y;
	return;
}

void Ball::Stop()
{
	Movement.X = 0.0f;
	Movement.Y = 0.0f;
	return;
}

void Ball::BounceOffBlock()
{
}

void Ball::BounceOffBat()
{
	Movement.Y = -Movement.Y;
	return;
}

void Ball::BounceAtAngle(Vector colEntityPos, float colEntityHeight, float colEntityWidth)
{

	Vector ballPos = GetPosition();

	float xdiff = ballPos.X - (colEntityPos.X + (colEntityWidth / 2.0f));
	float ydiff = ballPos.Y - (colEntityPos.Y + (colEntityHeight / 2.0f));

	float xRatio = xdiff / (abs(xdiff) + abs(ydiff));
	float yRatio = ydiff / (abs(xdiff) + abs(ydiff));

	SetMovement(Vector(abs(batBaseLaunchSpeed)*xRatio, abs(batBaseLaunchSpeed)*yRatio));

	return;
}
void Ball::AccelerateLeft()
{
	if (Movement.X > -maxSpeed)
	{
		Movement.X -= ballMovementSpeed;
	}

	return;
}

void Ball::AccelerateRight()
{
	if (Movement.X < maxSpeed)
	{
		Movement.X += ballMovementSpeed;
	}

	return;
}

void Ball::ApplyDrag()
{
	Movement = Vector(Movement.X - Movement.X*dragCoefficient, Movement.Y*dragCoefficient);
	return;
}


void Ball::CheckBatCollision(Vector batPosition)
{
	Vector ballPosition = Vector(Sprite->GetX(), Sprite->GetY());

	float minX = batPosition.X - kBallRadius;
	float maxX = batPosition.X + kBatWidth + kBallRadius;
	float minZ = batPosition.Y - kBallRadius;
	float maxZ = batPosition.Y + kBatHeight + kBallRadius;

	if (ballPosition.X > minX && ballPosition.X < maxX && ballPosition.Y > minZ && ballPosition.Y < maxZ)
	{
		ReverseY();
		BounceAtAngle(batPosition, kBatHeight, kBatWidth);
	}
	return;
}


