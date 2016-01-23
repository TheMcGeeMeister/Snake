#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>
#include <Display.h>

/*enum ConsoleMode
{
    MODE_COMMAND, MODE_SELECTION, MODE_UI_SELECTION, MODE_UI_COMMAND
};

class Console
{
    public:
        Console();
        //Console(int size_x, int size_y, ConsoleMode Mode=MODE_SELECTION); Canceled For Now
        Console(int size_x, int size_y);
        //Console(int size_x, int size_y, int start_x, int start_y, ConsoleMode Mode=MODE_SELECTION); Canceled For now
        Console(int size_x, int size_y, int start_x, int start_y);
        virtual ~Console();
        void addText(std::string);
        void newLine(std::string);
        void computeCommand(std::string);
        void scrollUp();
        void scrollDown();
        //void setMode(ConsoleMode); Canceled For Now
        void setActiveLine(int);
        //void addSelection(std::string);
        void addSelection(std::string , int line);
        void draw();
    protected:

    private:
        int size_x_;
        int size_y_;
        int start_x_;
        int start_y_;
        int active_line_;
        int current_y_;
        //ConsoleMode mode_; Cancel For Now
        map<int, string> console_;
        Display screen_;
};*/

#endif // CONSOLE_H
