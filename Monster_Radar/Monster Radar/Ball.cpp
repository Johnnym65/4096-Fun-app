#include "Ball.h"
#include "MainGame.h"


//created the new Tile
Ball* Ball::create()
{
    Ball *pSprite = new Ball();
    
    pSprite->autorelease();
        
    return pSprite;
   
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

//Moves the tile to designated location
void Ball::moveTo(int gridX, int gridY, bool kill){
    size = cocos2d::CCDirector::sharedDirector()->getWinSize();
    
    if(currentGridX!= gridX || currentGridY != gridY)
    {
        MainGame* h = dynamic_cast<MainGame*>(this->getParent());
        h->move = true;
        //float d = static_cast<float>(j)/v;
    }
    
    
    currentGridX = gridX;
    currentGridY = gridY;
    
    
    //move tile
    this->runAction(cocos2d::CCMoveTo::create(.15f, ccp(size.width/2-198 + (132* gridX), size.height/2+198 - (132*gridY)) ));
    
   
    //if tile should be deleted, then delete tile
    if(kill)
    {
        this->scheduleOnce(cocos2d::SEL_SCHEDULE(&Ball::deleteSelf), .15f);
    }
    
}

//get current x position of tile
int Ball::getPosX(){
    return getPosition().x;
}

//get current y position of tile
int Ball::getPosY(){
    return getPosition().y;
}

//double the tile value eg from 16 to 32
void Ball::doubleSelf(){
    
    this->setZOrder(3);
    currentNumber *=2;
    std::stringstream ss;
    ss << currentNumber;
    std::string str = ss.str();
    
    std::string imageName = str+".png";
    
    this->setTexture(cocos2d::CCTextureCache::sharedTextureCache()->addImage(imageName.c_str()));
    
    
    
    
}

//makes the tile 'bounce' when its doubled
void Ball::bounce(){
    this->runAction(cocos2d::CCScaleTo::create(.15f, 1.2));
    this->scheduleOnce(cocos2d::SEL_SCHEDULE(&Ball::small), .15f);
}
void Ball::small(){
    this->runAction(cocos2d::CCScaleTo::create(.15f, 1));
}
//deletes self
void Ball::deleteSelf(){
    this->getParent()->removeChild(this);
}