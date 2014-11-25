#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <string>


class MainGame : public cocos2d::CCLayer
{
    
    private:
    
        cocos2d::CCSize size;
        cocos2d::CCSprite* pSprite;
    
        cocos2d::CCMenuItemImage* ntPopUp;
        cocos2d::CCMenuItemImage* gameOver;
        cocos2d::CCSprite* NewTopTileSprite;
    
        int tileSize = 66;
    
        int topTile = 0;
    
        cocos2d::CCArray *tiles;
    
        bool board[4][4];
        Ball* tilesOnBoard[4][4];
        Ball* NewTilesOnBoard[4][4];
    
    cocos2d::CCLabelTTF* scoredisplay;
    
    cocos2d::CCSprite* fiveTwelve;
    

    

    public:
        // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
        virtual bool init();

        // there's no 'id' in cpp, so we recommend to return the class instance pointer
        static cocos2d::CCScene* scene();
        
        // a selector callback
        void didSwipe(CCObject* pSender);
    /*
        void sortRight();
        void sortLeft();
    
        void sortUp();
        void sortDown();
    
    */
    
        bool move = false;
    
        bool isLine(int x, int y, int j);
        bool isLineLeft(int i, int j, int m);
        bool isLineUp(int i, int j, int m);
        bool isLineDown(int i, int j, int m);
    
        void menuCloseCallback(CCObject* pSender);
    
        void newTile();
    
        void backToChosen();
    
        void closePopUp();
        void openPopUp();
    
    
        void endGame();
        void end();
    
        void replay();

        CREATE_FUNC(MainGame);
    

};


#endif // __MainGame_SCENE_H__
