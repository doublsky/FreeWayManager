//
//  FWMenu.cpp
//  FreeWay
//
//  Created by Tony TAN on 11/13/14.
//
//

#include "FWMenu.h"
#include "FreeWay.h"

USING_NS_CC;

bool FWMenu::init()
{
    //super init
    if (!CCLayerColor::initWithColor(ccc4(0xcf, 0xcf, 0xcf, 0xff)))
    {
        return false;
    }
    // get screen size
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //create a menu item "new game"
    CCMenuItemFont *newGame = CCMenuItemFont::create("New Game", this, menu_selector(FWMenu::MenuNewGameCallback));
    newGame->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    newGame->setColor(ccc3(0x00, 0x00, 0x00));
    CCMenu *pMenu = CCMenu::create(newGame, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu);
    
    return true;
}

void FWMenu::MenuNewGameCallback(CCObject *pObject)
{
    // create a new scene with a main game layer
    CCScene *nextScene = CCScene::create();
    FreeWay *layer = FreeWay::create();
    nextScene->addChild(layer);
    
    //replace scene
    CCDirector::sharedDirector()->replaceScene(nextScene);
}