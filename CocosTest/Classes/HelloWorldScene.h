#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


class HelloWorld : public cocos2d::Layer
{   
private:
    cocos2d::Sprite* _player;
    void addMonster(float dt);
    std::vector<cocos2d::Sprite*> monster;
    std::vector<cocos2d::Sprite*> projectile;
     bool onContactBegin(const cocos2d::PhysicsContact& contact);
    cocos2d::EventListenerTouchOneByOne *touch_listener;
    cocos2d::Label *scoreLabel;
    void updateScoreLabel(int score);

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    
    virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
