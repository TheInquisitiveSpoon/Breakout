// Breakout.cpp: Made by Niall Starkey, Reece Hewitson, Josh Riley, Tom Wilson.

// HEADERS:
#include <TL-Engine.h>
#include <fstream>
#include <sstream>
#include "Bat.h"
#include "Ball.h"
#include "Block.h"
#include <vector>
using namespace tle;

// FORWARD DECLARATIONS:
void LoadMap(I3DEngine* engine);
Vector GetBoardPosition(int x, int y);
void PlaceBall(Ball ball, Bat bat);
bool AreBlocksDestroyed(); //Will always show false so wont load next level right now
bool IsGameOver(int lives);
void EndGame(); //Stubbed out for use later

// ENUMS:
enum GameMode {Paused, Ready};
enum Level {One, Two, Three, Four, Five};

// STRUCTS:

// CONSTANTS:
const int blockHorizontalSpacing = 68;
const int blockVerticalSpacing = 37;
const int numberOfLevels = 4;

const float kTopScreen = 0.0f;
const float kBottomScreen = 900.0f; //Needs to be set to the bottom of the screen
const float kLeftScreen = 141.0f;//Needs to be set to where the left walls edge is
const float kRightScreen = 1139.0f;//Same but for right hand wall
const float kBallRadius = 8.0f;
const float kWidthOfBat = 86.0f;

const float kBatBallSpacer = 35.0f; //Space that should be between the bat and ball at launch

// ARRAYS:
ISprite* backdrops[numberOfLevels];
vector<Block> gameBlocks;


// KEY CODES:
EKeyCode escape = Key_Escape;
EKeyCode space = Key_Space;
EKeyCode a = Key_A;
EKeyCode d = Key_D;

// CLASSES:

// MAIN:
void main()
{
	I3DEngine* engine = New3DEngine( kTLX );
	engine->StartFullscreen();
	engine->AddMediaFolder( "./Media" );
	
	//VARIABLES:
	GameMode currentGameMode = Paused;
	Level currentLevel = One;

	int CurrentGameMode = 0;
	int lives = 3;


	//ISprite* backdrop = engine->CreateSprite("nick5.png", 0, 0, 1);

	ICamera* camera = engine->CreateCamera(kManual);

	ISprite* batSprite = engine->CreateSprite("Bat.png", 597, 875);
	Bat bat(batSprite);

	ISprite* ballSprite = engine->CreateSprite("tinyball.png", 632, 850);
	Ball ball(ballSprite);
	
	IFont* myFont = engine->LoadFont("Ariel");

	ISprite* leftWall = engine->CreateSprite("metal wall.png");
	ISprite* rightWall = engine->CreateSprite("metal wall right.png", 1139, 0);

	LoadMap(engine);

	engine->Timer();
	// MAIN:
	while (engine->IsRunning())
	{
		engine->DrawScene();
		float frameTime = engine->Timer();
		myFont->Draw(to_string((int)(1.0f/frameTime)), 100, 100, kBlack, kCentre);
		///Frame Constants
		Vector ballPosition = ball.GetPosition();
		Vector batPosition = bat.GetPosition();

		///Keyboard inputs
		if (engine->KeyHit(escape))
		{
			engine->Stop();
		}

		

		


		///Make bat and ball follow each other
		if (currentGameMode == Paused)
		{
			if (engine->KeyHeld(a))
			{
				bat.AccelerateLeft();
				ball.AccelerateLeft();
			}
			if (engine->KeyHeld(d))
			{
				bat.AccelerateRight();
				ball.AccelerateRight();
			}
			///Make sure bat stays in bounds
			if (batPosition.X < kLeftScreen || batPosition.X + 86.0f>kRightScreen)
			{
				bat.ReverseX();
				ball.ReverseX();
			}

			ball.ApplyDrag();

			if (engine->KeyHit(space))
			{
				currentGameMode = Ready;
				ball.Launch();
			} 

		}
		
		
		if (currentGameMode == Ready)
		{
			///Playing keyboard inputs
			if (engine->KeyHeld(a))
			{
				bat.AccelerateLeft();

			}
			if (engine->KeyHeld(d))
			{
				bat.AccelerateRight();
			}

			///Collisions with walls
			if (ballPosition.Y >= kBottomScreen)
			{
				ball.Stop();
				if (IsGameOver(lives))
				{
					lives--;
					PlaceBall(ball, bat);
					currentGameMode = Paused;
				}
				else
				{
					EndGame();
				}
			}

			if (ballPosition.X<kLeftScreen || ballPosition.X + (kBallRadius * 2)>kRightScreen)
			{
				ball.ReverseX();
			}
			if (ballPosition.Y <= kTopScreen)
			{
				ball.ReverseY();
			}

			///Make sure bat stays in bounds
			if (batPosition.X < kLeftScreen || batPosition.X + 86.0f>kRightScreen)
			{
				bat.ReverseX();
			}

			///Collisions with blocks

			for (int i = 0; i < gameBlocks.size(); i++)
			{
				gameBlocks[i].CheckCollision(ball, engine);
			}

			///Collision with bat

			ball.CheckBatCollision(batPosition);

			///Check whether all blocks have been destroyed

			if (AreBlocksDestroyed())
			{
				ball.Stop();
				currentGameMode = Paused;
				PlaceBall(ball, bat);
			}

		}

		bat.ApplyDrag();
		ball.Move(frameTime);
		bat.Move(frameTime);
		
	}

	engine->Delete();
}
// FUNCTIONS:

void PlaceBall(Ball ball, Bat bat)
{
	Vector batPos = bat.GetPosition();
	batPos.Y -= kBatBallSpacer;
	batPos.X += (kWidthOfBat / 2.0f);
	ball.SetPosition(batPos);
	return;
}

void LoadMap(I3DEngine* engine)
{
	string line;
	ifstream infile;
	infile.open("map.txt");

	while (!infile.eof())
	{
		getline(infile, line);
		string read = "";
		int spaceCount = 0;
		int xPosition = 0;
		int yPosition = 0;
		BlockStates state;

		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ')
			{
				if (spaceCount == 0)
				{
					spaceCount++;
					xPosition = stoi(read);
					read = "";
				}
				else
				{
					spaceCount = 0;
					yPosition = stoi(read);
					read = "";
				}
			}
			else if (i == line.length() - 1)
			{
				read += line[i];
				state = static_cast<BlockStates>(stoi(read));
				spaceCount;
				Vector pos = GetBoardPosition(xPosition, yPosition);
				Block block = Block(engine, state, pos);
				gameBlocks.push_back(block);
				read = "";
			}
			else
			{
				read += line[i];
			}
		}
	}
	infile.close();
}

Vector GetBoardPosition(int x, int y)
{
	return Vector{ static_cast<float>(x*blockHorizontalSpacing +165) , static_cast<float>(y*blockVerticalSpacing) };
}

bool AreBlocksDestroyed() //Will always show false so wont load next level right now
{
	bool allDestroyed = true;

	for (int i = 0; i < gameBlocks.size(); i++)
	{
		if (gameBlocks[i].GetBlockstatate() != Dead)
		{
			allDestroyed = false;
		}
	}
	return allDestroyed;
}

bool IsGameOver(int lives)
{
	if (lives >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EndGame() //Stubbed out for use later
{
	return;
}