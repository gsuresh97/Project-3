#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Dirt::move(){}

void FrackMan::move(){
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

//----------------------redo
void Actor::move(){
    
}

//-----------------------------redo
bool Actor::annoy(unsigned int amt){
    return true;
}

//-----------------------------redo
bool Actor::canActorsPassThroughMe() const{
    return true;
}

//-----------------------------redo
bool Actor::canDigThroughDirt() const{
    return true;
}

//-----------------------------redo
bool Actor::canPickThingsUp() const{
    return true;
}

//-----------------------------redo
bool Actor::huntsFrackMan() const{
    return false;
}

//-----------------------------redo
bool Actor::needsToBePickedUpToFinishLevel() const{
    return false;
}

//-----------------------------redo
void Agent::addGold(){
    
}

//-----------------------------redo
bool Agent::annoy(unsigned int amount){
    return true;
}

//-----------------------------redo
bool Agent::canPickThingsUp() const{
    return true;
}


//-----------------------------redo
bool FrackMan::annoy(unsigned int amount){
    return false;
}

//-----------------------------redo
void FrackMan::addGold(){
    
}

//-----------------------------redo
bool FrackMan::canDigThroughDirt() const{
    return true;
}

//-----------------------------redo
unsigned int Agent::getHitPoints() const{
    return m_hitPoints;
}
