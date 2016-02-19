#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;

class Actor: public GraphObject{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0):GraphObject(imageID, startX, startY, dir, size, depth), m_world(world){
        setVisible(true);
    }
    virtual void doSomething(bool hit, int key){
        
    }
    StudentWorld* getWorld(){
        return m_world;
    }
private:
    StudentWorld* m_world;
};


class Dirt : public Actor{
public:
    Dirt(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 0.25, unsigned int depth = 3):Actor(imageID, startX, startY, world, dir, size, depth){
        
    }
    
    virtual void doSomething();
private:
};

class FrackMan : public Actor{
public:
    FrackMan(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0):Actor(imageID, startX, startY, world, dir, size, depth){
        
    }
    
    int getHealth(){
        return 80;
    }
    
    virtual void doSomething();
private:
    
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
