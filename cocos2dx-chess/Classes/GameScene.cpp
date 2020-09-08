//
//  GameScene.cpp
//  cocos2dx-chess
//
//  Created by jamelee on 2020/8/28.
//

#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene() {
    
}

GameScene::~GameScene() {
    if (steps != NULL) {
        steps->release();
    }
}

Scene *GameScene::createScene(bool _clickRed) {
    auto scene = Scene::create();
    auto layer = GameScene::create(_clickRed);
    scene->addChild(layer);
    return scene;
}

GameScene *GameScene::create(bool _clickRed) {
    GameScene *game = new GameScene();
    if (game && game->init(_clickRed)) {
        game->autorelease();
        return game;
    } else {
        delete game;
        game = NULL;
        return NULL;
    }
}

bool GameScene::init(bool _clickRed) {
    if (!Layer::init()) {
        return false;
    }
    clickRed = _clickRed;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x +visibleSize.width -closeItem->getContentSize().width /2, origin.y +closeItem->getContentSize().height /2));
    
    auto newGameItem = MenuItemImage::create("res/new.png", "res/new_selected.png", CC_CALLBACK_1(GameScene::newgameMenuCallback, this));
    newGameItem->setPosition(Vec2(visibleSize.width -200, 200));

    auto backItem = MenuItemImage::create("res/regret.png", "res/regret_selected.png", CC_CALLBACK_1(GameScene::backupMenuCallback, this));
    backItem->setPosition(Vec2(visibleSize.width -200, 100));

    auto menu = Menu::create(closeItem, backItem, newGameItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto floor = Sprite::create("res/floor.png");
    floor->setPosition(visibleSize.width /2 +origin.x, visibleSize.height /2 +origin.y);
    floor->setScaleX(visibleSize.width /floor->getContentSize().width);
    floor->setScaleY(visibleSize.height /floor->getContentSize().height);
    this->addChild(floor);
    
    auto qipan = Sprite::create("res/background.png");
//    qipan->setAnchorPoint(Vec2(0, 0));
    qipan->setPosition(Vec2(visibleSize.width /2, visibleSize.height /2));
//    qipan->setScale((visibleSize.height -offset.y *2) /qipan->getContentSize().height);
    qipan->setScale((visibleSize.width -20 *2) /qipan->getContentSize().width);
    this->addChild(qipan);
    
    EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), qipan);

    
    return true;
}

bool GameScene::onTouchesBegan(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    
    return true;
}

void GameScene::onTouchesMoved(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    
}

void GameScene::onTouchesEnded(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    
}

void GameScene::onTouchesCancelled(cocos2d::Touch *mTouch, cocos2d::Event *mEvent) {
    
}

void GameScene::menuCloseCallback(cocos2d::Ref *pSender) {
    
}

void GameScene::backupMenuCallback(cocos2d::Ref *pSender) {
    
}

void GameScene::newgameMenuCallback(cocos2d::Ref *pSender) {
    
}
