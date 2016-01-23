#include <iostream>
#include <Display.h>
#include <Timer.h>
#include <Player.h>
#include <random>
#include <conio.h>
#include <thread>
#include <Network.h>

using namespace std;

void spawnMultipleApples(int spawn_amount);
void clearScreen();
void clearScreen(int lines, int width);

Display Test(5, 10, 1, 1);
Timer MovementCoolDown;
Direction CurMove;
Player Player;
Position applePosition;
Timer InputCoolDown;
double CoolDownTime=0.04;
bool ateSelfYaDumb=false;
bool gameExit=false;

namespace Game
{

}

Timer SpeedCoolDown;

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
    ateSelfYaDumb=true;
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

void SpeedTime() // No Affect Atm
{
    if(SpeedCoolDown.Update()==false)
    {
        return;
    }
    CoolDownTime+=0.1;
    SpeedCoolDown.StartNewTimer(1.00);
}

void SlowTime() // No Affect Atm
{
    if(SpeedCoolDown.Update()==false)
    {
        return;
    }
    CoolDownTime-=0.01;
    SpeedCoolDown.StartNewTimer(1.00);
}

void TestInput()
{
    if(GetAsyncKeyState('W'))
    {
        if(Player.CanChangeDirect(Up)==true && Player.CanMoveCertainDirection(Up))
        {
            Player.SetPlayerDirect(Up);
            Player.AddTurnPoint(Up);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    else if(GetAsyncKeyState('S') && Player.CanMoveCertainDirection(Down))
    {
        if(Player.CanChangeDirect(Down)==true)
        {
            Player.SetPlayerDirect(Down);
            Player.AddTurnPoint(Down);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    else if(GetAsyncKeyState('A') && Player.CanMoveCertainDirection(Left))
    {
        if(Player.CanChangeDirect(Left)==true)
        {
            Player.SetPlayerDirect(Left);
            Player.AddTurnPoint(Left);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    else if(GetAsyncKeyState('D') && Player.CanMoveCertainDirection(Right))
    {
        if(Player.CanChangeDirect(Right)==true && Player.CanMoveCertainDirection(Right))
        {
            Player.SetPlayerDirect(Right);
            Player.AddTurnPoint(Right);
            InputCoolDown.StartNewTimer(0.2);
        }
    }
    if(GetAsyncKeyState('T'))
    {
        if(InputCoolDown.Update()==false)
        {
            return;
        }
        Player.AddTail();
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

void logic() // Not in-use TODO:Fix this shit. Even though idk why it's broken
{
    while(ateSelfYaDumb==false && gameExit==false)
    {
        char input=getch();
        switch(input)
        {
            case 'w':
                if(Player.CanChangeDirect(Up)==true && Player.CanMoveCertainDirection(Up))
                {
                    Player.SetPlayerDirect(Up);
                    Player.AddTurnPoint(Up);
                } break;
            case 's':
                if(Player.CanChangeDirect(Down)==true && Player.CanMoveCertainDirection(Down))
                {
                    Player.SetPlayerDirect(Down);
                    Player.AddTurnPoint(Down);
                } break;
            case 'a':
                if(Player.CanChangeDirect(Left)==true && Player.CanMoveCertainDirection(Left))
                {
                    Player.SetPlayerDirect(Left);
                    Player.AddTurnPoint(Left);
                } break;
            case 'd':
                if(Player.CanChangeDirect(Right)==true && Player.CanMoveCertainDirection(Right))
                {
                    Player.SetPlayerDirect(Right);
                    Player.AddTurnPoint(Right);
                } break;
        }
        CursorPos(43,0);
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

void appleUpdate();

void spawnApple()
{
    applePosition.x=(rand() % (Test.GetMaxSizeX()+1))+Test.getStartPositionX();
    applePosition.y=(rand() % (Test.GetMaxSizeY()+1))+Test.getStartPositionY();
    appleUpdate();
}

void spawnMultipleApples(int spawn_amount)
{
    for(int x=0;x<spawn_amount;x++)
    {
        applePosition.x=(rand() % (Test.GetMaxSizeX()+1))+Test.getStartPositionX();
        applePosition.y=(rand() % (Test.GetMaxSizeY()+1))+Test.getStartPositionY();
        appleUpdate();
    }
}

void appleUpdate()
{
    Test.SetPos(applePosition, '@');
}

void gameLoop()
{
    Position pos(2,2);
    Player.SetPlayerPos(pos);
    spawnApple();
    Test.clearDisplay();
    Test.DrawBorder();
    while(isExit()==false && ateSelfYaDumb==false)
    {
        TestInput();
        Player.Update();
        Test.Update();
        appleUpdate();
        Sleep(1);
    }
    Player.resetTail();
    ateSelfYaDumb=false;
    return;
}

void startGame()
{
    Timer InputCoolDown;
    int selection=0;
    CursorPos(0,0);
    cout<<"1.Start Game<-"<<endl
        <<"2.Exit Game"<<endl;
    while(true==true)
    {
        if(GetAsyncKeyState('W') || GetAsyncKeyState('S'))
        {
            if(InputCoolDown.Update()==true)
            {
                if(selection==0)
                {
                    selection=1;
                    clearScreen(2, 15);
                    CursorPos(0,0);
                    cout<<"1.Start Game"<<endl
                        <<"2.Exit Game<-"<<endl;
                }else
                {
                    selection=0;
                    clearScreen(2, 15);
                    CursorPos(0,0);
                    cout<<"1.Start Game<-"<<endl
                        <<"2.Exit Game"<<endl;
                }
                InputCoolDown.StartNewTimer(0.2);
            }
        }else if(GetAsyncKeyState(VK_RETURN))
        {
            if(InputCoolDown.Update()==true)
            {
                if(selection==0)
                {
                    clearScreen();
                    gameLoop();
                    clearScreen();
                    CursorPos(0,0);
                    cout<<"1.Start Game<-"<<endl
                        <<"2.Exit Game"<<endl;
                }else
                {
                    return;
                }
                InputCoolDown.StartNewTimer(0.2);
            }
        }
        /*if(selection==0)
        {
            clearScreen(2, 15);
            CursorPos(0,0);
            cout<<"1.Start Game<-"<<endl
                <<"2.Exit Game"<<endl;
        }else
        {
            clearScreen(2, 15);
            CursorPos(0,0);
            cout<<"1.Start Game"<<endl
                <<"2.Exit Game<-"<<endl;
        }*/
        Sleep(1);
    }
}

void clearScreen()
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

void clearScreen(int lines, int width)
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

    CursorPos((Test.GetMaxSizeX()+Test.getStartPositionX())+2, 0);

    startGame();
    /*while(isExit()==false && ateSelfYaDumb==false)
    {
        TestInput();
        Player.Update();
        Test.Update();
        appleUpdate();
        Sleep(1);
    }*/
    /*clearScreen();
    cout<<"<<Dev Mode Initialized>>"<<endl;
    Network Client;
    Client.StartClient("24.100.184.220");
    Client.CloseClientConnection();
    cout<<"Error:"<<Client.isError()<<endl;
    cout<<Client.getLastError()<<endl;
    cout<<false<<endl;
    gameExit=true;
    Sleep(1000);
    cin.get();*/
    return 0;
}