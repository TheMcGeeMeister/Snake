#include "Console.h"


/*Console::~Console()
{
    //dtor
}

Console::Console(int size_x, int size_y)
{
    size_y_=size_y;
    size_x_=size_x;
    start_x_=1;
    start_y_=1;
    current_y_=1;
    active_line_=1;
    screen_.setSizeX(size_x);
    screen_.setSizeY(size_y);
    screen_.setStartPositionY(1);
    screen_.setStartPositionX(1);
}

Console::Console(int size_x, int size_y, int start_x, int start_y)
{
    size_y_=size_y;
    size_x_=size_x;
    start_y_=start_y;
    start_x_=start_x;
    current_y_=1;
    active_line_=1;
    screen_.setSizeY(size_y);
    screen_.setSizeX(size_x);
    screen_.setStartPositionY(1);
    screen_.setStartPositionX(1);
}

Console::draw()
{

}

Console::addText(std::string text)
{
    Position pos;
    console_[0]+=text;
    string::iterator iter=text.begin();
    string::iterator iEnd=text.end();
    pos.y=0;
    for(;iter!=iEnd;iter++)
    {
        pos.x=(int)iter;
        screen_.SetPos(pos, text[iter]);
    }
}

Console::newLine()
{
    std::map<int, string>::iterator iter=console_.end();
    std::map<int, string>::iterator iEnd=console_.begin();
    for(;iter!=iEnd;iter--) // Iter goes backwards
    {
        if(iter->second.empty()==false)
        {
            console_[iter->first.begin()+1]=iter->second;
        }
    }
}*/

