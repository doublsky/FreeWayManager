//
//  FWEntrance.cpp
//  FreeWay
//
//  Created by Tony TAN on 11/25/14.
//
//

#include "FWEntrance.h"
#include "FWGameover.h"

#define FREN_OF_SLOW_CAR 1.0f
#define FREN_OF_NORMAL_CAR 2.0f
#define FREN_OF_FAST_CAR 3.0f

USING_NS_CC;

void FWEntrance::onEnter()
{
    // super init
    CCNode::onEnter();
    
    // then get the screen size
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //initial the cover, it is a sprite
    /*cover = CCSprite::create("TBD");
    cover->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+cover->getContentSize().height/2));
    addChild(cover);*/
    
    // schedual up the schedualor
    schedule(schedule_selector(FWEntrance::addSlowCarInWL), 1.0f/FREN_OF_SLOW_CAR);
    schedule(schedule_selector(FWEntrance::addNormalCarInWL), 1.0f/FREN_OF_NORMAL_CAR);
    schedule(schedule_selector(FWEntrance::addFastCarInWL), 1.0f/FREN_OF_FAST_CAR);
}

void FWEntrance::addSlowCarInWL(float dt)
{
    if (CCRANDOM_0_1() > 0.6)
    {
        addCarInWL(SLOWCAR);
    }
}

void FWEntrance::addNormalCarInWL(float dt)
{
    if (CCRANDOM_0_1() > 0.4)
    {
        addCarInWL(NORMALCAR);
    }}

void FWEntrance::addFastCarInWL(float dt)
{
    if (CCRANDOM_0_1() > 0.2)
    {
        addCarInWL(FASTCAR);
    }
}

void FWEntrance::addCarInWL(carKind kind)
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