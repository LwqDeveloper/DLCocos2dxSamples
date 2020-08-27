//
//  CardSprite.hpp
//  cocos2dx-2048
//
//  Created by jamelee on 2020/8/27.
//

#ifndef CardSprite_hpp
#define CardSprite_hpp

#include "cocos2d.h"

class CardSprite: public cocos2d::Sprite {
    
public:
    static CardSprite *createCardSprite(int number, int width, int height, float x, float y);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    
    int getNumber();
    void setNumber(int num);
    
private:
    int number;
    void cardInit(int number, int width, int height, float x, float y);
    cocos2d::Label *cardNumber;
    cocos2d::LayerColor *colorBackground;
};

#endif /* CardSprite_hpp */
