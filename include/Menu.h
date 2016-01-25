#ifndef Menu_H
#define Menu_H
#include <iostream>
#include <string>
#include <Display.h>
#include <Timer.h>

using namespace std;

class Menu
{
    public:
		Menu(unsigned int size_x, unsigned int size_y);
		Menu(unsigned int size_x, unsigned int size_y, unsigned int offset_x, unsigned int offset_y);
		Menu();
		~Menu();

		void addSelection(string text);
		void setMenuFocus(bool isFocused);
		void setHiddenState(bool isHidden);

		unsigned int getActiveSelection();

		bool selectionActivated();
		bool isMenuInFocus();
		bool isHidden();
		bool getMenuFocus();

		void update();

		Timer& InputTimer = InputCoolDown;
    protected:

    private:
		unsigned int size_x_, size_y_, offset_x_, offset_y_, selected_, selectionAmount_;
		map<unsigned int, string> selections_;
		bool isMenuFocused_;
		bool reDraw;
		bool selectionActivated_;
		bool isHidden_;
		Timer InputCoolDown;

};

#endif // Menu_H
