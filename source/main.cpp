#include "AIE.h"
#include <iostream>
#include "Pongstuff.h"

//GLOBALS 
float fTime;
const int screenWidth = 600, screenHeight = 400;
void UpdateMainMenu(), LoadGame(), UpdateGameState(), EndGame();
int score1 = 0, score2 = 0;
char *wintext;
bool displayscores = false;
enum GAMESTATES
{
	MENU,
	LOADGAME,
	GAME,
	END
};
GAMESTATES CurrentState = MENU;

PLAYERBAR playerone, playertwo;
BALL playball;

int main( int argc, char* argv[] )
{	
	Initialise(screenWidth, screenHeight, false, "hipster poNg");
    SetBackgroundColour(SColour(0, 0, 0, 255));
	AddFont("./fonts/arial.fnt");
    //Game Loop
    do
    {
        ClearScreen();
		fTime = GetDeltaTime();
		if (IsKeyDown(GLFW_KEY_ESCAPE))
			return 0;
		SetFont("./fonts/arial.fnt");
		switch (CurrentState)
		{
		case MENU:
			UpdateMainMenu();
			break;
		case LOADGAME:
			LoadGame();
			CurrentState = GAME;
		case GAME:
			UpdateGameState();
			break;
		case END:
			EndGame();
			break;
		default:
			break;
		}
    } while(!FrameworkUpdate());

    Shutdown();
	
    return 0;
}
void UpdateMainMenu()
{
	DrawString("Press I to play", 60, 350, SColour(255, 255, 255, 255));
	DrawString("Press K to Hi-Scores", 60, 250, SColour(255, 255, 255, 255));
	DrawString("Press F to be a quitter", 60, 150, SColour(255, 255, 255, 255));
	if (IsKeyDown(GLFW_KEY_I))
		CurrentState = LOADGAME;
	if (IsKeyDown(GLFW_KEY_K))
		displayscores = true;
	if (IsKeyDown(GLFW_KEY_F))
	{
		wintext = "NOBODY WINS";
		CurrentState = END;
	}
}

void LoadGame()
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
	playball.SetSpeed(0, 0);
	playball.SetBound(playball.GetWidth() * 0.5f, screenWidth - (playball.GetWidth() * 0.5f));
	playball.SetSprite(CreateSprite("./images/ball.png", playball.GetWidth(), playball.GetHeight(), true));
}

void UpdateGameState()
{
	if (IsKeyDown(GLFW_KEY_KP_4))
	{
		score1 = 9;
	}
	if (IsKeyDown(GLFW_KEY_KP_6))
	{
		score2 = 9;
	}
	if (IsKeyDown(GLFW_KEY_SPACE) && playball.GetSpeedY() == 0)
	{
		playball.SetSpeed(-200, 75);
		if (score1 > score2)
		{
			playball.SetSpeed(-200, -75);
		}
	}
	if (IsKeyDown(GLFW_KEY_S), IsKeyDown(GLFW_KEY_H), IsKeyDown(GLFW_KEY_I), IsKeyDown(GLFW_KEY_T))
	{
		playball.SetSprite(CreateSprite("./images/dudeguy.png", playball.GetWidth(), playball.GetHeight(), true));
		playerone.SetSprite(CreateSprite("./images/dudeguy.png", playerone.GetWidth(), playerone.GetHeight(), true));
		playertwo.SetSprite(CreateSprite("./images/dudeguy.png", playertwo.GetWidth(), playertwo.GetHeight(), true));
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
	if (CheckBoxBox(playball.GetBox(), Box(0, -100, 600, 0)))
	{
		playball.SetLoc(0.5f * screenWidth, 0.5f * screenHeight);
		score2++;
		playball.SetSpeed(0, 0);
	}
	if (CheckBoxBox(playball.GetBox(), Box(0, 400, 600, 500)))
	{
		playball.SetLoc(0.5f * screenWidth, 0.5f * screenHeight);
		score1++;
		playball.SetSpeed(0, 0);
	}
	//WINCONDITIONS
	if (score1 > 8)
	{
		wintext = "BOTTOM PLAYER WINS";
		CurrentState = END;
	}
	if (score2 > 8)
	{
		wintext = "TOP PLAYER WINS";
		CurrentState = END;
	}
	//DRAW
	if (playball.GetSpeedY() == 0)
	{
		DrawString("PRESS SPACE", 0.3f * screenWidth, 0.3f * screenHeight);
	}
	char scoreone[2], scoretwo[2];
	itoa(score1, scoreone, 10);
	itoa(score2, scoretwo, 10);
	DrawString(scoreone, 50, 0.5f * screenHeight, SColour(255, 255, 255, 255));
	DrawString(scoretwo, 550, 0.5f * screenHeight, SColour(255, 255, 255, 255));

	MoveSprite(playball.GetSprite(), playball.GetX(), playball.GetY());
	DrawSprite(playball.GetSprite());
	MoveSprite(playerone.GetSprite(), playerone.GetX(), playerone.GetY());
	DrawSprite(playerone.GetSprite());
	MoveSprite(playertwo.GetSprite(), playertwo.GetX(), playertwo.GetY());
	DrawSprite(playertwo.GetSprite());
}

void EndGame()
{
	DrawString(wintext, 0.3f * screenWidth, 0.5f * screenHeight);
}