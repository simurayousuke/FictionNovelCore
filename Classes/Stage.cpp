#include "Stage.h"

Stage::Stage()
{

}

Stage::Stage(std::string cont,int next)
{
	context = cont;
	nextId = next;
}

Stage::~Stage()
{

}

std::string Stage::getContext()
{
	return context;
}

int Stage::getNextId()
{
	return nextId;
}

void Stage::setNextId(int id)
{
	nextId = id;
}
void Stage::setContext(std::string cont)
{
	context = cont;
}
void Stage::setFont(std::string fnt)
{
	font = fnt;
}
void Stage::setHasButton(bool ifhas)
{
	hasBtn = ifhas;
}
void Stage::setButtonNum(int num)
{
	buttonNum = num;
}
void Stage::setButtons(Button* button)
{
	buttons = button;
}
void Stage::setBgm(std::string s)
{
	bgm = s;
}
void Stage::setBg(std::string s)
{
	bg = s;
}
void Stage::setConversationBg(std::string s)
{
	conversationBg = s;
}
void Stage::setVoice(std::string s)
{
	voice = s;
}
void Stage::setFontSize(int sz)
{
	fontSize = sz;
}


std::string Stage::getFont()
{
	return font==""? Local::getDefaultFont() : font;
}
bool Stage::hasButton()
{
	return hasBtn;
}
int Stage::getButtonNum()
{
	return buttonNum;
}
Button* Stage::getButtons()
{
	return buttons;
}
std::string Stage::getBgm()
{
	return bgm;
}
std::string Stage::getBg()
{
	return bg;
}
std::string Stage::getConversationBg()
{
	return conversationBg;
}
std::string Stage::getVoice()
{
	return voice;
}
int Stage::getFontSize()
{
	return fontSize;
}