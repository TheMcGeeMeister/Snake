#ifndef GAME_H
#define GAME_H
#include <Display.h>
#include <Player.h>

namespace Game
{
	extern Display display;
}

void CursorPos(short int y, short int x);
void FillLine(int line, int width);
void clearScreen(unsigned int lines, unsigned int width);

#endif