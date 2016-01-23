#include "Display.h"

Display::Display(int size_y, int size_x)
{
    nlength=1;
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    this->size_x=size_x;
    this->size_y=size_y;
    start_x_=1;
    start_y_=1;
}

Display::Display(int size_y, int size_x, int start_y, int start_x)
{
    nlength=1;
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    this->size_x=size_x;
    this->size_y=size_y;
    start_y_=start_y;
    start_x_=start_x;
}

Display::Display()
{
	
}

Display::~Display()
{
    //dtor
}

bool Display::isValidPosition(Position position)
{
    if(position.x<start_x_)
    {
        return false;
    }else if(position.x>(start_x_+size_x))
    {
        return false;
    }else if(position.y<start_y_)
    {
        return false;
    }else if(position.y>(start_y_+size_y))
    {
        return false;
    }else
    {
        return true;
    }
}

void Display::DrawBorder()
{
    Position position;
    position.x=start_x_-1;
    for(int y=start_y_-1;y<=(size_y+start_y_+1);y++) // Left Border
    {
        position.y=y;
        SetPos(position, '#');
    }
    position.x=(start_x_+size_x+1);
    for(int y=(start_y_-1);y<=(size_y+start_y_+1);y++) // Right Border
    {
        position.y=y;
        SetPos(position, '#');
    }
    position.y=start_y_-1;
    for(int x=(start_x_)-1;x<=(size_x+start_x_+1);x++) // Top Border
    {
        position.x=x;
        SetPos(position, '#');
    }
    position.y=(start_y_+size_y+1);
    for(int x=(start_x_-1);x<=(size_x+start_x_+1);x++) // Bottom Border
    {
        position.x=x;
        SetPos(position, '#');
    }

}

void Display::SetPos(Position pos, char graphic)
{
    display_change gChange;
    gChange.SetChange(pos, graphic);
    MapChangesBuffer.push_back(gChange);
    GameMap[pos()]=graphic;
}

void Display::SetPosAttribute(Position pos, DWORD attribute)
{
    display_change aChange;
    aChange.SetChangeColor(pos, attribute);
    MapChangesBuffer.push_back(aChange);
}

void Display::setStartPositionX(int _x)
{
    start_x_=_x;
}

void Display::setStartPositionY(int _y)
{
    start_y_=_y;
}

void Display::setSizeY(int _in_y)
{
    size_y=_in_y;
    return;
}

void Display::setSizeX(int _in_x)
{
    size_x=_in_x;
    return;
}


void Display::Update()
{
    Position CurrentPosition(0,0);
    vector<display_change>::iterator iter=MapChangesBuffer.begin();
    vector<display_change>::iterator iEnd=MapChangesBuffer.end();
    for(;iter!=iEnd;iter++)
    {
        if(iter->isChangeGraphic()==true)
        {
            CurrentPosition=iter->GetChangePos();
            const char graphic=GameMap[CurrentPosition()];
            pos.X=CurrentPosition.x;
            pos.Y=CurrentPosition.y;
            WriteConsoleOutputCharacter(h, &graphic, nlength, pos, &output);
        }else
        {
            const WORD attribute=iter->GetChangeAttribute();
            CurrentPosition=iter->GetChangePos();
            pos.X=CurrentPosition.x;
            pos.Y=CurrentPosition.y;
            WriteConsoleOutputAttribute(h, &attribute, nlength, pos, &output);
        }
    }
    MapChangesBuffer.clear();
}

void Display::clearDisplay()
{
    GameMap.clear();
    MapChangesBuffer.clear();
}

int Display::GetMaxSizeY()
{
    return size_y;
}

int Display::GetMaxSizeX()
{
    return size_x;
}

int Display::getStartPositionX()
{
    return start_x_;
}

int Display::getStartPositionY()
{
    return start_y_;
}

char Display::GetPos(Position position)
{
    return GameMap[position()];
}








void display_change::SetChange(Position pos, char graphic)
{
    isChangeGraphic_=true;
    this->pos=pos;
    this->graphic=graphic;
    return;
}

void display_change::SetChangeColor(Position position, DWORD attribute)
{
    isChangeGraphic_=false;
    pos=position;
    attribute_=attribute;
    return;
}

Position display_change::GetChangePos()
{
    return pos;
}

char display_change::GetChangeGraphic()
{
    return graphic;
}

DWORD display_change::GetChangeAttribute()
{
    return attribute_;
}
bool display_change::isChangeAttribute()
{
    if(isChangeGraphic_==false)
    {
        return true;
    }else
    {
        return false;
    }
}

bool display_change::isChangeGraphic()
{
    return isChangeGraphic_;
}
