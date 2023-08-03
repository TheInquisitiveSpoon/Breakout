#include "Block.h"
#include "Ball.h"
#include <TL-Engine.h>

using namespace tle;

float kBlockHeight = 32.0f;
float kBlockWidth = 64.0f;
float kRadiusOfBall = 8.0f;

Block::Block(I3DEngine* engine, BlockStates blockState, Vector pos)
{
	BlockState = blockState;
	Sprite = engine->CreateSprite(fileNames[BlockState], pos.X, pos.Y);
}


Block::~Block()
{

}

BlockStates Block::GetBlockstatate()
{
	return BlockState;
}

void Block::SetBlockstate(BlockStates blockstate)
{
	BlockState = blockstate;
	return;
}

ISprite* Block::GetSprite()
{
	return Sprite;
}

void Block::SetSprite(ISprite * sprite)
{
	Sprite = sprite;
	return;
}

Vector Block::GetPostion()
{
	Vector vector;
	vector.X = Sprite->GetX();
	vector.Y = Sprite->GetY();
	return vector;
}

bool Block::CheckCollision(Ball& ball, I3DEngine* engine)
{																						  
	Vector blockPosition = Vector(Sprite->GetX(), Sprite->GetY());						  
	Vector ballPosition = ball.GetPosition();
																						  
	float minX = blockPosition.X - kRadiusOfBall;							  
	float maxX = blockPosition.X + kBlockWidth + kRadiusOfBall;
	float minZ = blockPosition.Y - kRadiusOfBall;
	float maxZ = blockPosition.Y + kBlockHeight + kRadiusOfBall;
																						  
	if (ballPosition.X > minX && ballPosition.X < maxX && ballPosition.Y > minZ && ballPosition.Y < maxZ)
	{
		ball.ReverseY();
		ball.BounceAtAngle(blockPosition, kBlockHeight, kBlockWidth);
		BlockHit(blockPosition, engine);
		return true;
	}																					  
																						  
																						  
	return false;
}

void Block::BlockHit(Vector blockPosition, I3DEngine* engine)
{
	DecrementBlockState();
	if (BlockState != 0)
	{
		Sprite->SetPosition(-400.0f, -400.0f);
		Sprite = engine->CreateSprite(fileNames[BlockState], blockPosition.X, blockPosition.Y);
	}
	else 
	{
		Sprite->SetPosition(-400.0f, -400.0f);
	}
	
	return;
}

void Block::DecrementBlockState()
{
	switch (BlockState)
	{
	case Rainbow:
		BlockState = Dark_Blue;
		return;
	case Dark_Blue:
		BlockState = Red;
		return;
	case Red:
		BlockState = Light_Blue;
		return;
	case Light_Blue:
		BlockState = Yellow;
		return;
	case Yellow:
		BlockState = Green;
		return;
	case Green:
		BlockState = Purple;
		return;
	case Purple:
		BlockState = Dead;
		return;
	case Dead:
		BlockState = Rainbow;
		return;
	}
}
