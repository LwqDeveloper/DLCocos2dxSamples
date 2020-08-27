//
//  GameScene.hpp
//  cocos2dx-2048
//
//  Created by jamelee on 2020/8/27.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "CardSprite.h"

class GameScene: public cocos2d::Layer {
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

private:
    int totalScore;
    cocos2d::Label *currentScoreLabel;
    int maxScore;
    cocos2d::Label *maxScoreLabel;
    void createGameBackground(cocos2d::Size size);
    CardSprite *cardArray[4][4];
    
    bool checkIsGameOver();
    void createRandomCardNumber();
    
    int beginX, beginY, endX, endY;
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
};

#endif /* GameScene_hpp */
