//
//  GuideScene.hpp
//  cocos2dx-chess
//
//  Created by jamelee on 2020/8/28.
//

#ifndef GuideScene_hpp
#define GuideScene_hpp

#include "cocos2d.h"

class GuideScene: public cocos2d::Layer {
    
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GuideScene);
    
    virtual bool onTouchBegan(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    virtual void onTouchMoved(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    virtual void onTouchEnded(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    virtual void onTouchCancelled(cocos2d::Touch *mTouch, cocos2d::Event *mEvent);
    virtual void update(float delta);
    
public:
    cocos2d::Sprite* jiang;
    cocos2d::Sprite* shuai;
    bool clickRed;
};

#endif /* GuideScene_hpp */
