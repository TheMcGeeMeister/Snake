#ifndef DISPLAY_H
#define DISPLAY_H
#include <Position.h>
#include <windows.h>
#include <map>
#include <vector>

using namespace std;

class display_change
{
    public:
        void SetChange(Position, char);
        void SetChangeColor(Position, DWORD);

        Position GetChangePos();
        char GetChangeGraphic();
        DWORD GetChangeAttribute();

        bool isChangeGraphic();
        bool isChangeAttribute();
    private:
        Position pos;
        char graphic;
        DWORD attribute_;
        bool isChangeGraphic_;
};

class Display
{
    public:
        Display(unsigned int size_y, unsigned int size_x);
        Display(unsigned int size_y, unsigned int size_x, unsigned int offset_y, unsigned int offset_x);
		Display();
        virtual ~Display();
        void Update();
        void DrawBorder();
        void clearDisplay();
        void SetPos(Position, char);
        void SetPosAttribute(Position, DWORD);
        void setSizeY(int);
        void setSizeX(int);
        void setStartPositionX(int);
        void setStartPositionY(int);
		void setOffSetPositionX(int);
		void setOffSetPositionY(int);
        bool isValidPosition(Position);
        int GetMaxSizeY();
        int GetMaxSizeX();
        int getStartPositionX();
        int getStartPositionY();
		unsigned int getOffSetPositionX();
		unsigned int getOffSetPositionY();
        char GetPos(Position);
		Position getRandomValidPosition();
    private:
        map<pair<int,int>, char> GameMap;
        vector<display_change> MapChangesBuffer;
        HANDLE h;
        unsigned int size_y, size_x;
        unsigned int offset_y_, offset_x_;
        DWORD nlength;
        DWORD output;
		WORD readAttribute_;
        COORD pos;
		char readConsole_;
};

#endif // DISPLAY_H
