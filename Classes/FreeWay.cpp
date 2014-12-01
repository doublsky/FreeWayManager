//
//  FreeWay.cpp
//  FreeWay
//
//  Created by Tony TAN on 9/19/14.
//
//

#include "FreeWay.h"
#include "car.h"
#include "FWGameover.h"

#define LANE_WIDTH 40.0f
#define SLOW_SPEED 3.0f
#define NORMAL_SPEED 5.0f
#define FAST_SPEED 7.0f

#define CAR_LAYER 100

USING_NS_CC;

bool FreeWay::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    //enable the return button in Android
    setKeypadEnabled(true);
    
    //there is no car in the waiting list at beginning
    numOfNormalInWaitingList = 0;
    numOfSlowInWaitingList = 0;
    numOfFastInWaitingList = 0;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //add a background, aka the road
    CCSprite *background = CCSprite::create("background.png");
    background->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    addChild(background);
    
    // three buttons for adding cars
    CCMenuItemImage *pAddSlowCar = CCMenuItemImage::create("car_slow_button.png",
                                                          "car_slow_button.png",
                                                          this,
                                                          menu_selector(FreeWay::menuAddSlowCarCallback));
    
	pAddSlowCar->setPosition(ccp(origin.x + visibleSize.width - pAddSlowCar->getContentSize().width/2-30 ,
                                 origin.y + pAddSlowCar->getContentSize().height));
    
    CCMenuItemImage *pAddNormalCar = CCMenuItemImage::create("car_normal_button.png",
                                                             "car_normal_button.png",
                                                             this,
                                                             menu_selector(FreeWay::menuAddNormalCarCallback));
    
	pAddNormalCar->setPosition(ccp(origin.x + visibleSize.width - pAddNormalCar->getContentSize().width/2-30 ,
                                   origin.y + pAddNormalCar->getContentSize().height*2+30));
    
    CCMenuItemImage *pAddFastCar = CCMenuItemImage::create("car_fast_button.png",
                                                           "car_fast_button.png",
                                                           this,
                                                           menu_selector(FreeWay::menuAddFastCarCallback));
    
	pAddFastCar->setPosition(ccp(origin.x + visibleSize.width - pAddFastCar->getContentSize().width/2-30 ,
                                 origin.y + pAddFastCar->getContentSize().height*3+60));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pAddSlowCar, pAddNormalCar, pAddFastCar, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 2, 600);
    
    //initial the car lsit
    carList = CCArray::create();
    carList->retain();          //for autorelease, otherwise it will be reclaim immediately
    
    //add a layer as a container of all cars
    CCNode *carContainer = CCNode::create();
    addChild(carContainer, 1, CAR_LAYER);
    
    //CCArray *children = carContainer->getChildren();
    //CCLog("num of children = %d", children->count());
    
    //show the number of cars in waiting list
    char s[50];
    
    sprintf(s, "%d", numOfSlowInWaitingList);
    CCLabelTTF *slowCar = CCLabelTTF::create(s, "Arial", 24);
    slowCar->setPosition(ccp(origin.x + visibleSize.width - pAddSlowCar->getContentSize().width,
                             origin.y + pAddSlowCar->getContentSize().height));
    slowCar->setColor(ccBLACK);
    addChild(slowCar, 2, 700);
    
    sprintf(s, "%d", numOfNormalInWaitingList);
    CCLabelTTF *normalCar = CCLabelTTF::create(s, "Arial", 24);
    normalCar->setPosition(ccp(origin.x + visibleSize.width - pAddSlowCar->getContentSize().width,
                             origin.y + pAddSlowCar->getContentSize().height*2+30));
    normalCar->setColor(ccBLACK);
    addChild(normalCar, 2, 800);
    
    sprintf(s, "%d", numOfFastInWaitingList);
    CCLabelTTF *fastCar = CCLabelTTF::create(s, "Arial", 24);
    fastCar->setPosition(ccp(origin.x + visibleSize.width - pAddSlowCar->getContentSize().width,
                             origin.y + pAddSlowCar->getContentSize().height*3+60));
    fastCar->setColor(ccBLACK);
    addChild(fastCar, 2, 900);
    
    //start adding cars in waiting list, in different frequency
    schedule(schedule_selector(FreeWay::addSlowCarInWL), 1.0f);
    schedule(schedule_selector(FreeWay::addNormalCarInWL), 0.5f);
    schedule(schedule_selector(FreeWay::addFastCarInWL), 0.35f);
    
    return true;
}

void FreeWay::addSlowCarInWL(float dt)
{
    if (CCRANDOM_0_1() > 0.4)
    {
        addCarInWL(SLOWCAR);
    }
}

void FreeWay::addNormalCarInWL(float dt)
{
    if (CCRANDOM_0_1() > 0.3)
    {
        addCarInWL(NORMALCAR);
    }
}

void FreeWay::addFastCarInWL(float dt)
{
    if (CCRANDOM_0_1() > 0.2)
    {
        addCarInWL(FASTCAR);
    }
}

void FreeWay::addCarInWL(carKind kind)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (numOfSlowInWaitingList > 59 || numOfNormalInWaitingList > 59 || numOfFastInWaitingList > 59)
    {
        FWGameover *GOLayer = FWGameover::create();
        GOLayer->ignoreAnchorPointForPosition(false);
        GOLayer->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
        addChild(GOLayer, 3);
        CCDirector::sharedDirector()->getScheduler()->unscheduleAll();
        removeChildByTag(600);
        removeChildByTag(700);
        removeChildByTag(800);
        removeChildByTag(900);
    }
    else
    {
        switch (kind)
        {
            case SLOWCAR:
                if (numOfSlowInWaitingList < 60)
                {
                    numOfSlowInWaitingList++;
                    char s[50];                 //also remember to change the number on screen
                    sprintf(s, "%d", numOfSlowInWaitingList);
                    CCLabelTTF *plabel = (CCLabelTTF*)getChildByTag(700);
                    plabel->setString(s);
                }
                break;
            case NORMALCAR:
                if (numOfNormalInWaitingList < 60)
                {
                    numOfNormalInWaitingList++;
                    char s[50];                   //also remember to change the number on screen
                    sprintf(s, "%d", numOfNormalInWaitingList);
                    CCLabelTTF *plabel = (CCLabelTTF*)getChildByTag(800);
                    plabel->setString(s);
                }
            case FASTCAR:
                if (numOfFastInWaitingList < 60)
                {
                    numOfFastInWaitingList++;
                    char s[50];                   //also remember to change the number on screen
                    sprintf(s, "%d", numOfFastInWaitingList);
                    CCLabelTTF *plabel = (CCLabelTTF*)getChildByTag(900);
                    plabel->setString(s);
                }
                
            default:
                break;
        }
 
    }
    
}

void FreeWay::menuAddSlowCarCallback(cocos2d::CCObject *pSender)
{
    if (numOfSlowInWaitingList > 0)
    {
        numOfSlowInWaitingList--;
        char s[50];                 //also remember to change the number on screen
        sprintf(s, "%d", numOfSlowInWaitingList);
        CCLabelTTF *plabel = (CCLabelTTF*)getChildByTag(700);
        plabel->setString(s);
        addCar(SLOW_SPEED);
    }
}

void FreeWay::menuAddNormalCarCallback(cocos2d::CCObject *pSender)
{
    if (numOfNormalInWaitingList > 0)
    {
        numOfNormalInWaitingList--;
        char s[50];                   //also remember to change the number on screen
        sprintf(s, "%d", numOfNormalInWaitingList);
        CCLabelTTF *plabel = (CCLabelTTF*)getChildByTag(800);
        plabel->setString(s);
        addCar(NORMAL_SPEED);
    }
}

void FreeWay::menuAddFastCarCallback(cocos2d::CCObject *pSender)
{
    if (numOfFastInWaitingList > 0)
    {
        numOfFastInWaitingList--;
        char s[50];                   //also remember to change the number on screen
        sprintf(s, "%d", numOfFastInWaitingList);
        CCLabelTTF *plabel = (CCLabelTTF*)getChildByTag(900);
        plabel->setString(s);
        addCar(FAST_SPEED);
    }
}

void FreeWay::addCar(float speed)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCNode *container = (CCNode*) getChildByTag(CAR_LAYER);
    
    FWCar *car = FWCar::create("car_normal.png", speed);
    car->setAnchorPoint(ccp(0.5, 0.5));
    
    //for debugging
    //FWCar *car = FWCar::create("car_debug.png", speed);
    
    //column is the flag to show whether it is possible to place a car in this column
    int column[4];
    for (int i = 0; i < 4; i++)
    {
        column[i] = 0;      //initial with "no car"
    }
    
    //then we need to know which column is avaliable to place a car
    CCObject *pObject;
    //int debug_count = 0;
    CCARRAY_FOREACH(carList, pObject)
    {
        CCNode *pNode = (CCNode*)pObject;
        float YPosition = pNode->getPosition().y;
        float XPosition = pNode->getPosition().x;
        
        //if no car on screen, skip, all lanes are available
        if (container->getChildren()->count() == 0)
        {
            carList->removeAllObjects();
            break;
        }
        
        //remove the cars that are too far from entrance
        if (pNode && YPosition > origin.y+car->getContentSize().height*3)
        {
            //CCLog("remove this node: %lx", pNode);
            carList->removeObject(pNode);
            continue;
        }
        //if a car is around the entrance
        if (YPosition < pNode->getContentSize().height*2)
        {
            if (XPosition >= visibleSize.width/2-LANE_WIDTH*2 && XPosition <= visibleSize.width/2-LANE_WIDTH)
            {
                column[0] = 1;
            }
            else if (XPosition >= visibleSize.width/2-LANE_WIDTH && XPosition <= visibleSize.width/2)
            {
                column[1] = 1;
            }
            else if (XPosition >= visibleSize.width/2 && XPosition <= visibleSize.width/2+LANE_WIDTH)
            {
                column[2] = 1;
            }
            else
            {
                column[3] = 1;
            }
        }
        //debug_count++;
    }
    //CCLog("%d cars visited", debug_count);
    
    if (column[0]*column[1]*column[2]*column[3])
    {
        if (speed < 4.0f)
        {
            numOfSlowInWaitingList++;
        }
        else if (speed < 6.0f)
        {
            numOfNormalInWaitingList++;
        }
        else
        {
            numOfFastInWaitingList++;
        }
        return;     //all lanes are occupied
    }
    //else create a random number from 0 to 3
    int random = CCRANDOM_0_1() * 4;
    //CCLog("random = %d", random);
    
    //keep searching until a available spot is found
    while (1)
    {
        if (column[random] == 0)
        {
            car->lane = random;
            car->setPosition(ccp(origin.x+visibleSize.width/2+LANE_WIDTH*((float)random-1.5), origin.y+0));
            break;
        }
        random = CCRANDOM_0_1() * 4;
    }
    
    carList->addObject(car);
    container->addChild(car);
    //numOfCar++;
    
    //add movement, for debugging
    //CCActionInterval *drive = CCMoveBy::create(2.0f, ccp(0, visibleSize.height+car->getContentSize().height/2));
    //car->runAction(drive);
}

void FreeWay::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
}
