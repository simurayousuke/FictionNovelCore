#ifndef  _BUTTON_H_
#define  _BUTTON_H_

#include "cocos2d.h"


class Button
{
public:
	Button();
	Button(std::string cont, int next);
	Button(std::string cont, std::string font, int next);
	~Button();
	std::string getContext();
	std::string getFont();
	int getNextId();
	void setContext(std::string cont);
	void setFont(std::string fnt);
	void setNextId(int id);
private:
	std::string context;
	std::string font = "";
	int nextId;
};

#endif // _BUTTON_H_
