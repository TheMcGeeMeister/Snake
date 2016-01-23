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
        Display(int size_y, int size_x);
        Display(int size_y, int size_x, int start_y, int start_x);
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
        bool isValidPosition(Position);
        int GetMaxSizeY();
        int GetMaxSizeX();
        int getStartPositionX();
        int getStartPositionY();
        char GetPos(Position);
    private:
        map<pair<int,int>, char> GameMap;
        vector<display_change> MapChangesBuffer;
        HANDLE h;
        int size_y, size_x;
        int start_y_, start_x_;
        DWORD nlength;
        DWORD output;
        COORD pos;
};

#endif // DISPLAY_H
