#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    cout << "hello" << endl;
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(backgroundSprite);
    

    scoreLabel = Label::createWithTTF("Score:0", "fonts/Marker Felt.ttf",48);
    
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Vec2(origin.x+visibleSize.width - scoreLabel ->getContentSize().width,
                            origin.y+visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    _player = Sprite::create("player-hd.png");
    _player->setPosition(visibleSize.width/8,visibleSize.height/2);
    this->addChild(_player);
    
    this->schedule(schedule_selector(HelloWorld::addMonster), 1);
    
    touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->setSwallowTouches(false);
    touch_listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touch_listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
    
    EventListenerPhysicsContact *contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

static int j = 0;

bool HelloWorld::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point touchLocation = pTouch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    Sprite* projectileExmaple = Sprite::create("projectile-hd.png");
    j+=1;
    auto OneBody = PhysicsBody::createBox(projectileExmaple->getContentSize());
    OneBody->setContactTestBitmask(0x04);
    
    OneBody->setTag(-1);
    
    projectileExmaple->setPhysicsBody(OneBody);
    projectileExmaple->setPosition(visibleSize.width/8,visibleSize.height/2);
    projectile.push_back(projectileExmaple);
    this->addChild(projectile.back(),j);
    Point offset    = ccpSub(touchLocation, _player->getPosition());
    float ratio     = offset.y/offset.x;
    int targetX   = _player->getContentSize().width/2 + visibleSize.width;
    int targetY   = (targetX*ratio) + _player->getPosition().y;
    Vec2 targetPosition = Vec2(targetX,targetY);
    MoveTo* Move = MoveTo::create(2, targetPosition);
    projectile.back()->runAction(Move);
    return true;

}
void HelloWorld::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}
void HelloWorld::onTouchEnded(Touch* pTouch, Event* pEvent)
{
}

static int i = 0;
void HelloWorld::addMonster(float dt){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* MonsterExample = Sprite::create("monster-hd.png");
    i = i+1;
    auto OneBody = PhysicsBody::createBox(MonsterExample->getContentSize());
    OneBody->setContactTestBitmask(0x08);
    
    OneBody->setTag(1);
    
    MonsterExample->setPhysicsBody(OneBody);
    MonsterExample->setPosition(
                                visibleSize.width + MonsterExample->getContentSize().width,
                                MonsterExample->getContentSize().height/2+CCRANDOM_0_1()*(visibleSize.height - MonsterExample->getContentSize().height/2));
    monster.push_back(MonsterExample);
    this->addChild(monster.back(),i);
    MoveTo* Move = MoveTo::create(3, Vec2(-monster.back()->getContentSize().width/2,monster.back()->getPosition().y));
    monster.back()->runAction(Move);

    
}

static int score = 0;

bool HelloWorld::onContactBegin(const cocos2d::PhysicsContact& contact){
    
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if (a->getTag()+b->getTag()==0) {
        HelloWorld::updateScoreLabel(++score);
    }
    

    this->removeChild(a->getNode());
    this->removeChild(b->getNode());
    return true;
    
}


void HelloWorld::updateScoreLabel(int score){
    std::stringstream ss;
    ss << "Score:" << score;
    scoreLabel->setString(ss.str());
    
}
