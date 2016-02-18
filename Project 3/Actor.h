#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"


class Actor: public GraphObject{
public:
    Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0):GraphObject(imageID, startX, startY, dir, size, depth){
        
    }
    virtual void act(bool hit, int key){
        
    }
};

class Dirt : public Actor{
public:
    Dirt(int imageID, int startX, int startY, Direction dir = right, double size = 0.25, unsigned int depth = 0):Actor(imageID, startX, startY, dir, size, depth){
        
    }
    
    virtual void act(int x, int y){
        if ((getX() - x) >= 0 && (getX() - x) < 4 && (getY() - y) >= 0 && (getY() - y) < 4){
            setVisible(false);
        }
    }
private:
};

class FrackMan : public Actor{
public:
    FrackMan(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0):Actor(imageID, startX, startY, dir, size, depth){
        
    }
    
    int getHealth(){
        return 80;
    }
    
    virtual void act(bool hit, int key){
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
                    if((getY()+3) < 59)
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
private:

};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
