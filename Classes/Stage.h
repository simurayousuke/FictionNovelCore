#ifndef  _STAGE_H_
#define  _STAGE_H_

#include "cocos2d.h"
#include "Button.h"

class Stage
{
public:
	Stage();
	Stage(std::string cont,int next);
	~Stage();	
	void setNextId(int id);
	void setContext(std::string cont);
	void setFont(std::string fnt);
	void setHasButton(bool ifhas);
	void setButtonNum(int num);
	void setButtons(Button* button);
	void setBgm(std::string s);
	void setBg(std::string s);
	void setConversationBg(std::string s);
	void setVoice(std::string s);

	int getNextId();
	std::string getContext();
	std::string getFont();
	bool hasButton();
	int getButtonNum();
	Button* getButtons();
	std::string getBgm();
	std::string getBg();
	std::string getConversationBg();
	std::string getVoice();
private:	
	int nextId;
	std::string context;
	std::string font="";
	bool hasBtn;
	int buttonNum;
	Button* buttons;
	std::string bgm = "";
	std::string bg = "";
	std::string conversationbg = "";
	std::string voice = "";
};

#endif // _STAGE_H_

/*
	int		id
	string	context
		string	font(null)
	bool	hasbutton
		int	buttonnum
			string buttonXcontext
			string buttonXfont(null)
			int	   buttonXnextid
	string bgm(null)
	string bg(null)
	string conversationbg(null)
	string voice(null)
	string nextid(if no button)
*/
