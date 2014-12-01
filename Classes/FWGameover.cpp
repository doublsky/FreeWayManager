//
//  FWGameover.cpp
//  FreeWay
//
//  Created by Tony TAN on 11/21/14.
//
//

#include "FWGameover.h"
#include "FreeWay.h"

USING_NS_CC;

bool FWGameover::init()
{
    // get window size at first
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (!CCLayerColor::initWithColor(ccc4(0xff, 0xff, 0xff, 0xff), visibleSize.width/2, visibleSize.width/2))
    {
        return false;
    }
    // an item to replay
    CCMenuItemFont *replay = CCMenuItemFont::create("Replay", this, menu_selector(FWGameover::MenuReplayCallback));
    replay->setPosition(ccp(visibleSize.width/4, visibleSize.width/4));
    replay->setColor(ccc3(0x00, 0x00, 0x00));
    CCMenu *pMenu = CCMenu::create(replay, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu);
    
    return true;
}

void FWGameover::MenuReplayCallback(CCObject *pObject)
{
    //for test fisrt...
    CCLog("replay game...");
    
    //try change the scene
    CCScene *nextScene = CCScene::create();
    FreeWay *pLayer = FreeWay::create();
    nextScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(nextScene);
}