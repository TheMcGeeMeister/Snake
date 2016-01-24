#include <iostream>
#include <Timer.h>
#include <random>
#include <conio.h>
#include <thread>
#include <Game.h>
#include <sstream>

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
	Display display(5, 10, 1, 1);
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

void settingsMenu()
{
	Timer InputCoolDown;
	int selection = 0;
	int selectionMax = 4;

	int max_y = Game::display.GetMaxSizeY();
	int max_x = Game::display.GetMaxSizeX();
	int offset_y = Game::display.getOffSetPositionY();
	int offset_x = Game::display.getOffSetPositionX();

	bool exit = false;
	bool reDraw = true;

	while (exit==false)
	{
		if (GetAsyncKeyState('W'))
		{
			if (InputCoolDown.Update() == true)
			{
				selection == 0 ? selection = selectionMax : selection--;

				reDraw = true;

				InputCoolDown.StartNewTimer(0.2);
			}
		}
		else if (GetAsyncKeyState('S'))
		{
			if (InputCoolDown.Update() == true)
			{
				selection == selectionMax ? selection = 0 : selection++;

				reDraw = true;

				InputCoolDown.StartNewTimer(0.2);
			}
		}

		if (GetAsyncKeyState('A'))
		{
			if (InputCoolDown.Update() == true)
			{
				switch (selection)
				{
				case 0:
					max_x == 0 ? max_x = 0 : max_x--; break;
				case 1:
					max_y == 0 ? max_y = 0 : max_y--; break;
				case 2:
					offset_x == 1 ? offset_x = 1 : offset_x--; break;
				case 3:
					offset_y == 1 ? offset_y = 1 : offset_y--; break;
				}
				InputCoolDown.StartNewTimer(0.2);
				reDraw = true;
			}
		}
		else if (GetAsyncKeyState('D'))
		{
			if (InputCoolDown.Update() == true)
			{
				switch (selection)
				{
				case 0:
					max_x == 500 ? max_x = 0 : max_x++; break;
				case 1:
					max_y == 500 ? max_y = 0 : max_y++; break;
				case 2:
					offset_x == 500 ? offset_x = 0 : offset_x++; break;
				case 3:
					offset_y == 500 ? offset_y = 0 : offset_y++; break;
				default:
					break;
				}
				InputCoolDown.StartNewTimer(0.2);
				reDraw = true;
			}
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (selection==4)
			{
				exit = true;
				Game::display.setSizeX(max_x);
				Game::display.setSizeY(max_y);
				Game::display.setOffSetPositionX(offset_x);
				Game::display.setOffSetPositionY(offset_y);
				reDraw = false;
				clearScreen(5, 25);
			}
		}

		if (reDraw == true)
		{
			std::ostringstream max_x_str;
			std::ostringstream max_y_str;
			std::ostringstream offset_y_str;
			std::ostringstream offset_x_str;

			max_x_str << max_x;
			max_y_str << max_y;
			offset_x_str << offset_x;
			offset_y_str << offset_y;

			reDraw = false;

			clearScreen(5, 25);
			CursorPos(0, 0);

			switch (selection)
			{
			case 0:
				cout << "1.Size X <" << max_x_str.str() << "> <-" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Return"; break;
			case 1:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << "> <-" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Return"; break;
			case 2:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << "> <-" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Return"; break;
			case 3:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << "> <-" << endl
					<< "5.Return"; break;
			case 4:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Return <-"; break;
			}
		}

	}
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
        applePosition.x=(rand() % (Game::display.GetMaxSizeX()+1))+Game::display.getOffSetPositionX();
        applePosition.y=(rand() % (Game::display.GetMaxSizeY()+1))+Game::display.getOffSetPositionY();
        appleUpdate();
    }
}

void appleUpdate()
{
    Game::display.SetPos(applePosition, '@');
}

void gameLoop()
{
    Position pos(Game::display.getOffSetPositionY()+1, Game::display.getOffSetPositionX());
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

void mainMenu()
{
    Timer InputCoolDown;
	int selection = 0;
	int selectionMax = 2;
	bool reDraw = true;
    CursorPos(0,0);
    while(true)
    {
        if(GetAsyncKeyState('W'))
        {
            if(InputCoolDown.Update() == true)
            {
				selection == 0 ? selection = 2 : selection--;

				reDraw = true;

                InputCoolDown.StartNewTimer(0.2);
            }
		}
		else if(GetAsyncKeyState('S'))
		{
			if (InputCoolDown.Update() == true)
			{
				selection == selectionMax ? selection = 0 : selection++;

				reDraw = true;

				InputCoolDown.StartNewTimer(0.2);
			}
		}
		else if (GetAsyncKeyState(VK_RETURN))
        {
            if(InputCoolDown.Update()==true)
            {
                if(selection==0)
                {
                    clearScreen(3,20);
                    gameLoop();
                    clearScreen(Game::display.GetMaxSizeY()+Game::display.getOffSetPositionY()+2, Game::display.GetMaxSizeX()+Game::display.getOffSetPositionX()+2); // Adds the max width, plus offset, +2 for the borders.
                    CursorPos(0,0);
					reDraw = true;
				} else if (selection==1)
                {
					settingsMenu();
					reDraw = true;
				}
				else
					return;

                InputCoolDown.StartNewTimer(0.2);
            }
        }

		if (reDraw==true)
		{
			clearScreen(3, 20);
			CursorPos(0, 0);
			reDraw = false;
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

    mainMenu();

    return 0;
}
