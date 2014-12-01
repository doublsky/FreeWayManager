//
//  FWGameover.h
//  FreeWay
//
//  Created by Tony TAN on 11/21/14.
//
//

#ifndef __FreeWay__FWGameover__
#define __FreeWay__FWGameover__

#include "cocos2d.h"

class FWGameover : public cocos2d::CCLayerColor
{
    
public:
    //parent's functions
    virtual bool init();
    CREATE_FUNC(FWGameover);
    
    //menu items callbacks
    void MenuReplayCallback(cocos2d::CCObject *pObject);
};

#endif /* defined(__FreeWay__FWGameover__) */
