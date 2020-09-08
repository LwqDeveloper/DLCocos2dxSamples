//
//  GuideScene.cpp
//  cocos2dx-chess
//
//  Created by jamelee on 2020/8/28.
//

#include "GuideScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene *GuideScene::createScene() {
    Scene *scene = Scene::create();
    Layer *layer = GuideScene::create();
    scene->addChild(layer);
    return scene;
}

bool GuideScene::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getWinSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    jiang = Sprite::create("res/bkg1.png");
    jiang->setPosition(visibleSize.width /2 -jiang->getContentSize().width *2, visibleSize.height /2);
    this->addChild(jiang);
    
    shuai = Sprite::create("res/bkg2.png");
    shuai->setPosition(visibleSize.width /2 +shuai->getContentSize().width *2, visibleSize.height /2);
    this->addChild(shuai);
    
    EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GuideScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GuideScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GuideScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GuideScene::onTouchCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, jiang);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), shuai);
    
    return true;
}

bool GuideScene::onTouchBegan(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    return true;
}

void GuideScene::onTouchMoved(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    
}

void GuideScene::onTouchCancelled(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    
}

void GuideScene::onTouchEnded(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    Vec2 location = mTouch->getLocation();
    bool isClicked = false;
    if (jiang->getBoundingBox().containsPoint(location) ||
        shuai->getBoundingBox().containsPoint(location)) {
        isClicked = true;
        clickRed = shuai->getBoundingBox().containsPoint(location) ? true: false;
    }
    if (isClicked) {
        int duration = 1;
        Size winSize = Director::getInstance()->getWinSize();
        MoveTo *to = MoveTo::create(duration, Vec2(winSize.width /2, winSize.height /2));
        RotateBy *rb = RotateBy::create(duration, 360);
        
        Spawn *jiangAction = Spawn::create(to, rb, NULL);
        Spawn *shuaiAction = Spawn::create(to->clone(), rb->clone()->reverse(), NULL);
        jiang->runAction(jiangAction);
        shuai->runAction(shuaiAction);
        scheduleUpdate();
    }
}

void GuideScene::update(float delta) {
    float jiang_x = jiang->getPositionX();
    float shuai_x = shuai->getPositionX();
    if (abs(jiang_x -shuai_x) < jiang->getContentSize().width) {
        Director::getInstance()->replaceScene(GameScene::createScene(clickRed));
    }
}
