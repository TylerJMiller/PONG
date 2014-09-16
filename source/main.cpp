#include "AIE.h"
#include <iostream>
#include "Pongstuff.h"

//GLOBALS 
float fTime;
const int screenWidth = 600, screenHeight = 400;
void UpdateMainMenu(), Load(), UpdateGameState();
int score1 = 0, score2 = 0;
enum GAMESTATES
{
	MENU,
	LOAD,
	GAME,
	END
};
GAMESTATES CurrentState = LOAD;

PLAYERBAR playerone, playertwo;
BALL playball;

int main( int argc, char* argv[] )
{	
	Initialise(screenWidth, screenHeight, false, "poNg");
    SetBackgroundColour(SColour(0, 0, 0, 255));
	
    //Game Loop
    do
    {
        ClearScreen();
		fTime = GetDeltaTime();
		if (IsKeyDown(GLFW_KEY_ESCAPE))
			CurrentState = END;
		switch (CurrentState)
		{
		case MENU:
			UpdateMainMenu();
			break;
		case LOAD:
			Load();
			CurrentState = GAME;
		case GAME:
			UpdateGameState();
			break;
		case END:
			return 0;
		default:
			break;
		}
    } while(!FrameworkUpdate());

    Shutdown();
	
    return 0;
}
void UpdateMainMenu()
{

}

void Load()
{
	playerone.SetLoc(0.5f * screenWidth, 50);
	playerone.SetSize(100, 25);
	playerone.SetSpeed(300);
	playerone.SetBound(playerone.GetWidth() * 0.5f, screenWidth - (playerone.GetWidth() * 0.5f));
	playerone.SetSprite(CreateSprite("./images/player.png", playerone.GetWidth(), playerone.GetHeight(), true));
	playerone.SetKeys('Z', 'X');

	playertwo.SetLoc(0.5f * screenWidth, 350);
	playertwo.SetSize(100, 25);
	playertwo.SetSpeed(300);
	playertwo.SetBound(playerone.GetWidth() * 0.5f, screenWidth - (playerone.GetWidth() * 0.5f));
	playertwo.SetSprite(CreateSprite("./images/player.png", playerone.GetWidth(), playerone.GetHeight(), true));
	playertwo.SetKeys('Q', 'W');

	playball.SetLoc(0.5f * screenWidth, 0.5f * screenHeight);
	playball.SetSize(20, 20);
	playball.SetSpeed(-200, 75);
	playball.SetBound(playball.GetWidth() * 0.5f, screenWidth - (playball.GetWidth() * 0.5f));
	playball.SetSprite(CreateSprite("./images/ball.png", playball.GetWidth(), playball.GetHeight(), true));
}

void UpdateGameState()
{
	if (IsKeyDown(GLFW_KEY_S), IsKeyDown(GLFW_KEY_H), IsKeyDown(GLFW_KEY_I), IsKeyDown(GLFW_KEY_T))
	{
		playball.SetSprite(CreateSprite("./images/dudeguy.png", playball.GetWidth(), playball.GetHeight(), true));
	}
	playerone.Move(fTime);
	playertwo.Move(fTime);
	playball.Move(fTime);
	if (CheckBoxBox(playball.GetBox(), playerone.GetBox()) && playball.GetSpeedY() < 0)
	{
		playball.Reverse();
	}
	if (CheckBoxBox(playball.GetBox(), playertwo.GetBox()) && playball.GetSpeedY() > 0)
	{
		playball.Reverse();
	}

	//DRAW
	MoveSprite(playball.GetSprite(), playball.GetX(), playball.GetY());
	DrawSprite(playball.GetSprite());
	MoveSprite(playerone.GetSprite(), playerone.GetX(), playerone.GetY());
	DrawSprite(playerone.GetSprite());
	MoveSprite(playertwo.GetSprite(), playertwo.GetX(), playertwo.GetY());
	DrawSprite(playertwo.GetSprite());
}