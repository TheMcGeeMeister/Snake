#include <iostream>
#include <Timer.h>
#include <random>
#include <conio.h>
#include <thread>
#include <Menu.h>
#include <Game.h>
#include <sstream>

using namespace std;

void spawnMultipleApples(int spawn_amount);
void clearScreen();
void clearScreen(unsigned int lines, unsigned int width);


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

void FillLine(int line, int width)
{
	COORD pos;
	pos.X = 0;
	pos.Y = line;
	DWORD nlength = width;
	DWORD output;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR graphic = ' ';
	FillConsoleOutputCharacter(h, graphic, nlength, pos, &output);
}

Position Make_Pos(int y, int x)
{
    return Position(y,x);
}

void Logic()
{
	if (InputCoolDown.Update() == true)
	{
		if (GetAsyncKeyState('W'))
		{
			if (Game::player.isValidDirectChange(Up) == true && Game::player.isValidPositionInDirect(Up))
			{
				Game::player.SetPlayerDirect(Up);
				InputCoolDown.StartNewTimer(0.05);
			}
		}
		else if (GetAsyncKeyState('S'))
		{
			if (Game::player.isValidDirectChange(Down) == true && Game::player.isValidPositionInDirect(Down))
			{
				Game::player.SetPlayerDirect(Down);
				InputCoolDown.StartNewTimer(0.05);
			}
		}
		else if (GetAsyncKeyState('A'))
		{
			if (Game::player.isValidDirectChange(Left) == true && Game::player.isValidPositionInDirect(Left))
			{
				Game::player.SetPlayerDirect(Left);
				InputCoolDown.StartNewTimer(0.05);
			}
		}
		else if (GetAsyncKeyState('D'))
		{
			if (Game::player.isValidDirectChange(Right) == true && Game::player.isValidPositionInDirect(Right))
			{
				Game::player.SetPlayerDirect(Right);
				InputCoolDown.StartNewTimer(0.05);
			}
		}
		if (GetAsyncKeyState('T'))
		{
			Game::player.AddTail();
			InputCoolDown.StartNewTimer(0.1);
		}
		if (GetAsyncKeyState('Y'))
		{
			spawnMultipleApples(3);
			InputCoolDown.StartNewTimer(0.1);
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
	int selectionMax = 5;

	int max_y = Game::display.GetMaxSizeY();
	int max_x = Game::display.GetMaxSizeX();
	int offset_y = Game::display.getOffSetPositionY();
	int offset_x = Game::display.getOffSetPositionX();
	double playerSpeed = Game::player.getMovementCooldown();

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
				case 4:
					playerSpeed < 0.001 ? playerSpeed = 0.04 : playerSpeed-=0.001; break;
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
				case 4:
					playerSpeed == 1 ? playerSpeed = 0.04 : playerSpeed+=0.001; break;
				default:
					break;
				}
				InputCoolDown.StartNewTimer(0.2);
				reDraw = true;
			}
		}
		else if (GetAsyncKeyState('F'))
		{
			if (InputCoolDown.Update() == true)
			{
				switch (selection)
				{
				case 0:
					max_x == 500 ? max_x = 0 : max_x += 10;
					if (max_x > 500) max_x -= 500; break;
				case 1:
					max_y == 500 ? max_y = 0 : max_y+=10;
					if (max_y > 500) max_y -= 500; break;
				case 2:
					offset_x == 500 ? offset_x = 0 : offset_x+=10;
					if (offset_x > 500) offset_x -= 500; break;
				case 3:
					offset_y == 500 ? offset_y = 0 : offset_y+=10;
					if (offset_y > 500) offset_y -= 500; break;
				case 4:
					playerSpeed == 1 ? playerSpeed = 0.04 : playerSpeed += 0.01;
					if (playerSpeed > 1) playerSpeed -= 0.96; break;
				default:
					break;
				}
				InputCoolDown.StartNewTimer(0.2);
				reDraw = true;
			}
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (selection==selectionMax)
			{
				exit = true;
				Game::display.setSizeX(max_x);
				Game::display.setSizeY(max_y);
				Game::display.setOffSetPositionX(offset_x);
				Game::display.setOffSetPositionY(offset_y);
				Game::player.setMovementCooldown(playerSpeed);
				reDraw = false;
				clearScreen(5, 50);
			}
		}

		if (reDraw == true)
		{
			std::ostringstream max_x_str;
			std::ostringstream max_y_str;
			std::ostringstream offset_y_str;
			std::ostringstream offset_x_str;
			std::ostringstream playerSpeed_str;

			max_x_str << max_x;
			max_y_str << max_y;
			offset_x_str << offset_x;
			offset_y_str << offset_y;
			playerSpeed_str << playerSpeed;

			reDraw = false;

			clearScreen(5, 50);
			CursorPos(0, 0);

			switch (selection)
			{
			case 0:
				cout << "1.Size X <" << max_x_str.str() << "> <-" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Player Speed Timer <" << playerSpeed_str.str() << "%>" << endl
					<< "6.Return"; break;
			case 1:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << "> <-" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Player Speed Timer <" << playerSpeed_str.str() << "%>" << endl
					<< "6.Return"; break;
			case 2:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << "> <-" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Player Speed Timer <" << playerSpeed_str.str() << "%>" << endl
					<< "6.Return"; break;
			case 3:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << "> <-" << endl
					<< "5.Player Speed Timer <" << playerSpeed_str.str() << "%>" << endl
					<< "6.Return"; break;
			case 4:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Player Speed Timer <" << playerSpeed_str.str() << "%> <-" << endl
					<< "6.Return"; break;
			case 5:
				cout << "1.Size X <" << max_x_str.str() << ">" << endl
					<< "2.Size Y <" << max_y_str.str() << ">" << endl
					<< "3.Offset X <" << offset_x_str.str() << ">" << endl
					<< "4.Offset Y <" << offset_y_str.str() << ">" << endl
					<< "5.Player Speed Timer <" << playerSpeed_str.str() << "%>" << endl
					<< "6.Return <-"; break;
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
	CursorPos(Game::display.GetMaxSizeY() + Game::display.getOffSetPositionY() + 2, Game::display.GetMaxSizeX() + Game::display.getOffSetPositionX() + 2);
    Position pos(Game::display.getOffSetPositionY()+1, Game::display.getOffSetPositionX()+1);
    Game::player.SetPlayerPos(pos);
	Game::player.setDirect(Up);
    spawnApple();
    Game::display.clearDisplay();
    Game::display.DrawBorder();
    while(isExit()==false && playerAteSelf==false)
    {
        Logic();
        Game::player.Update();
        Game::display.Update();
        appleUpdate();
    }
    Game::player.resetTail();
	Game::display.clearDisplay();
    playerAteSelf=false;
    return;
}

void mainMenu()
{
	Menu menu;
	menu.addSelection("Start Game");
	menu.addSelection("Settings");
	menu.addSelection("Exit");
		
	while (true)
	{
		menu.update();
		if (menu.selectionActivated())
		{
			switch (menu.getActiveSelection())
			{
			case 1:
				menu.setHiddenState(true);
				gameLoop();
				menu.setHiddenState(false);
				break;
			case 2:
				menu.setHiddenState(true);
				settingsMenu();
				menu.setHiddenState(false);
				menu.InputTimer.StartNewTimer(0.2);
				break;
			case 3:
				return;
				break;
			}
		}
    }
}

void clearScreen() // Not reccomended takes a lot of time to clear this much Edit: Maybe not as long, changed it to use FillLine() but hasn't been tested for efficiency
{
    Position pos;
    for(int y=0;y<=300;y++)
    {
        pos.y=y;
		FillLine(y, 300);
    }
}

void clearScreen(unsigned int lines, unsigned int width) // Pick the amount of lines, and the width of them to be cleared
{
    Position pos;
    for(unsigned int y=0;y<=lines;y++)
    {
        pos.y=y;
		FillLine(y, width);
        /*for(int x=0;x<=width;x++) FillLine is more efficent
        {
            pos.x=x;
            SetPos(pos, ' ');
        }*/
    }
}

int main()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 1;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorInfo(h, &cursorInfo);

    srand((unsigned int)time(NULL));

    CursorPos((Game::display.GetMaxSizeX()+Game::display.getStartPositionX())+2, 0);

    mainMenu();

    return 0;
}
