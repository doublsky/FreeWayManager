//
//  car.h
//  FreeWay
//
//  Created by Tony TAN on 9/19/14.
//
//

#ifndef __FreeWay__car__
#define __FreeWay__car__

#include "cocos2d.h"

class FWCar : public cocos2d::CCSprite {
private:
    float maxspeed;
    float speed;
    float shift;
    
    //for debugging
    bool isNeededToDraw_left;
    bool isNeededToDraw_right;

    
public:
    //member variable
    int lane;
    FWCar *forwardCar;
    FWCar *backwardCar;
    
    //original functions
    static FWCar* create(const char *pszFileName, float speed);
    virtual void onEnter();
    
    //create movement
    void update(float dt);
    
    //for debuggng
    //virtual void draw();
    
    //collision detection
    bool isCarAhead(float distance);
    bool isLeftEmpty();
    bool isRightEmpty();
    bool isOnAimedLane();
};

#endif /* defined(__FreeWay__car__) */
