//
//  StartScreen.cpp
//  Monster Radar
//
//  Created by Johnny Murphy on 21/03/2014.
//
//

#include "StartScreen.h"
#include "MainGame.h"

#include "SimpleAudioEngine.h"
#include "Ball.h"
#include "CCSwipeGestureRecognizer.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* StartScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScreen *layer = StartScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    //swipe gesture
    CCSwipeGestureRecognizer * swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(StartScreen::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionLeft| kSwipeGestureRecognizerDirectionUp| kSwipeGestureRecognizerDirectionDown);
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    CCLog("size");
    std::cout<<size.width;
    
    
    //Background image
    std::string s1 = "startScreenBG.png";
    pSprite = CCSprite::create(s1.c_str());
    pSprite->setPosition(ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    
    
    
    //tutorial image which appears if its the users first time playing
    tutorial = CCMenuItemImage::create(
                                       "tutorial.png",
                                       "tutorial.png",
                                       this,
                                       menu_selector(StartScreen::endTut));
    tutorial->setPosition(ccp(0,0));
    tutorial->setOpacity(0);
    tutorial->setEnabled(false);
    
    
    
    
    //Tutorial image is set as a button so user can touch to skip
    CCMenu* menu = CCMenu::create();
    menu->addChild(tutorial,1000);
    this->addChild(menu,1000);
    

    
    //checks to see if the user has played before using local attribute on phone. if they are new it sets default high tile as 64
    
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("playedBefore", false))
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("highTile", 64);
        
        CCUserDefault::sharedUserDefault()->flush();
        
        firstime = true;
    }

    
    
    //The motivation text
    ttf1 = CCLabelTTF::create("Come on you can at least get 128!", "Helvetica", 20,
                                          CCSizeMake(500, 32), kCCTextAlignmentCenter);
    ttf1->setColor(ccc3(0,0,0));
    ttf1->setPosition(ccp(size.width/2, size.height/2+340));
    this->addChild(ttf1, 50);
    
    
    
    
    
    //the start page when the app opens initially
    startPage = CCSprite::create("startImage.png");
    startPage->setPosition(ccp(size.width/2, size.height/2) );
    this->addChild(startPage, 10000);
    
    //calls 'removeStartPage' after 2 seconds
    this->scheduleOnce(cocos2d::SEL_SCHEDULE(&StartScreen::removeStartPage), 2.0f);
    
       return true;
}

void StartScreen::removeStartPage(){
    
    //removes startpage
     startPage->runAction(cocos2d::CCFadeTo::create(.1f, 0));
    
    //gets the 'high tile' number from local storage
    int highTile = CCUserDefault::sharedUserDefault()->getIntegerForKey("highTile");
    
    //show hightile for 128
    if(highTile == 128){
        CCSprite* oneTwoEight = CCSprite::create("128.png");
        oneTwoEight->setScale(1.05);
        oneTwoEight->setPosition(ccp(size.width/2 - 128, size.height/2 +253) );
        this->addChild(oneTwoEight);
        
        ttf1->setString("Only 128? that's Pathetic!");
    }
    
    //show hightile for 256 and lower
    if(highTile == 256){
        CCSprite* oneTwoEight = CCSprite::create("128.png");
        oneTwoEight->setScale(1.05);
        oneTwoEight->setPosition(ccp(size.width/2 - 128, size.height/2 +253) );
        this->addChild(oneTwoEight, -1);
        
        CCSprite* twofivesix = CCSprite::create("256.png");
        twofivesix->setScale(1.05);
        twofivesix->setPosition(ccp(size.width/2 + 128, size.height/2 +253) );
        this->addChild(twofivesix,-1);
        
        ttf1->setString("256 is a good start, still not great");
    }
    
    //show hightile for 512 and lower
    if(highTile == 512){
        CCSprite* oneTwoEight = CCSprite::create("128.png");
        oneTwoEight->setScale(1.05);
        oneTwoEight->setPosition(ccp(size.width/2 - 128, size.height/2 +253) );
        this->addChild(oneTwoEight);
        
        CCSprite* twofivesix = CCSprite::create("256.png");
        twofivesix->setScale(1.05);
        twofivesix->setPosition(ccp(size.width/2 + 128, size.height/2 +253) );
        this->addChild(twofivesix);
        
        CCSprite* fiveTwelve = CCSprite::create("512.png");
        fiveTwelve->setScale(1.05);
        fiveTwelve->setPosition(ccp(size.width/2 - 128, size.height/2+70) );
        this->addChild(fiveTwelve);
        
        ttf1->setString("Now were talking! 512 is impressive");
    }
    
    //show hightile for 1024 and lower
    if(highTile == 1024){
        CCSprite* oneTwoEight = CCSprite::create("128.png");
        oneTwoEight->setScale(1.05);
        oneTwoEight->setPosition(ccp(size.width/2 - 128, size.height/2 +253) );
        this->addChild(oneTwoEight);
        
        CCSprite* twofivesix = CCSprite::create("256.png");
        twofivesix->setScale(1.05);
        twofivesix->setPosition(ccp(size.width/2 + 128, size.height/2 +253) );
        this->addChild(twofivesix);
        
        CCSprite* fiveTwelve = CCSprite::create("512.png");
        fiveTwelve->setScale(1.05);
        fiveTwelve->setPosition(ccp(size.width/2 - 128, size.height/2+70) );
        this->addChild(fiveTwelve);
        
        CCSprite* onezeroTwoFour = CCSprite::create("1024.png");
        onezeroTwoFour->setScale(1.05);
        onezeroTwoFour->setPosition(ccp(size.width/2 + 128, size.height/2+70) );
        this->addChild(onezeroTwoFour);
        
        ttf1->setString("1024! brilliant work, Dont quit");
    }
    
    
    //show hightile for 2048 and lower
    if(highTile == 2048){
        
        CCSprite* oneTwoEight = CCSprite::create("128.png");
        oneTwoEight->setScale(1.05);
        oneTwoEight->setPosition(ccp(size.width/2 - 128, size.height/2 +253) );
        this->addChild(oneTwoEight);
        
        CCSprite* twofivesix = CCSprite::create("256.png");
        twofivesix->setScale(1.05);
        twofivesix->setPosition(ccp(size.width/2 + 128, size.height/2 +253) );
        this->addChild(twofivesix);
        
        CCSprite* fiveTwelve = CCSprite::create("512.png");
        fiveTwelve->setScale(1.05);
        fiveTwelve->setPosition(ccp(size.width/2 - 128, size.height/2+70) );
        this->addChild(fiveTwelve);
        
        CCSprite* onezeroTwoFour = CCSprite::create("1024.png");
        onezeroTwoFour->setScale(1.05);
        onezeroTwoFour->setPosition(ccp(size.width/2 + 128, size.height/2+70) );
        this->addChild(onezeroTwoFour);
        
        CCSprite* twozerofoureight = CCSprite::create("2048.png");
        twozerofoureight->setScale(1.05);
        twozerofoureight->setPosition(ccp(size.width/2 - 128, size.height/2-122) );
        this->addChild(twozerofoureight);
        
        ttf1->setString("2048! you should quit..");
    }
    
    
    //show hightile for 4096 and lower
    if(highTile == 4096){
        CCSprite* oneTwoEight = CCSprite::create("128.png");
        oneTwoEight->setScale(1.05);
        oneTwoEight->setPosition(ccp(size.width/2 - 128, size.height/2 +253) );
        this->addChild(oneTwoEight);
        
        CCSprite* twofivesix = CCSprite::create("256.png");
        twofivesix->setScale(1.05);
        twofivesix->setPosition(ccp(size.width/2 + 128, size.height/2 +253) );
        this->addChild(twofivesix);
        
        CCSprite* fiveTwelve = CCSprite::create("512.png");
        fiveTwelve->setScale(1.05);
        fiveTwelve->setPosition(ccp(size.width/2 - 128, size.height/2+70) );
        this->addChild(fiveTwelve);
        
        CCSprite* onezeroTwoFour = CCSprite::create("1024.png");
        onezeroTwoFour->setScale(1.05);
        onezeroTwoFour->setPosition(ccp(size.width/2 + 128, size.height/2+70) );
        this->addChild(onezeroTwoFour);
        
        CCSprite* twozerofoureight = CCSprite::create("2048.png");
        twozerofoureight->setScale(1.05);
        twozerofoureight->setPosition(ccp(size.width/2 - 128, size.height/2-122) );
        this->addChild(twozerofoureight);
        
        CCSprite* fourzeroninesix = CCSprite::create("4096.png");
        fourzeroninesix->setScale(1.05);
        fourzeroninesix->setPosition(ccp(size.width/2 + 128, size.height/2-122) );
        this->addChild(fourzeroninesix);
        
        
        ttf1->setString("congratulations, you have no Life!!");
    }

    
}


void StartScreen::didSwipe(CCObject* pSender)
{
    //callback method for when a swipe is detected
    
    CCSwipe* swipe = dynamic_cast<CCSwipe*>(pSender);
    
    //if the user swiped left
    if(swipe->direction == kSwipeGestureRecognizerDirectionLeft)
    {
        //if has not played before
        if(!CCUserDefault::sharedUserDefault()->getBoolForKey("playedBefore", false))
        {
            //show tutorial image
            openTut();
        
            ttf1->setVisible(false);
            this->scheduleOnce(cocos2d::SEL_SCHEDULE(&StartScreen::endTut), 10.0f);
            
            //set local attribute "played before" to true
            CCUserDefault::sharedUserDefault()->setBoolForKey("playedBefore", true);
            
            CCUserDefault::sharedUserDefault()->flush();
            
           
        }
        else{
            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFadeBL::create(1, MainGame::scene()));
        }
        
        
    }
  
}

//show tutorial image
void StartScreen::openTut(){
    tutorial->setEnabled(true);
    tutorial->runAction(cocos2d::CCFadeTo::create(.15f, 255));
   
    
}

//get rid of tutorial image and start game 
void StartScreen::endTut(){
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFadeBL::create(1, MainGame::scene()));
}
