#include "AIE.h"
#include <iostream>
#include "Pongstuff.h"
#include <cmath>

using namespace std;

//GLOBALS 
float fTime;
const int screenWidth = 600, screenHeight = 400;
void UpdateMainMenu(), LoadGame(), UpdateGameState(), EndGame(), errytime(), QuitGame();
int score1 = 0, score2 = 0;
char *wintext;
bool displayscores = false;
float endtime = 0;
bool quitShit = false;
int oldScore;
enum GAMESTATES
{
	MENU,
	LOADGAME,
	GAME,
	END,
	QUIT
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
		if (IsKeyDown(GLFW_KEY_ESCAPE) || quitShit)
			return 0;
		errytime();
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
		case QUIT:
			QuitGame();
			break;
		default:
			break;
		}
    } while(!FrameworkUpdate());

    Shutdown();
	
    return 0;
}
void errytime()
{
	ClearScreen();
	fTime = GetDeltaTime();

	SetFont("./fonts/arial.fnt");
}
void UpdateMainMenu()
{
	if (!displayscores)
	{
		DrawString("Press I to play", 60, 350, SColour(255, 255, 255, 255));
		DrawString("Press K to Hi-Scores", 60, 250, SColour(255, 255, 255, 255));
		DrawString("Press F to be a quitter", 60, 150, SColour(255, 255, 255, 255));
	}
	if (displayscores)
	{
		DrawString("Highest speed is ", 60, 250, SColour(255, 255, 255, 255));
		char a[6];
		fstream fscores;
		fscores.open("fscores.txt", ios_base::in);
		fscores.getline(a, 6);
		fscores.close();
		DrawString(a, 272, 250, SColour(255, 255, 255, 255));

		DrawString("Old highest speed is ", 60, 200, SColour(255, 255, 255, 255));
		char ca[6];
		fstream foldscores;
		foldscores.open("foldscores.txt", ios_base::in);
		foldscores.getline(ca, 6);
		foldscores.close();
		DrawString(ca, 317, 200, SColour(255, 255, 255, 255));

		DrawString("Press L to return", 60, 150, SColour(255, 255, 255, 255));

	}
	if (IsKeyDown(GLFW_KEY_I))
		CurrentState = LOADGAME;
	if (IsKeyDown(GLFW_KEY_K) && displayscores == false)
		displayscores = true;
	else if (IsKeyDown(GLFW_KEY_L) && displayscores == true)
		displayscores = false;
	if (IsKeyDown(GLFW_KEY_F))
	{
		wintext = "NOBODY WINS";
		CurrentState = QUIT;
	}
}

void LoadGame()
{
	oldScore = ReadAsFloat();

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
	if (IsKeyDown(GLFW_KEY_KP_9))
	{
		score1 = 8;
		score2 = 8;
	}
	if (IsKeyDown(GLFW_KEY_KP_7))
	{
		oldScore = 0;
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
		if (playball.LengthSpeed() > ReadAsFloat())
		{
			char a[6];
			itoa(playball.LengthSpeed(), a, 10);
			WriteOld(ReadAsFloat());
			Write(a);
		}
		playball.SetSpeed(0, 0);
	}
	if (CheckBoxBox(playball.GetBox(), Box(0, 400, 600, 500)))
	{
		playball.SetLoc(0.5f * screenWidth, 0.5f * screenHeight);
		score1++;
		if (playball.LengthSpeed() > ReadAsFloat())
		{
			char a[6];
			itoa(playball.LengthSpeed(), a, 10);
			WriteOld(ReadAsFloat());
			Write(a);
		}
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
	//DRAWING STUFF
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
	if (oldScore < ReadAsFloat())
	{
		DrawString("New Hi-Score!", 60, 350, SColour(255, 255, 255, 255));
		DrawString("New Speed is ", 60, 300, SColour(255, 255, 255, 255));
		char a[6];
		fstream fscores;
		fscores.open("fscores.txt", ios_base::in);
		fscores.getline(a, 6);
		fscores.close();
		DrawString(a, 235, 300, SColour(255, 255, 255, 255));
		DrawString("Old Speed is ", 60, 250, SColour(255, 255, 255, 255));
		char ca[6];
		fstream foldscores;
		foldscores.open("foldscores.txt", ios_base::in);
		foldscores.getline(ca, 6);
		foldscores.close();
		DrawString(ca, 235, 250, SColour(255, 255, 255, 255));
	}
	char countDown[3];
	endtime += fTime;
	char scoreone[2], scoretwo[2];
	itoa(score1, scoreone, 10);
	itoa(score2, scoretwo, 10);
	DrawString(scoreone, 280, 0.6f * screenHeight, SColour(255, 255, 255, 255));
	DrawString("_", 300, 0.63f * screenHeight, SColour(255, 255, 255, 255));
	DrawString(scoretwo, 320, 0.6f * screenHeight, SColour(255, 255, 255, 255));
	itoa(9 - (int)endtime, countDown, 10);
	if (endtime >= 10)
	{
		score1 = 0;
		score2 = 0;
		endtime = 0;
		CurrentState = MENU;
	}
	DrawString(countDown, 0.5f * screenWidth, 0.3f * screenHeight);
	DrawString(wintext, 0.3f * screenWidth, 0.5f * screenHeight, SColour(255, 255, 255, 255));
}

void QuitGame()
{
	DrawString(wintext, 0.3f * screenWidth, 0.5f * screenHeight, SColour(255, 255, 255, 255));
	char countDown[3];
	endtime += fTime;
	itoa(5 - (int)endtime, countDown, 10);
	if (endtime > 5)
	{
		quitShit = true;
	}
	DrawString(countDown, 0.5f * screenWidth, 0.3f * screenHeight);
}