#include "Actor.h"
#include "StudentWorld.h"
//#include <vector>

using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Dirt::move(){}

void FrackMan::move(){
    int key;
    bool hit = getWorld()->getKey(key);
    vector<Actor*> bob = getWorld()->getItems();
    bool move = true;
    if(hit){
        switch (key) {
            case KEY_PRESS_LEFT:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (!bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX() - 1, getY(), bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                setDirection(left);
                if(move && getX() > 0)
                    moveTo(getX()-1, getY());
                else if (move && getX() == 0)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_RIGHT:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (!bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX() + 1, getY(), bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                setDirection(right);
                if(move && (getX()+3) < 63)
                    moveTo(getX()+1, getY());
                else if (move && getX() + 3 == 63)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_UP:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (!bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX(), getY() + 1, bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                setDirection(up);
                if(move && (getY()) < 60)
                    moveTo(getX(), getY()+1);
                else if (move && getY() == 60)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_DOWN:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (!bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX(), getY() - 1, bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                setDirection(down);
                if(move && getY() > 0)
                    moveTo(getX(), getY() - 1);
                else if (move && getY() == 0)
                    moveTo(getX(), getY());
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

void Actor::setDead(){
    dead = true;
}

bool Actor::isAlive() const{
    return !dead;
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

bool FrackMan::hasMoved(){
    if (m_moved) {
        m_moved = false;
        return true;
    }
    return false;
}

//-----------------------------redo
unsigned int Agent::getHitPoints() const{
    return m_hitPoints;
}

void Boulder::move(){
    if (!isAlive()) {
        return;
    }
    if(getState() == 's'){
        if (getWorld()->isFreeUnder(getX(), getY()))
            setState('w');
    }
    if(getState() == 'w' && getW()<30){
        incrementW();
    } else if (getW() == 30){
        setState('f');
    }
    if (getState() == 'f') {
        getWorld()->playSound(SOUND_FALLING_ROCK);
        if(getWorld()->canMoveDown(getX(), getY()))
            moveTo(getX(), getY() - 1);
        else{
            setDead();
        }
    }
}

int Boulder::getW(){
    return wait;
}
void Boulder::incrementW(){
    wait++;
}
bool Boulder::canActorsPassThroughMe() const{
    return false;
}
char Boulder::getState(){
    return state;
}
void Boulder::setState(char c){
    state = c;
}