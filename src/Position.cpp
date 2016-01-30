#include "Position.h"

Position::Position()
{
    return;
}

Position::Position(int y, int x)
{
    this->x=x;
    this->y=y;
    return;
}

Position::~Position()
{
    return;
}

void Position::SetX(int x)
{
    this->x=x;
    return;
}

void Position::SetY(int y)
{
    this->y=y;
    return;
}

bool Position::operator<(const Position& b) const
{
    if(this->y<b.y)
    {
        return true;
    }else if(this->y==b.y)
    {
        if(this->x<b.x)
        {
            return true;
        }
    }else
    {
        return false;
    }
    return false;
}

pair<int, int> Position::operator()()
{
    pair<int, int> data;
    data.first=y;
    data.second=x;
    return data;
}

void Position::operator()(int y, int x)
{
    this->y=y;
    this->x=x;
    return;
}

void Position::operator=(const Position& pos)
{
    y=pos.y;
    x=pos.x;
}

bool Position::operator==(const Position& pos)
{
    if(pos.x==x && pos.y==y)
    {
        return true;
    }else
    {
        return false;
    }
}

