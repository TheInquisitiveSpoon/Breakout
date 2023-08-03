#pragma once
#include <TL-Engine.h>
#include "Vector.h"
#include "Ball.h"
#include <vector>

using namespace tle;

enum BlockStates
{
	Dead,
	Purple,
	Green,
	Yellow,
	Light_Blue,
	Red,
	Dark_Blue,
	Rainbow
};

class Block
{
	string fileNames[8] =
	{
		"empty",
		"block1.png",
		"block2.png",
		"block3.png",
		"block4.png",
		"block5.png",
		"block6.png",
		"block7.png"
	};
	BlockStates BlockState;
	ISprite* Sprite;

public:
	Block(I3DEngine* engine, BlockStates blockState, Vector pos);
	~Block();

	BlockStates GetBlockstatate();
	void SetBlockstate(BlockStates blockstate);

	ISprite* GetSprite();
	void SetSprite(ISprite* sprite);

	Vector GetPostion();

	bool CheckCollision(Ball& ball, I3DEngine* engine);

	void DecrementBlockState();

	void BlockHit(Vector blockPosition, I3DEngine* engine);
};