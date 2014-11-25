//
//  Tile.h
//  Monster Radar
//
//  Created by Johnny Murphy on 14/03/2014.
//
//

#ifndef __Monster_Radar__Tile__
#define __Monster_Radar__Tile__

#include <iostream>
#include "cocos2d.h"

class Ball : public cocos2d::CCSprite
{
public:
    
    // Ball color
    int _m_iColor;
    
    // returns a pointer to new Ball instance.
    static Ball* create();

    void moveTo(int gridX, int gridY, bool kill);
    void deleteSelf();
    void doubleSelf();
    void bounce();
    
    void small();
    
    cocos2d::CCSize size;
    
    int currentGridX;
    int currentGridY;
    
    bool moved;
    
    int getPosX();
    int getPosY();
    
    int score;
    int Highscore;
    
    int currentNumber = 2;
    
    bool made = false;
    bool doubled = false;
};




#endif // __HELLOWORLD_SCENE_H__
