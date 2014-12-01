//
//  car.cpp
//  FreeWay
//
//  Created by Tony TAN on 9/19/14.
//
//

#include "car.h"
#include "FreeWay.h"

#define LANE_WIDTH 40.0f


USING_NS_CC;

FWCar* FWCar::create(const char *pszFileName, float speed)
{
    FWCar *pobSprite = new FWCar();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->maxspeed = speed;
        pobSprite->speed = pobSprite->maxspeed;
        pobSprite->shift = 0.0f;
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void FWCar::onEnter()
{
    //CCLog("onEnter is called");
    //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    //CCActionInterval *drive = CCMoveBy::create(2.0f, ccp(0, visibleSize.height+this->getContentSize().height/2));
    //this->runAction(drive);
    //scheduleUpdate();
    isNeededToDraw_left = false;
    isNeededToDraw_right = false;
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0,false);
}

void FWCar::update(float dt)
{
    //CCLog("updating position...");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    if (this->getPositionY() < origin.y+visibleSize.height+this->getContentSize().height*5)
    {
        this->setPositionY(this->getPositionY()+this->speed);       //default running
    }
    else        //finish the road
    {
        //CCLog("car %lx is out of window!", this);
        unscheduleUpdate();
        getParent()->removeChild(this);
        return;
    }
    
    CCSize carSize= this->getContentSize();
    
    if (isOnAimedLane())
    {
        if (isCarAhead(1.5*carSize.height))
        {
            //CCLog("start truning...");
            if (isLeftEmpty())
            {
                //CCLog("left is empty");
                lane--;
            }
            else if (isRightEmpty())
            {
                //CCLog("right is empty");
                lane++;
            }
            else
            {
                //CCLog("both are full, decelerate");
                if (speed > 3.0f)
                {
                    speed = speed - 1.0f;
                }
            }
        }
        else if (speed < maxspeed && !isCarAhead(2.5*carSize.height))      //on right lane && haven't reach max speed
        {
            speed = speed + 0.3f;
        }
    }
    else        //ont on right lane, changing lane
    {
        this->setPositionX(this->getPositionX()+shift);
    }
}

bool FWCar::isOnAimedLane()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (this->getPositionX()+1 < origin.x+visibleSize.width/2+LANE_WIDTH*((float)lane-1.5))
    {
        shift = 2.0f;
        //CCLog("truning right...");
        return false;
    }
    else if (this->getPositionX()-1 > origin.x+visibleSize.width/2+LANE_WIDTH*((float)lane-1.5))
    {
        //CCLog("this->getPositionX()-1 = %f", this->getPositionX()-1);
        //CCLog("origin.x+visibleSize.width/2+LANE_WIDTH*((float)lane-1.5) = %f", origin.x+visibleSize.width/2+LANE_WIDTH*((float)lane-1.5));
        shift = -2.0f;
        //CCLog("truning left...");
        return false;
    }
    return true;
}

bool FWCar::isCarAhead(float distance)
{
    CCNode *parent = (CCNode*) getParent();
    CCArray *children = parent->getChildren();
    CCObject *pObject;
    
    CCSize selfSize = this->getContentSize();
    CCRect selfRect = CCRectMake(-selfSize.width/2, selfSize.height/2, selfSize.width, distance);
    
    CCARRAY_FOREACH(children, pObject)
    {
        CCNode *pNode = (CCNode*) pObject;
        CCPoint relativePos = convertToNodeSpaceAR(pNode->getPosition());
        
        CCSize otherSize = pNode->getContentSize();
        //CCLog("size of other object is x = %f, y = %f", otherSize.width, otherSize.height);
        CCRect otherRect = CCRectMake(-otherSize.width/2+relativePos.x, -otherSize.height/2+relativePos.y, otherSize.width, otherSize.height);
        
        if ( this != pNode && selfRect.intersectsRect(otherRect) )
        {
            //CCLog("car %lx ahead!", pNode);
            return true;
        }
    }
    return false;
}

bool FWCar::isLeftEmpty()
{
    if (lane == 0)
    {
        //CCLog("leftest lane!");
        return false;
    }
    else
    {
        CCNode *parent = (CCNode*) getParent();
        CCArray *children = parent->getChildren();
        CCObject *pObject;
        
        CCSize selfSize = this->getContentSize();
        CCRect selfRect = CCRectMake(-selfSize.width/2-LANE_WIDTH, -selfSize.height*2, selfSize.width, 4*selfSize.height);
        
        CCARRAY_FOREACH(children, pObject)
        {
            CCNode *pNode = (CCNode*) pObject;
            CCPoint relativePos = convertToNodeSpaceAR(pNode->getPosition());
            
            CCSize otherSize = pNode->getContentSize();
            //CCLog("size of other object is x = %f, y = %f", otherSize.width, otherSize.height);
            CCRect otherRect = CCRectMake(-otherSize.width/2+relativePos.x, -otherSize.height/2+relativePos.y, otherSize.width, otherSize.height);
            
            if ( this != pNode && selfRect.intersectsRect(otherRect) )
            {
                //CCLog("car %lx on the left!", pNode);
                //isNeededToDraw_left = true;
                return false;
            }
        }
    }
    isNeededToDraw_left = false;
    return true;
}

bool FWCar::isRightEmpty()
{
    if (lane == 3)
    {
        //CCLog("rightest lane!");
        return false;
    }
    else
    {
        CCNode *parent = (CCNode*) getParent();
        CCArray *children = parent->getChildren();
        CCObject *pObject;
        
        CCSize selfSize = this->getContentSize();
        CCRect selfRect = CCRectMake(-selfSize.width/2+LANE_WIDTH, -selfSize.height*2, selfSize.width, 4*selfSize.height);
        
        CCARRAY_FOREACH(children, pObject)
        {
            CCNode *pNode = (CCNode*) pObject;
            CCPoint relativePos = convertToNodeSpaceAR(pNode->getPosition());
            
            CCSize otherSize = pNode->getContentSize();
            //CCLog("size of other object is x = %f, y = %f", otherSize.width, otherSize.height);
            CCRect otherRect = CCRectMake(-otherSize.width/2+relativePos.x, -otherSize.height/2+relativePos.y, otherSize.width, otherSize.height);
            
            if ( this != pNode && selfRect.intersectsRect(otherRect) )
            {
                //CCLog("car %lx on the right!", pNode);
                //isNeededToDraw_right = true;
                return false;
            }
        }
    }
    isNeededToDraw_right = false;
    return true;
}
/*
void FWCar::draw()
{
    CCSprite::draw();
    
    ccDrawColor4B(0, 0, 0, 255);
    
    CCSize selfSize = this->getContentSize();
    
    CCPoint origin_left = CCPointMake(-LANE_WIDTH, -selfSize.height*1.5);
    CCPoint destination_left = CCPointMake(selfSize.width-LANE_WIDTH, selfSize.height*1.5);
    CCPoint origin_right = CCPointMake(LANE_WIDTH, -selfSize.height*1.5);
    CCPoint destination_right = CCPointMake(selfSize.width+LANE_WIDTH, selfSize.height*1.5);
    if (isNeededToDraw_left)
    {
        ccDrawRect(origin_left, destination_left);
    }
    if (isNeededToDraw_right)
    {
        ccDrawRect(origin_right, destination_right);
    }
    
    CCPoint origin_self = CCPointMake(0, 0);
    CCPoint destination_self = CCPointMake(selfSize.width, selfSize.height);
    ccDrawRect(origin_self, destination_self);
    
}*/
