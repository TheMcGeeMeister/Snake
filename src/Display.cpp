#include "Display.h"

Display::Display(unsigned int size_y, unsigned int size_x)
{
    nlength=1;
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    this->size_x=size_x;
    this->size_y=size_y;
    offset_x_=1;
    offset_y_=1;
}

Display::Display(unsigned int size_y, unsigned int size_x, unsigned int offset_y, unsigned int offset_x)
{
    nlength=1;
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    this->size_x=size_x;
    this->size_y=size_y;
	offset_y_ = offset_y;
	offset_x_ = offset_x;
}

Display::Display()
{
	nlength = 1;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	size_x = 10;
	size_y = 5;
	offset_y_ = 1;
	offset_x_ = 1;
}

Display::~Display()
{
    //dtor
}

bool Display::isValidPosition(Position position)
{
    if(position.x<offset_x_)
    {
        return false;
    }else if(position.x>(offset_x_+size_x))
    {
        return false;
    }else if(position.y<offset_y_)
    {
        return false;
    }else if(position.y>(offset_y_+size_y))
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
    position.x=offset_x_-1;
    for(int y=offset_y_-1;y<=(size_y+offset_y_+1);y++) // Left Border
    {
        position.y=y;
        SetPos(position, '#');
    }
    position.x=(offset_x_+size_x+1);
    for(int y=(offset_y_-1);y<=(size_y+offset_y_+1);y++) // Right Border
    {
        position.y=y;
        SetPos(position, '#');
    }
    position.y=offset_y_-1;
    for(int x=(offset_x_)-1;x<=(size_x+offset_x_+1);x++) // Top Border
    {
        position.x=x;
        SetPos(position, '#');
    }
    position.y=(offset_y_+size_y+1);
    for(int x=(offset_x_-1);x<=(size_x+offset_x_+1);x++) // Bottom Border
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
    offset_x_=_x;
}

void Display::setStartPositionY(int _y)
{
    offset_y_=_y;
}

void Display::setOffSetPositionX(int _x)
{
	offset_x_ = _x;
}

void Display::setOffSetPositionY(int _y)
{
	offset_y_ = _y;
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
            const WORD attribute=(const WORD)iter->GetChangeAttribute();
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
    return offset_x_;
}

int Display::getStartPositionY()
{
    return offset_y_;
}

unsigned int Display::getOffSetPositionX()
{
	return offset_y_;
}

unsigned int Display::getOffSetPositionY()
{
	return offset_y_;
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
