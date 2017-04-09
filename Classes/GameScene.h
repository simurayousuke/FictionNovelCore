#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include "GameCore.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(std::string titleString);

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	static std::string titleStr;
};



#endif // __Game_SCENE_H__
