#include <iostream>
#include <Timer.h>
#include <random>
#include <conio.h>
#include <thread>
#include <Game.h>

using namespace std;

void spawnMultipleApples(int spawn_amount);
void clearScreen();
void clearScreen(int lines, int width);


Timer MovementCoolDown;
Direction CurMove;
Position applePosition;
Timer InputCoolDown;
double CoolDownTime=0.04;
bool playerAteSelf=false;
bool gameExit=false;

Timer SpeedCoolDown;

namespace Game
{
	Display display(10, 10, 0, 0);
	Player player;
}

void SetPos(Position _pos, char _graphic)
{
    COORD pos;
    pos.X=_pos.x;
    pos.Y=_pos.y;
    DWORD nlength=1;
    DWORD output;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    const char graphic=_graphic;
    WriteConsoleOutputCharacter(h, &graphic, nlength, pos, &output);
}

void gameOver()
{
    playerAteSelf=true;
}

void CursorPos(short int y, short int x)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos={x,y};
    SetConsoleCursorPosition(h, pos);
}

Position Make_Pos(int y, int x)
{
    return Position(y,x);
}

void Logic()
{
    if(GetAsyncKeyState('W'))
    {
        if(Game::player.CanChangeDirect(Up)==true && Game::player.CanMoveCertainDirection(Up))
        {
            Game::player.SetPlayerDirect(Up);
            Game::player.AddTurnPoint(Up);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    else if(GetAsyncKeyState('S') && Game::player.CanMoveCertainDirection(Down))
    {
        if(Game::player.CanChangeDirect(Down)==true)
        {
            Game::player.SetPlayerDirect(Down);
            Game::player.AddTurnPoint(Down);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
	else if (GetAsyncKeyState('A') && Game::player.CanMoveCertainDirection(Left))
    {
		if (Game::player.CanChangeDirect(Left) == true)
        {
            Game::player.SetPlayerDirect(Left);
            Game::player.AddTurnPoint(Left);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    else if(GetAsyncKeyState('D') && Game::player.CanMoveCertainDirection(Right))
    {
        if(Game::player.CanChangeDirect(Right)==true && Game::player.CanMoveCertainDirection(Right))
        {
            Game::player.SetPlayerDirect(Right);
            Game::player.AddTurnPoint(Right);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    if(GetAsyncKeyState('T'))
    {
        if(InputCoolDown.Update()==false)
        {
            return;
        }
        Game::player.AddTail();
        InputCoolDown.StartNewTimer(0.2);
    }
    if(GetAsyncKeyState('Y'))
    {
        if(InputCoolDown.Update()==false)
        {
            spawnMultipleApples(3);
        }
    }
    return;
}

bool isExit()
{
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        return true;
    }else
    {
        return false;
    }
}

void selectionChangeMapSize()
{
	
}

void appleUpdate();

void spawnApple()
{
    applePosition.x=(rand() % (Game::display.GetMaxSizeX()+1))+Game::display.getStartPositionX();
    applePosition.y=(rand() % (Game::display.GetMaxSizeY()+1))+Game::display.getStartPositionY();
    appleUpdate();
}

void spawnMultipleApples(int spawn_amount)
{
    for(int x=0;x<spawn_amount;x++)
    {
        applePosition.x=(rand() % (Game::display.GetMaxSizeX()+1))+Game::display.getStartPositionX();
        applePosition.y=(rand() % (Game::display.GetMaxSizeY()+1))+Game::display.getStartPositionY();
        appleUpdate();
    }
}

void appleUpdate()
{
    Game::display.SetPos(applePosition, '@');
}

void gameLoop()
{
    Position pos(2,2);
    Game::player.SetPlayerPos(pos);
    spawnApple();
    Game::display.clearDisplay();
    Game::display.DrawBorder();
    while(isExit()==false && playerAteSelf==false)
    {
        Logic();
        Game::player.Update();
        Game::display.Update();
        appleUpdate();
        Sleep(1);
    }
    Game::player.resetTail();
    playerAteSelf=false;
    return;
}

void startGame()
{
    Timer InputCoolDown;
	int selection = 0;
	int selectionMax = 2;
    CursorPos(0,0);
    while(true)
    {
        if(GetAsyncKeyState('W'))
        {
            if(InputCoolDown.Update()==true)
            {
				selection == 0 ? selection = 2 : selection--;

                InputCoolDown.StartNewTimer(0.2);
            }
		}
		else if(GetAsyncKeyState('S'))
		{
			if (InputCoolDown.Update() == true)
			{
				selection == selectionMax ? selection = 0 : selection++;

				InputCoolDown.StartNewTimer(0.2);
			}
		}
		else if (GetAsyncKeyState(VK_RETURN))
        {
            if(InputCoolDown.Update()==true)
            {
                if(selection==0)
                {
                    clearScreen(3,10);
                    gameLoop();
                    clearScreen();
                    CursorPos(0,0);
				} else if (selection==1)
                {
					selectionChangeMapSize();
				}
				else
					return;

                InputCoolDown.StartNewTimer(0.2);
            }
        }

		clearScreen(3, 20);
		CursorPos(0, 0);

		switch (selection)
		{
		case 0:
			cout << "1.Start Game <-" << endl
				<< "2.Settings" << endl
				<< "3.Exit";
			break;
		case 1:
			cout << "1.Start Game" << endl
				<< "2.Settings <-" << endl
				<< "3.Exit";
			break;
		case 2:
			cout << "1.Start Game" << endl
				<< "2.Settings" << endl
				<< "3.Exit <-";
			break;
		default:
			return;
		}

        Sleep(1);
    }
}

void clearScreen() // Not reccomended takes a lot of time to clear this much
{
    Position pos;
    for(int y=0;y<=300;y++)
    {
        pos.y=y;
        for(int x=0;x<=300;x++)
        {
            pos.x=x;
            SetPos(pos, ' ');
        }
    }
}

void clearScreen(int lines, int width) // Pick the amount of lines, and the width of them to be cleared
{
    Position pos;
    for(int y=0;y<=lines;y++)
    {
        pos.y=y;
        for(int x=0;x<=width;x++)
        {
            pos.x=x;
            SetPos(pos, ' ');
        }
    }
}

int main()
{
    srand(time(NULL));

    CursorPos((Game::display.GetMaxSizeX()+Game::display.getStartPositionX())+2, 0);

    startGame();

    return 0;
}
