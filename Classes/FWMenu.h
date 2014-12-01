//
//  FWMenu.h
//  FreeWay
//
//  Created by Tony TAN on 11/13/14.
//
//

#ifndef __FreeWay__FWMenu__
#define __FreeWay__FWMenu__

#include "cocos2d.h"

class FWMenu : public cocos2d::CCLayerColor
{
    
public:
    //super functions
    virtual bool init();
    CREATE_FUNC(FWMenu);
    
    
    //menu items callbacks
    void MenuNewGameCallback(cocos2d::CCObject *pObject);
};

#endif /* defined(__FreeWay__FWMenu__) */
