//
//  CardSprite.cpp
//  cocos2dx-2048
//
//  Created by jamelee on 2020/8/27.
//

#include "CardSprite.h"

USING_NS_CC;

CardSprite *CardSprite::createCardSprite(int number, int width, int height, float x, float y) {
    CardSprite *card = new CardSprite();
    if (card && card->init()) {
        card->autorelease();
        card->cardInit(number, width, height, x, y);
        return card;
    }
    CC_SAFE_DELETE(card);
    return NULL;
}

bool CardSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

int CardSprite::getNumber() {
    return this->number;
}

void CardSprite::setNumber(int num) {
    number = num;
    // string
    if (num > 0) {
        cardNumber->setString(__String::createWithFormat("%i", num)->getCString());
    } else {
        cardNumber->setString("");
    }
    
    // font
    if (num >= 1024) {
        cardNumber->setSystemFontSize(40);
    } else if (num >= 128) {
        cardNumber->setSystemFontSize(60);
    } else if (num >= 16) {
        cardNumber->setSystemFontSize(90);
    } else if (num >= 0) {
        cardNumber->setSystemFontSize(100);
    }
    
    // color
    if (num == 0) {
        colorBackground->setColor(Color3B(200, 190, 180));
    } else if (number == 2) {
        colorBackground->setColor(Color3B(240,230,220));
    } else if (number == 4) {
        colorBackground->setColor(Color3B(240,220,200));
    } else if (number == 8) {
        colorBackground->setColor(Color3B(240,180,120));
    } else if (number == 16) {
        colorBackground->setColor(Color3B(240,140,90));
    } else if (number == 32) {
        colorBackground->setColor(Color3B(240,120,90));
    } else if (number == 64) {
        colorBackground->setColor(Color3B(240,90,60));
    } else if (number == 128) {
        colorBackground->setColor(Color3B(240,90,60));
    } else if (number == 256) {
        colorBackground->setColor(Color3B(240,200,70));
    } else if (number == 512) {
        colorBackground->setColor(Color3B(240,200,70));
    } else if (number == 1024) {
        colorBackground->setColor(Color3B(0,130,0));
    } else if (number == 2048) {
        colorBackground->setColor(Color3B(0,130,0));
    }
}

void CardSprite::cardInit(int number, int width, int height, float x, float y) {
    
    colorBackground = LayerColor::create(Color4B(200, 190, 180, 255), width -10, height -10);
    colorBackground->setPosition(Point(x, y));

    cardNumber = Label::createWithTTF("", "fonts/arial.ttf", 100);
    if (cardNumber != nullptr) {
        cardNumber->setPosition(colorBackground->getContentSize().width /2, colorBackground->getContentSize().height/2);
        cardNumber->setTag(8);
        colorBackground->addChild(cardNumber);
    }
    
    this->setNumber(number);
    
    this->addChild(colorBackground);
}
