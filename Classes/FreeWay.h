//
//  FreeWay.h
//  FreeWay
//
//  Created by Tony TAN on 9/19/14.
//
//

#ifndef __FreeWay__FreeWay__
#define __FreeWay__FreeWay__

#include "cocos2d.h"

enum carKind
{
    SLOWCAR = 0,
    NORMALCAR,
    FASTCAR
};

class FreeWay : public cocos2d::CCLayer
{
private:
    //member variable
    //int numOfCar;
    int numOfSlowInWaitingList;
    int numOfNormalInWaitingList;
    int numOfFastInWaitingList;

    //add a car
    void addCar(float speed);
    
    //add a car in waiting list
    void addCarInWL(carKind kind);
    
public:
    cocos2d::CCArray *carList;        //container of all the cars
    
    // original function
    virtual bool init();
    CREATE_FUNC(FreeWay);
    
    //add car in waiting list
    void addSlowCarInWL(float dt);
    void addNormalCarInWL(float dt);
    void addFastCarInWL(float dt);
    
    //keypad click callback
    void keyBackClicked();
    
    //menu callback
    void menuAddSlowCarCallback(CCObject* pSender);
    void menuAddNormalCarCallback(CCObject* pSender);
    void menuAddFastCarCallback(CCObject* pSender);

};


#endif /* defined(__FreeWay__FreeWay__) */
