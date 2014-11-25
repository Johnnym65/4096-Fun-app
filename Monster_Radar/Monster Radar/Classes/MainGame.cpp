#include "MainGame.h"
#include "SimpleAudioEngine.h"
#include "Ball.h"
#include "StartScreen.h"
#include "CCSwipeGestureRecognizer.h"




using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainGame *layer = MainGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    
    //creating and initialising swipe gesture recogniser
    CCSwipeGestureRecognizer * swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(MainGame::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionLeft| kSwipeGestureRecognizerDirectionUp| kSwipeGestureRecognizerDirectionDown);
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    CCLog("size");
    std::cout<<size.width;
    
    
    //setting background
    std::string s1 = "background-iphone5.png";
    pSprite = CCSprite::create(s1.c_str());
    pSprite->setPosition(ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    
    
    
    
    //ntPopUp->setOpacity(255);
    
    
    
    //back button
    CCMenuItemImage* back = CCMenuItemImage::create(
                                                    "backtomenu.png",
                                                    "backtomenu.png",
                                                    this,
                                                    menu_selector(MainGame::backToChosen));
    back->setPosition(ccp(0,360));

    
    //new tile pop up image, pop up that appears when a new tile is reached
    ntPopUp = CCMenuItemImage::create(
                                      "newTilePopUp.png",
                                      "newTilePopUp.png",
                                      this,
                                      menu_selector(MainGame::closePopUp));
    ntPopUp->setPosition(ccp(0,0));
    ntPopUp->setOpacity(0);
    
    
    
    //game over pop up that appears when the game is over
    gameOver = CCMenuItemImage::create(
                                      "gameOver.png",
                                      "gameOver.png",
                                      this,
                                      menu_selector(MainGame::replay));
    gameOver->setPosition(ccp(0,0));
    gameOver->setOpacity(0);
    gameOver->setEnabled(false);
    
  
    
    
    CCMenu* menu = CCMenu::create();
    menu->addChild(back,100);
    menu->addChild(ntPopUp,1100);
    menu->addChild(gameOver,1000);

    this->addChild(menu,1000);
    
    
    //tile image at the bottom which shows your highest tile for the current game
    NewTopTileSprite = CCSprite::create("2.png");
    NewTopTileSprite->setScale(2.5);
    NewTopTileSprite->setOpacity(0);
    NewTopTileSprite->setPosition(ccp(size.width/2, size.height/2) );
    this->addChild(NewTopTileSprite, 1001);
    
    
    /*int hscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore");
    
    if(!hscore){
        hscore = 0;
    }
    
    std::stringstream ss;
    ss << hscore;
    std::string str = ss.str();
    
    
    //timeholder.insert(2,":");
    
    std::string s = "hello";*/
    
   
    
    
    
   
    
    
    
    
    
    
    
    
    //initialising the tile array
    tiles = new CCArray;
    
    
    //creates a 4*4 matrix or a 2d array.
    
	for(int i=0; i<4; i++)    //This loops on the rows.
	{
		for(int j=0; j<4; j++) //This loops on the columns
		{
			//board[i][j] = false; //you can also connect to the file
			//and place the name of your ifstream in the input after opening the file will
			//let you read from the file.
            tilesOnBoard[i][j] = NULL;
            NewTilesOnBoard[i][j] = NULL;
		}
	}
    
    //start with 2 tiles
    newTile();
    newTile();
    
    
    fiveTwelve = CCSprite::create("2.png");
    fiveTwelve->setPosition(ccp(size.width/2, size.height/2-409) );
    this->addChild(fiveTwelve, 1);
    
    
    
    
        CCLog("size");
    std::cout<<size.width;


    return true;
}


//sends the user back to start startscreen
void MainGame::backToChosen()
{
   
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, StartScreen::scene()));
}

//new tile reached pop up is shown
void MainGame::openPopUp()
{
    ntPopUp->setEnabled(true);
    ntPopUp->runAction(cocos2d::CCFadeTo::create(.15f, 255));
    NewTopTileSprite->runAction(cocos2d::CCFadeTo::create(.15f, 255));
}

void MainGame::closePopUp()
{
    ntPopUp->runAction(cocos2d::CCFadeTo::create(.15f, 0));
    NewTopTileSprite->runAction(cocos2d::CCFadeTo::create(.15f, 0));
}


//schedules the game to end in .8 seconds
void MainGame::endGame(){
    this->scheduleOnce(cocos2d::SEL_SCHEDULE(&MainGame::end), .8f);
    
}

//shows the game over pop up
void MainGame::end(){
    gameOver->runAction(cocos2d::CCFadeTo::create(.15f, 255));
    ntPopUp->setEnabled(false);
    gameOver->setEnabled(true);
}

//replay button clicked
void MainGame::replay(){
    
    
    
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, MainGame::scene()));
    
}

//when a swipe gesture is detected
void MainGame::didSwipe(CCObject* pSender)
{
    CCSwipe* swipe = dynamic_cast<CCSwipe*>(pSender);
    
    
    //if swipe is right then move tiles right
    if(swipe->direction == kSwipeGestureRecognizerDirectionRight)
    {
        
        
        
        for(int i=3; i>=0; i--)    //This loops on the rows.
        {
            for(int j=0; j<4; j++) //This loops on the columns
            {
                if(tilesOnBoard[i][j])
                {
                    //if(i == 0 && j ==2)
                    //{
                        for(int t=0; t<4; t++) //This loops on the columns
                        {
                            for(int p=0; p<4; p++) //This loops on the columns
                            {
                                if(NewTilesOnBoard[t][p])
                                {
                                    std::stringstream ss;
                                    ss << t;
                                    std::string str = ss.str();
                                    
                                    std::stringstream sss;
                                    sss << p;
                                    std::string str1 = sss.str();
                                    
                                    std::string s = "tilesOnBoard["+str+"]["+str1+"]";
                                    
                                    CCLog(s.c_str());
                                }
                            }
                       // }
                        
                    }
                    CCLog("-------------");
                    if(NewTilesOnBoard[3][j]){
                        
                        if(NewTilesOnBoard[3][j]->currentNumber == tilesOnBoard[i][j]->currentNumber && isLine(i, j, 3) && !NewTilesOnBoard[3][j]->doubled)
                        {
                            NewTilesOnBoard[3][j]->doubleSelf();
                            NewTilesOnBoard[3][j]->doubled = true;
                            NewTilesOnBoard[3][j]->bounce();
                            tilesOnBoard[i][j]->moveTo(3, j, true);
                            tilesOnBoard[i][j] = NULL;
                        }
                        
                        else if(NewTilesOnBoard[2][j]){
                            
                            if(NewTilesOnBoard[2][j]->currentNumber == tilesOnBoard[i][j]->currentNumber && isLine(i, j, 2)&& !NewTilesOnBoard[2][j]->doubled)
                            {
                                NewTilesOnBoard[2][j]->doubleSelf();
                                NewTilesOnBoard[2][j]->doubled = true;
                                NewTilesOnBoard[2][j]->bounce();
                                tilesOnBoard[i][j]->moveTo(2, j, true);
                                tilesOnBoard[i][j] = NULL;
                            }
                            
                            
                            else if(NewTilesOnBoard[1][j]){
                                
                                if(NewTilesOnBoard[1][j]->currentNumber == tilesOnBoard[i][j]->currentNumber && isLine(i, j, 1)&& !NewTilesOnBoard[1][j]->doubled)
                                {
                                    NewTilesOnBoard[1][j]->doubleSelf();
                                    NewTilesOnBoard[1][j]->doubled = true;
                                    NewTilesOnBoard[1][j]->bounce();
                                    tilesOnBoard[i][j]->moveTo(1, j, true);
                                    tilesOnBoard[i][j] = NULL;
                                }
                                
                                else if(NewTilesOnBoard[0][j]){
                                    
                                }
                                else
                                {
                                    tilesOnBoard[i][j]->moveTo(0, j, false);
                                    NewTilesOnBoard[0][j] = tilesOnBoard[i][j];
                                    NewTilesOnBoard[0][j]->made = true;
                                    tilesOnBoard[i][j] = NULL;
                                }
                                
                            }
                            else{
                                tilesOnBoard[i][j]->moveTo(1, j, false);
                                NewTilesOnBoard[1][j] = tilesOnBoard[i][j];
                                NewTilesOnBoard[1][j]->made = true;
                                tilesOnBoard[i][j] = NULL;
                                
                            }
                            
                        }
                        else
                        {
                            tilesOnBoard[i][j]->moveTo(2, j, false);
                            NewTilesOnBoard[2][j] = tilesOnBoard[i][j];
                            NewTilesOnBoard[2][j]->made = true;
                            tilesOnBoard[i][j] = NULL;
                            
                        }
                        
                    }
                    else{
                        tilesOnBoard[i][j]->moveTo(3, j, false);
                        NewTilesOnBoard[3][j] = tilesOnBoard[i][j];
                        NewTilesOnBoard[3][j]->made = true;
                        tilesOnBoard[i][j] = NULL;
                        
                    }
                }
                
                
            }
            
        }
        

        
        
        
        CCLog("swipeRight!");
    }
    
    
    
    
    
    
    
    
    //if swipe is left then move tiles right
    if(swipe->direction == kSwipeGestureRecognizerDirectionLeft)
    {
        
        
        
        for(int i=0; i<4; i++)    //This loops on the rows.
        {
            for(int j=0; j<4; j++) //This loops on the columns
            {
                if(tilesOnBoard[i][j])
                {
                    if(NewTilesOnBoard[0][j]){
                        
                        if(NewTilesOnBoard[0][j]->currentNumber == tilesOnBoard[i][j]->currentNumber && isLineLeft(i,j,0) && !NewTilesOnBoard[0][j]->doubled)
                        {
                            NewTilesOnBoard[0][j]->doubleSelf();
                            NewTilesOnBoard[0][j]->doubled = true;
                            NewTilesOnBoard[0][j]->bounce();
                            tilesOnBoard[i][j]->moveTo(0, j, true);
                            tilesOnBoard[i][j] = NULL;
                        }
                        
                        else if(NewTilesOnBoard[1][j]){
                            
                            if(NewTilesOnBoard[1][j]->currentNumber == tilesOnBoard[i][j]->currentNumber && isLineLeft(i,j,1) && !NewTilesOnBoard[1][j]->doubled)
                            {
                                NewTilesOnBoard[1][j]->doubleSelf();
                                NewTilesOnBoard[1][j]->doubled = true;
                                NewTilesOnBoard[1][j]->bounce();
                                tilesOnBoard[i][j]->moveTo(1, j, true);
                                tilesOnBoard[i][j] = NULL;
                            }
                            
                            else if(NewTilesOnBoard[2][j]){
                                
                                if(NewTilesOnBoard[2][j]->currentNumber == tilesOnBoard[i][j]->currentNumber && isLineLeft(i,j,2)&& !NewTilesOnBoard[2][j]->doubled)
                                {
                                    NewTilesOnBoard[2][j]->doubleSelf();
                                    NewTilesOnBoard[2][j]->doubled = true;
                                    NewTilesOnBoard[2][j]->bounce();
                                    tilesOnBoard[i][j]->moveTo(2, j, true);
                                    tilesOnBoard[i][j] = NULL;
                                }
                                
                                else if(NewTilesOnBoard[3][j]){
                                    
                                }
                                else{
                                    tilesOnBoard[i][j]->moveTo(3, j, false);
                                    NewTilesOnBoard[3][j] = tilesOnBoard[i][j];
                                    NewTilesOnBoard[3][j]->made = true;
                                    tilesOnBoard[i][j] = NULL;
                                }
                                
                                
                                
                            }
                            else{
                                tilesOnBoard[i][j]->moveTo(2, j, false);
                                NewTilesOnBoard[2][j] = tilesOnBoard[i][j];
                                NewTilesOnBoard[2][j]->made = true;
                                tilesOnBoard[i][j] = NULL;
                                
                            }
                            
                        }
                        else
                        {
                            tilesOnBoard[i][j]->moveTo(1, j, false);
                            NewTilesOnBoard[1][j] = tilesOnBoard[i][j];
                            NewTilesOnBoard[1][j]->made = true;
                            tilesOnBoard[i][j] = NULL;
                            
                        }
                        
                    }
                    else{
                        tilesOnBoard[i][j]->moveTo(0, j, false);
                        NewTilesOnBoard[0][j] = tilesOnBoard[i][j];
                        NewTilesOnBoard[0][j]->made = true;
                        tilesOnBoard[i][j] = NULL;
                        
                    }
                }
                
                
            }
            
        }

        
        CCLog("swipeLeft!");
    }
    
    
    
    
    
    
    
    
    
    //if swipe is up then move tiles right
    if(swipe->direction == kSwipeGestureRecognizerDirectionUp)
    {
        
        
        
        for(int i=0; i<4; i++)    //This loops on the rows.
        {
            for(int j=0; j<4; j++) //This loops on the columns
            {
                if(tilesOnBoard[j][i])
                {
                    if(NewTilesOnBoard[j][0]){
                        
                        if(NewTilesOnBoard[j][0]->currentNumber == tilesOnBoard[j][i]->currentNumber && isLineUp(j,i,0) && !NewTilesOnBoard[j][0]->doubled)
                        {
                            NewTilesOnBoard[j][0]->doubleSelf();
                            NewTilesOnBoard[j][0]->doubled = true;
                            NewTilesOnBoard[j][0]->bounce();
                            tilesOnBoard[j][i]->moveTo(j, 0, true);
                            tilesOnBoard[j][i] = NULL;
                        }
                        
                        else if(NewTilesOnBoard[j][1]){
                            
                            if(NewTilesOnBoard[j][1]->currentNumber == tilesOnBoard[j][i]->currentNumber && isLineUp(j,i,1) && !NewTilesOnBoard[j][1]->doubled)
                            {
                                NewTilesOnBoard[j][1]->doubleSelf();
                                NewTilesOnBoard[j][1]->doubled = true;
                                NewTilesOnBoard[j][1]->bounce();
                                tilesOnBoard[j][i]->moveTo(j, 1, true);
                                tilesOnBoard[j][i] = NULL;
                            }
                            
                            else if(NewTilesOnBoard[j][2]){
                                
                                if(NewTilesOnBoard[j][2]->currentNumber == tilesOnBoard[j][i]->currentNumber && isLineUp(j,i,2) && !NewTilesOnBoard[j][2]->doubled)
                                {
                                    NewTilesOnBoard[j][2]->doubleSelf();
                                    NewTilesOnBoard[j][2]->doubled = true;
                                    NewTilesOnBoard[j][2]->bounce();
                                    tilesOnBoard[j][i]->moveTo(j, 2, true);
                                    tilesOnBoard[j][i] = NULL;
                                }
                                
                                else if(NewTilesOnBoard[j][3]){
                                    
                                }
                                else{
                                    tilesOnBoard[j][i]->moveTo(j, 3, false);
                                    NewTilesOnBoard[j][3] = tilesOnBoard[j][i];
                                    NewTilesOnBoard[j][3]->made = true;
                                    tilesOnBoard[j][i] = NULL;
                                }
                                
                                
                            }
                            else{
                                tilesOnBoard[j][i]->moveTo(j, 2, false);
                                NewTilesOnBoard[j][2] = tilesOnBoard[j][i];
                                NewTilesOnBoard[j][2]->made = true;
                               tilesOnBoard[j][i] = NULL;
                                
                            }
                            
                        }
                        else
                        {
                            tilesOnBoard[j][i]->moveTo(j, 1, false);
                            NewTilesOnBoard[j][1] = tilesOnBoard[j][i];
                            NewTilesOnBoard[j][1]->made = true;
                            tilesOnBoard[j][i] = NULL;
                            
                        }
                        
                    }
                    else{
                        tilesOnBoard[j][i]->moveTo(j, 0, false);
                        NewTilesOnBoard[j][0] = tilesOnBoard[j][i];
                        NewTilesOnBoard[j][0]->made = true;
                        tilesOnBoard[j][i] = NULL;
                        
                    }
                }
                
                
            }
            
        }

        
        CCLog("swipeUp!");
    }
    
    
    
    
    
    
    //if swipe down right then move tiles right
    if(swipe->direction == kSwipeGestureRecognizerDirectionDown)
    {
        
        
        
        for(int i=3; i>=0; i--)    //This loops on the rows.
        {
            for(int j=0; j<4; j++) //This loops on the columns
            {
                if(tilesOnBoard[j][i])
                {
                    if(NewTilesOnBoard[j][3]){
                        
                        if(NewTilesOnBoard[j][3]->currentNumber == tilesOnBoard[j][i]->currentNumber && isLineDown(j,i,3) && !NewTilesOnBoard[j][3]->doubled)
                        {
                            NewTilesOnBoard[j][3]->doubleSelf();
                            NewTilesOnBoard[j][3]->doubled = true;
                            NewTilesOnBoard[j][3]->bounce();
                            tilesOnBoard[j][i]->moveTo(j, 3, true);
                            tilesOnBoard[j][i] = NULL;
                        }
                        
                        else if(NewTilesOnBoard[j][2]){
                            
                            if(NewTilesOnBoard[j][2]->currentNumber == tilesOnBoard[j][i]->currentNumber&& isLineDown(j,i,2)&& !NewTilesOnBoard[j][2]->doubled)
                            {
                                NewTilesOnBoard[j][2]->doubleSelf();
                                NewTilesOnBoard[j][2]->doubled = true;
                                NewTilesOnBoard[j][2]->bounce();
                                tilesOnBoard[j][i]->moveTo(j, 2, true);
                                tilesOnBoard[j][i] = NULL;
                            }
                            
                            else if(NewTilesOnBoard[j][1]){
                                
                                if(NewTilesOnBoard[j][1]->currentNumber == tilesOnBoard[j][i]->currentNumber && isLineDown(j,i,1)&& !NewTilesOnBoard[j][1]->doubled)
                                {
                                    NewTilesOnBoard[j][1]->doubleSelf();
                                    NewTilesOnBoard[j][1]->doubled = true;
                                    NewTilesOnBoard[j][1]->bounce();
                                    tilesOnBoard[j][i]->moveTo(j, 1, true);
                                    tilesOnBoard[j][i] = NULL;
                                }
                                
                                else if(NewTilesOnBoard[j][0]){
                                    
                                }
                                else{
                                    tilesOnBoard[j][i]->moveTo(j, 0, false);
                                    NewTilesOnBoard[j][0] = tilesOnBoard[j][i];
                                    NewTilesOnBoard[j][0]->made = true;
                                    tilesOnBoard[j][i] = NULL;
                                }
                                
                            }
                            else{
                                tilesOnBoard[j][i]->moveTo(j, 1, false);
                                NewTilesOnBoard[j][1] = tilesOnBoard[j][i];
                                NewTilesOnBoard[j][1]->made = true;
                                tilesOnBoard[j][i] = NULL;
                               
                            }
                            
                        }
                        else
                        {
                            tilesOnBoard[j][i]->moveTo(j, 2, false);
                            NewTilesOnBoard[j][2] = tilesOnBoard[j][i];
                            NewTilesOnBoard[j][2]->made = true;
                            tilesOnBoard[j][i] = NULL;
                            
                        }
                        
                    }
                    else{
                        tilesOnBoard[j][i]->moveTo(j, 3, false);
                        NewTilesOnBoard[j][3] = tilesOnBoard[j][i];
                        NewTilesOnBoard[j][3]->made = true;
                        tilesOnBoard[j][i] = NULL;
                        
                    }
                }
                
                
            }
            
        }
        
       
        
        CCLog("swipeUp!");
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
   
    
    for(int i=0; i<4; i++)    //This loops on the rows.
    {
        for(int j=0; j<4; j++) //This loops on the columns
        {
            tilesOnBoard[i][j] = NewTilesOnBoard[i][j];
            
            if(tilesOnBoard[i][j])
            {
                tilesOnBoard[i][j]->made = false;
                tilesOnBoard[i][j]->doubled = false;
                int temp =tilesOnBoard[i][j]->currentNumber;
                
                if(temp>topTile)
                {
                    topTile = temp;
                }
            }
            
            NewTilesOnBoard[i][j] = NULL;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    std::stringstream ss1;
    ss1 << topTile;
    std::string str1 = ss1.str();
    str1 += ".png";
    
    
    //chages high tile is new high tile is reached
    if(topTile > CCUserDefault::sharedUserDefault()->getIntegerForKey("highTile"))
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("highTile", topTile);
        CCUserDefault::sharedUserDefault()->flush();
        
        openPopUp();
        
        NewTopTileSprite->setTexture(cocos2d::CCTextureCache::sharedTextureCache()->addImage(str1.c_str()));
    }
    
    fiveTwelve->setTexture(cocos2d::CCTextureCache::sharedTextureCache()->addImage(str1.c_str()));
    
    
    
    
    
    
    
    
    //create new tile
    if(move)
    {
        newTile();
       
    }
    
    
    
        
    int count = 0;
    
    for(int i=0; i<4; i++)    //This loops on the rows.
    {
        for(int j=0; j<4; j++) //This loops on the columns
        {
            if(tilesOnBoard[i][j])
            {
                count++;
            }
        }
    }
    
    
    
    std::stringstream ss;
    ss << count;
    std::string str = ss.str();
    str += " Count";
    CCLOG(str.c_str());
    
    
    if(count == 16)
    {
        bool isFinished = true;
        
        for(int i=0; i<4; i++)    //This loops on the rows.
        {
            for(int j=0; j<4; j++) //This loops on the columns
            {
                if(i < 3){
                    if(tilesOnBoard[i+1][j])
                    {
                        if(tilesOnBoard[i+1][j]->currentNumber == tilesOnBoard[i][j]->currentNumber)
                        {
                            isFinished = false;
                        }
                    }
                }
                
                if(i >0){
                    if(tilesOnBoard[i-1][j])
                    {
                        if(tilesOnBoard[i-1][j]->currentNumber == tilesOnBoard[i][j]->currentNumber)
                        {
                            isFinished = false;
                        }
                    }
                }
                
                if(j < 3){
                    if(tilesOnBoard[i][j+1])
                    {
                        if(tilesOnBoard[i][j+1]->currentNumber == tilesOnBoard[i][j]->currentNumber)
                        {
                            isFinished = false;
                        }
                    }
                }
                
                if(j >0){
                    if(tilesOnBoard[i][j-1])
                    {
                        if(tilesOnBoard[i][j-1]->currentNumber == tilesOnBoard[i][j]->currentNumber)
                        {
                            isFinished = false;
                        }
                    }
                }
                
            }
        }
        
        if(isFinished){
            endGame();
        }
        
    }
    
    
    
    
    
    
}

//create a new tile in a random spot on the board that is free
void MainGame::newTile(){
    
    int rand1 = rand() % 4;
    int rand2 = rand() % 4;
    
    while(tilesOnBoard[rand1][rand2])
    {
        rand1 = rand() % 4;
        rand2 = rand() % 4;
    }
    
    
    
    Ball* tile1 = Ball::create();
    this->addChild(tile1, 1);
    tile1->initWithFile("2.png");
    tile1->moveTo(rand1, rand2, false);
    
    int fourOrTwo = rand() % 12;
    if(fourOrTwo>9)
    {
        tile1->doubleSelf();
    }
    
    
    //tiles->addObject(tile1);
    //board[2][0] = true;
    tilesOnBoard[rand1][rand2] = tile1;
    
    move = false;
    
}


void MainGame::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



//algorithm to check weather there is a free line from point x on the board to point y, used in the moving algorithm
bool MainGame::isLine(int x, int y, int j){
    

    
    
    
    for(int i = x+1; i < j; i++)
    {
        if(NewTilesOnBoard[i][y])
        {
            if(NewTilesOnBoard[i][y]->made);
            {
                std::stringstream ss;
                ss << i;
                std::string str = ss.str();
                
                std::stringstream sss;
                sss << y;
                std::string str1 = sss.str();
                
                std::string s = "NewTilesOnBoard["+str+"]["+str1+"]";
                
                CCLog(s.c_str());
               // NewTilesOnBoard[i][j]->doubleSelf();
                //CCLog("false");
                return false;
            }
        }
    }
     CCLog("true");
    return true;
    
   
    
   
    
    
}


bool MainGame::isLineLeft(int i, int j, int m){
    
    for(int z = i-1; z > m; z--)
    {
        if(NewTilesOnBoard[z][j])
        {
            if(NewTilesOnBoard[z][j]->made);
            {
                std::stringstream ss;
                ss << z;
                std::string str = ss.str();
                
                std::stringstream sss;
                sss << j;
                std::string str1 = sss.str();
                
                std::string s = "NewTilesOnBoard["+str+"]["+str1+"]";
                
                CCLog(s.c_str());
                // NewTilesOnBoard[i][j]->doubleSelf();
                //CCLog("false");
                return false;
            }
        }
    }
    CCLog("true");
    return true;
}


bool MainGame::isLineUp(int i, int j, int m){
    
    for(int z = j-1; z > m; z--)
    {
        if(NewTilesOnBoard[i][z])
        {
            if(NewTilesOnBoard[i][z]->made);
            {
                std::stringstream ss;
                ss << z;
                std::string str = ss.str();
                
                std::stringstream sss;
                sss << j;
                std::string str1 = sss.str();
                
                std::string s = "NewTilesOnBoard["+str+"]["+str1+"]";
                
                CCLog(s.c_str());
                // NewTilesOnBoard[i][j]->doubleSelf();
                //CCLog("false");
                return false;
            }
        }
    }
    CCLog("true");
    return true;
}


bool MainGame::isLineDown(int i, int j, int m){
    
    for(int z = j+1; z < m; z++)
    {
        if(NewTilesOnBoard[i][z])
        {
            if(NewTilesOnBoard[i][z]->made);
            {
                std::stringstream ss;
                ss << z;
                std::string str = ss.str();
                
                std::stringstream sss;
                sss << j;
                std::string str1 = sss.str();
                
                std::string s = "NewTilesOnBoard["+str+"]["+str1+"]";
                
                CCLog(s.c_str());
                // NewTilesOnBoard[i][j]->doubleSelf();
                //CCLog("false");
                return false;
            }
        }
    }
    CCLog("true");
    return true;
}





