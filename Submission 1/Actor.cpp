#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Dirt::doSomething(){}

void FrackMan::doSomething(){
    int key;
    bool hit = getWorld()->getKey(key);
    if(hit){
        switch (key) {
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(getX() > 0)
                    moveTo(getX()-1, getY());
                    break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if((getX()+3) < 63)
                    moveTo(getX()+1, getY());
                    break;
            case KEY_PRESS_UP:
                setDirection(up);
                if((getY()) <= 59)
                    moveTo(getX(), getY()+1);
                    break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if(getY() > 0)
                    moveTo(getX(), getY() - 1);
                    break;
            default:
                break;
        }
    }
}