//
//  GameScene.cpp
//  cocos2dx-2048
//
//  Created by jamelee on 2020/8/27.
//

#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
    this->addChild(layerColorBG);
    
//    auto maxLabel = Label::createWithTTF("Max", "fonts/arial.ttf", 50);
//    if (maxLabel != nullptr) {
//        maxLabel->setPosition(visibleSize.width / 4, visibleSize.height -visibleSize.width -100);
//        this->addChild(maxLabel, 0);
//    }
    auto maxImv = Sprite::create("high_ccore.png");
    if (maxImv != nullptr) {
        maxImv->setPosition(visibleSize.width / 4, visibleSize.height -visibleSize.width -150);
        this->addChild(maxImv);
    }
    
    maxScore = UserDefault::getInstance()->getIntegerForKey("kMaxScore");
    maxScoreLabel = Label::createWithTTF(__String::createWithFormat("%i", maxScore)->getCString(), "fonts/arial.ttf", 50);
    if (maxScoreLabel != nullptr) {
        maxScoreLabel->setPosition(visibleSize.width / 4, visibleSize.height -visibleSize.width -180);
        this->addChild(maxScoreLabel);
    }
    
//    auto scoreLabel = Label::createWithTTF("Score", "fonts/arial.ttf", 50);
//    if (scoreLabel != nullptr) {
//        scoreLabel->setPosition(visibleSize.width *3/ 4, visibleSize.height -visibleSize.width -100);
//        this->addChild(scoreLabel, 0);
//    }
    auto scoreImv = Sprite::create("score.png");
    if (scoreImv != nullptr) {
        scoreImv->setPosition(visibleSize.width *3/ 4, visibleSize.height -visibleSize.width -150);
        this->addChild(scoreImv);
    }
    
    totalScore = 0;
    currentScoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 40);
    if (currentScoreLabel != nullptr) {
        currentScoreLabel->setPosition(visibleSize.width *3/ 4, visibleSize.height -visibleSize.width -180);
        this->addChild(currentScoreLabel);
    }
        
    this->createGameBackground(visibleSize);
    
    this->createRandomCardNumber();
    this->createRandomCardNumber();

    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    Point bt = touch->getLocation();
    beginX = bt.x;
    beginY = bt.y;
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    Point et = touch->getLocation();
    int changeX = beginX -et.x;
    int changeY = beginY -et.y;
    if (abs(changeX) < 10 && abs(changeY) < 10) {
        return;
    }
        
    if (abs(changeX) > abs(changeY)) {
        if (changeX + 5 > 0) {
            if (checkIsGameOver(0)) {
                Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
                return;
            }
            goLeft();
        } else {
            if (checkIsGameOver(1)) {
                Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
                return;
            }
            goRight();
        }
    } else {
        if (changeY + 5 > 0) {
            if (checkIsGameOver(2)) {
                Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
                return;
            }
            goDown();
        } else {
            if (checkIsGameOver(3)) {
                Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
                return;
            }
            goUp();
        }
    }
    createRandomCardNumber();
    currentScoreLabel->setString(__String::createWithFormat("%i", totalScore)->getCString());
    if (maxScore < totalScore) {
        maxScoreLabel->setString(__String::createWithFormat("%i", totalScore)->getCString());
        UserDefault::getInstance()->setIntegerForKey("kMaxScore", totalScore);
    }
}

void GameScene::goLeft() {
    for (int row = 0; row < 4; row ++) {
        for (int column = 0; column < 4; column ++) {
            for (int x = column + 1; x < 4; x ++) {
                if (cardArray[x][row]->getNumber() > 0) {
                    if (cardArray[column][row]->getNumber() == 0) {
                        cardArray[column][row]->setNumber(cardArray[x][row]->getNumber());
                        cardArray[x][row]->setNumber(0);
                        column --;
                    } else if (cardArray[x][row]->getNumber() == cardArray[column][row]->getNumber()) {
                        cardArray[column][row]->setNumber(cardArray[x][row]->getNumber() *2);
                        cardArray[x][row]->setNumber(0);
                        totalScore += cardArray[column][row]->getNumber();
                    }
                    break;
                }
            }
        }
    }
}

void GameScene::goRight() {
    for (int row = 0; row < 4; row ++) {
        for (int column = 3; column >= 0; column --) {
            for (int x = column - 1; x >= 0; x --) {
                if (cardArray[x][row]->getNumber() > 0) {
                    if (cardArray[column][row]->getNumber() == 0) {
                        cardArray[column][row]->setNumber(cardArray[x][row]->getNumber());
                        cardArray[x][row]->setNumber(0);
                        column ++;
                    } else if (cardArray[x][row]->getNumber() == cardArray[column][row]->getNumber()) {
                        cardArray[column][row]->setNumber(cardArray[x][row]->getNumber() *2);
                        cardArray[x][row]->setNumber(0);
                        totalScore += cardArray[column][row]->getNumber();
                    }
                    break;
                }
            }
        }
    }
}

void GameScene::goUp() {
    for (int column = 0; column < 4; column ++) {
        for (int row = 3; row >= 0; row --) {
            for (int y = row - 1; y >= 0; y --) {
                if (cardArray[column][y]->getNumber() > 0) {
                    if (cardArray[column][row]->getNumber() == 0) {
                        cardArray[column][row]->setNumber(cardArray[column][y]->getNumber());
                        cardArray[column][y]->setNumber(0);
                        row ++;
                    } else if (cardArray[column][row]->getNumber() == cardArray[column][y]->getNumber()) {
                        cardArray[column][row]->setNumber(cardArray[column][y]->getNumber() *2);
                        cardArray[column][y]->setNumber(0);
                        totalScore += cardArray[column][row]->getNumber();
                    }
                    break;
                }
            }
        }
    }
}

void GameScene::goDown() {
    for (int column = 0; column < 4; column ++) {
        for (int row = 0; row < 4; row ++) {
            for (int y = row + 1; y < 4; y ++) {
                if (cardArray[column][y]->getNumber() > 0) {
                    if (cardArray[column][row]->getNumber() == 0) {
                        cardArray[column][row]->setNumber(cardArray[column][y]->getNumber());
                        cardArray[column][y]->setNumber(0);
                        row --;
                    } else if (cardArray[column][row]->getNumber() == cardArray[column][y]->getNumber()) {
                        cardArray[column][row]->setNumber(cardArray[column][y]->getNumber() *2);
                        cardArray[column][y]->setNumber(0);
                        totalScore += cardArray[column][row]->getNumber();
                    }
                    break;
                }
            }
        }
    }
}

// 0-left 1-right 2-down 3-top
bool GameScene::checkIsGameOver(int direction) {
    // 检查还是否有位置
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            if (cardArray[i][j]->getNumber() == 0) {
                return false;
            }
        }
    }
    // 检查相同数字
    if (direction == 0) {
        for (int i = 0; i < 4; i ++) {
            for (int j = 3; j > 0; j --) {
                if (cardArray[j][i]->getNumber() == cardArray[j-1][i]->getNumber()) {
                    return false;
                }
            }
        }
    } else if (direction == 1) {
        for (int i = 0; i < 4; i ++) {
            for (int j = 0; j < 3; j ++) {
                if (cardArray[j][i]->getNumber() == cardArray[j+1][i]->getNumber()) {
                    return false;
                }
            }
        }
    } else if (direction == 2) {
        for (int i = 0; i < 4; i ++) {
            for (int j = 3; j > 0; j --) {
                if (cardArray[j][i]->getNumber() == cardArray[j-1][i]->getNumber()) {
                    return false;
                }
            }
        }
    } else if (direction == 3) {
        for (int i = 0; i < 4; i ++) {
            for (int j = 0; j < 3; j ++) {
                if (cardArray[i][j]->getNumber() == cardArray[i][j+1]->getNumber()) {
                    return false;
                }
            }
        }
    }

    return true;
}

void GameScene::createGameBackground(Size size) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int cardWidth = (size.width -0) /4.0;
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            CardSprite *cs = CardSprite::createCardSprite(0, cardWidth, cardWidth, cardWidth *i + 5, cardWidth *j +visibleSize.height -visibleSize.width -20);
            cardArray[i][j] = cs;
            this->addChild(cs);
        }
    }
}

void GameScene::createRandomCardNumber() {
    int i = CCRANDOM_0_1() *4;
    int j = CCRANDOM_0_1() *4;
    if (cardArray[i][j]->getNumber() > 0) {
        this->createRandomCardNumber();
    } else {
        cardArray[i][j]->setNumber(CCRANDOM_0_1() *10 < 3? 4 : 2);
    }
}
