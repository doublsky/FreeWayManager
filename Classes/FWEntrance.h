//
//  FWEntrance.h
//  FreeWay
//
//  Created by Tony TAN on 11/25/14.
//
//

#ifndef __FreeWay__FWEntrance__
#define __FreeWay__FWEntrance__

#include "cocos2d.h"

enum carKind
{
    SLOWCAR = 0,
    NORMALCAR,
    FASTCAR
};

class FWEntrance : public cocos2d::CCNode
{
    cocos2d::CCSprite *cover;
    int numOfSlowInWaitingList;
    int numOfNormalInWaitingList;
    int numOfFastInWaitingList;
    
    //add a car
    void addCar(float speed);
    
    //add a car in waiting list
    void addCarInWL(carKind kind);
    
public:
    // super function
    virtual void onEnter();
    
    //add car in waiting list
    void addSlowCarInWL(float dt);
    void addNormalCarInWL(float dt);
    void addFastCarInWL(float dt);
    
    //menu callback
    void menuAddSlowCarCallback(CCObject* pSender);
    void menuAddNormalCarCallback(CCObject* pSender);
    void menuAddFastCarCallback(CCObject* pSender);
};

#endif /* defined(__FreeWay__FWEntrance__) */
