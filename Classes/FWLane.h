//
//  FWLane.h
//  FreeWay
//
//  Created by Tony TAN on 11/24/14.
//
//

#ifndef __FreeWay__FWLane__
#define __FreeWay__FWLane__

#include "cocos2d.h"
#include "car.h"

class FWLane : public cocos2d::CCNode
{
    
public:
    int laneOrder;
    FWLane *leftLane;
    FWLane *rightLane;
    
    //linked list operation
    void insert(FWCar *car, FWCar *before);
    void remove(FWCar *car);
};

#endif /* defined(__FreeWay__FWLane__) */
