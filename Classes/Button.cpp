#include "Button.h"

Button::Button()
{

}

Button::Button(std::string cont, int next)
{
	context = cont;
	nextId = next;
}

Button::Button(std::string cont, std::string fnt, int next)
{
	context = cont;
	font = fnt;
	nextId = next;
}

Button::~Button()
{

}

std::string Button::getContext()
{
	return context;
}

int Button::getNextId()
{
	return nextId;
}

std::string Button::getFont()
{
	return font == "" ? "Marker Felt.ttf" : font;
}

int Button::getFontSize()
{
	return fontSize;
}

void Button::setContext(std::string cont)
{
	context = cont;
}
void Button::setFont(std::string fnt)
{
	font = fnt;
}
void Button::setNextId(int id)
{
	nextId = id;
}
void Button::setFontSize(int sz)
{
	fontSize = sz;
}