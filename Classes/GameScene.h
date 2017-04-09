#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include "GameCore.h"
#include "Stage.h"
#include "Config.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	//static cocos2d::Scene* createScene(std::string titleString);
	static cocos2d::Scene* createScene(Stage* stg);

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void buttonClickCallback(cocos2d::Ref* pSender,int id);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	static std::string titleStr;
	static Stage* stage;
	
};



#endif // __Game_SCENE_H__
