//
//  GameScene.hpp
//  cocos2dx-chess
//
//  Created by jamelee on 2020/8/28.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

class GameScene: public cocos2d::Layer {
    
public:
    GameScene();
    virtual ~GameScene();
    
    static cocos2d::Scene *createScene(bool _clickRed);
    virtual bool init(bool _clickRed);
    
    static GameScene *create(bool _clickRed);
    
    bool onTouchesBegan(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    void onTouchesMoved(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    void onTouchesEnded(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    void onTouchesCancelled(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    
    void menuCloseCallback(cocos2d::Ref *pSender);
    void backupMenuCallback(cocos2d::Ref *pSender);
    void newgameMenuCallback(cocos2d::Ref *pSender);
public:
    bool clickRed;
    cocos2d::Array *steps;
};


#endif /* GameScene_hpp */
