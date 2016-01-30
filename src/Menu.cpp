#include "Menu.h"
#include "Game.h"
#include <sstream>


Menu::~Menu()
{
    //dtor
}

Menu::Menu()
{
	size_y_ = 25;
	size_x_ = 50;
	offset_x_ = 0;
	offset_y_ = 0;
	isMenuFocused_ = true;
	isHidden_ = false;
	selectionActivated_ = false;
	selectionAmount_ = 0;
	selected_ = 0;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(unsigned int size_x, unsigned int size_y)
{
    size_y_=size_y;
    size_x_=size_x;
    offset_x_=1;
    offset_y_=1;
	selected_ = 1;
	isMenuFocused_ = true;
	isHidden_ = false;
	selectionActivated_ = false;
	selectionAmount_ = 0;
	selected_ = 0;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(unsigned int size_x, unsigned int size_y, unsigned int offset_x, unsigned int offset_y)
{
    size_y_=size_y;
    size_x_=size_x;
    offset_y_=offset_y;
    offset_x_=offset_x;
    selected_=1;
	isMenuFocused_ = true;
	isHidden_ = false;
	selectionActivated_ = false;
	selectionAmount_ = 0;
	selected_ = 0;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Menu::addSelection(string text)
{
	selections_[selectionAmount_] = text;

	selectionAmount_++;
	reDraw = true;
}

void Menu::setMenuFocus(bool isFocused)
{
	isMenuFocused_ = isFocused;
}

void Menu::setHiddenState(bool isHidden)
{
	isHidden_ = isHidden;
	if (isHidden)
	{
		for (int i = 0; i != selectionAmount_; i++)
		{
			FillLine(i, size_x_);
		}
	}
	else
	{
		reDraw = true;
	}
}

void Menu::setSelectionColor(string selection, WORD color)
{
	selections_color_[selection] = color;
}

unsigned int Menu::getActiveSelection()
{
	return selected_ + 1;
}

bool Menu::selectionActivated()
{
	if (selectionActivated_)
	{
		selectionActivated_ = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool Menu::isMenuInFocus()
{
	return isMenuFocused_;
}

bool Menu::isHidden()
{
	return isHidden_;
}

bool Menu::getMenuFocus()
{
	return isMenuFocused_;
}

void Menu::update()
{
	stringstream buffer;
	if (reDraw)
	{
		clearScreen(selectionAmount_, size_x_);
		CursorPos(offset_y_, offset_x_);
		for (int i = 0; i != selectionAmount_; i++)
		{
			if (i == selected_)
			{
				buffer << i + 1 << "." << selections_[i] << " <-" << endl;
			}
			else
			{
				buffer << i + 1 << "." << selections_[i] << endl;
			}
		}
		cout << buffer.str();
		reDraw = false;
	}
	if (InputCoolDown.Update() == true && isMenuFocused_ == true && isHidden_ == false)
	{
		if (GetAsyncKeyState('W'))
		{
			selected_ == 0 ? selected_ = selectionAmount_-1 : selected_--;
			selectionActivated_ = false;
			InputCoolDown.StartNewTimer(0.2);
			reDraw = true;
		}
		else if (GetAsyncKeyState('S'))
		{
			selected_ == selectionAmount_ - 1 ? selected_ = 0 : selected_++;
			selectionActivated_ = false;
			InputCoolDown.StartNewTimer(0.2);
			reDraw = true;
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			selectionActivated_ = true;
			InputCoolDown.StartNewTimer(0.2);
		}
	}
}
