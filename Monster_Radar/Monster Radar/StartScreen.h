//
//  StartScreen.h
//  Monster Radar
//
//  Created by Johnny Murphy on 21/03/2014.
//
//

#ifndef __Monster_Radar__StartScreen__
#define __Monster_Radar__StartScreen__

#include "cocos2d.h"
#include "Ball.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <string>


class StartScreen : public cocos2d::CCLayer
{
    
private:
    
    cocos2d::CCSize size;
    
    cocos2d::CCSprite* pSprite;
    cocos2d::CCSprite* startPage;
    
    cocos2d::CCMenuItemImage* tutorial;
    
    bool firstime = false;
    cocos2d::CCLabelTTF* ttf1;
    
        /*
     cocos2d::CCSprite* radarPointer;
     cocos2d::CCSprite* searching;
     cocos2d::CCMenuItemImage *startSearch;
     bool bigsmall;
     
     cocos2d::CCSprite* radar;
     cocos2d::CCSprite* squareRadar;
     
     cocos2d::CCSprite* z1;
     cocos2d::CCSprite* z2;
     
     cocos2d::CCSprite* sleeper;
     cocos2d::CCMenuItemImage *searchAgain;
     
     cocos2d::CCSprite* result;
     cocos2d::CCSprite* noMonsters;
     
     
     
     
     
     bool iphone5;
     bool iphone4;
     bool iphone4s;
     bool ipad;
     
     std::string device;
     
     
     int scaleY;*/
    
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void didSwipe(CCObject* pSender);
    
    void openTut();
    void endTut();
    
    void removeStartPage();
    /*
     void sortRight();
     void sortLeft();
     
     void sortUp();
     void sortDown();
     
     */

    
    /*   void start();
     void searchingBig();
     
     void searchFinished();
     void searchResult();
     void makeZs();
     
     void searchA();*/
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(StartScreen);
    
    
};


#endif /* defined(__Monster_Radar__StartScreen__) */
