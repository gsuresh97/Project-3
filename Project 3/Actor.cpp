#include "Actor.h"
#include "StudentWorld.h"
//#include "GameConstants.h"
//#include <vector>

using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

typedef GraphObject::Direction Dir;

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
                    if (bob[i] && !bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX() - 1, getY(), bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                if (getDirection() != left) {
                    move = false;
                    setDirection(left);
                }
                if(move && getX() > 0)
                    moveTo(getX()-1, getY());
                else if (move && getX() == 0)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_RIGHT:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (bob[i] && !bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX() + 1, getY(), bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                if (getDirection() != right) {
                    move = false;
                    setDirection(right);
                }
                if(move && (getX()+3) < 63)
                    moveTo(getX()+1, getY());
                else if (move && getX() + 3 == 63)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_UP:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (bob[i] && !bob[i]->canActorsPassThroughMe() && getWorld()->isNear(getX(), getY() + 1, bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                if (getDirection() != up) {
                    move = false;
                    setDirection(up);
                }
                if(move && (getY()) < 60)
                    moveTo(getX(), getY()+1);
                else if (move && getY() == 60)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_DOWN:
                m_moved = true;
                for(int i = 0; i < bob.size(); i++){
                    if (bob[i] && !bob[i]->canActorsPassThroughMe()
                        && getWorld()->isNear(getX(), getY() - 1, bob[i]->getX(), bob[i]->getY(), 3)) {
                        move = false;
                    }
                }
                if (getDirection() != down) {
                    move = false;
                    setDirection(down);
                }
                if(move && getY() > 0)
                    moveTo(getX(), getY() - 1);
                else if (move && getY() == 0)
                    moveTo(getX(), getY());
                break;
            case KEY_PRESS_SPACE:
                if (m_water > 0) {
                    m_water--;
                    getWorld()->addSquirt();
                }
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
            case KEY_PRESS_TAB:
                if (m_gold>0) {
                    getWorld()->addGold();
                }
                break;
            case 'z':
            case 'Z':
                if (m_sonar_charges > 0) {
                    m_sonar_charges--;
                    for (int i = 0; i < bob.size(); i++) {
                        Actor* x = bob[i];
                        if (getWorld()->isNear(getX(), getY(), x->getX(), x->getY(), 12)) {
                            x->setVisible(true);
                        }
                    }
                }
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
    setVisible(false);
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

void Agent::setHitPoints(unsigned int hp){
    m_hitPoints = hp;
}

void Agent::decrementHitPoints(unsigned int hp){
    m_hitPoints -= hp;
}

unsigned int Agent::getScore() const{
    return getWorld()->getScore();
}

//-----------------------------redo
bool FrackMan::annoy(unsigned int amount){
    decrementHitPoints(amount);
    return true;
}

//-----------------------------redo
void FrackMan::addGold(){
    m_gold++;
}

void FrackMan::decGold(){
    m_gold--;
}

void FrackMan::addSonar(){
    m_sonar_charges++;
}

void FrackMan::addWater(){
    m_water+=5;
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

unsigned int FrackMan::getGold() const{
    return m_gold;
}

unsigned int FrackMan::getWater() const{
    return m_water;
}

unsigned int FrackMan::getSonar() const{
    return m_sonar_charges;
}

void FrackMan::getSquirtDets(int &x, int &y, Dir& dir){
    dir = getDirection();
    switch (dir) {
        case GraphObject::down:
            if(getWorld()->inSquirtField(getX(), getY() - 4)){
                x = getX();
                y = getY() - 4;
                //cout << "X: " << x << "\tY: " << y << endl;
            }
            break;
        case GraphObject::up:
            if(getWorld()->inSquirtField(getX(), getY() + 7)){
                x = getX();
                y = getY() + 4;
            }
            break;
        case GraphObject::left:
            if(getWorld()->inSquirtField(getX() - 4, getY())){
                x = getX() - 4;
                y = getY();
            }
            break;
        case GraphObject::right:
            if(getWorld()->inSquirtField(getX() + 7, getY())){
                x = getX() + 4;
                y = getY();
            }
            break;
        default:
            break;
    }
}

bool Protester::shouldLeaveOilField(){
    return shouldLeave;
}

void Protester::leave(){
    shouldLeave = true;
}

bool Protester::annoy(unsigned int amount){
    decrementHitPoints(amount);
    return true;
}

void Protester::addGold(){
    
}

bool Protester::huntsFrackMan() const{
    return true;
}

void RegularProtester::move(){
    
}

void RegularProtester::addGold(){
    
}

void HardcoreProtester::move(){
    
}

void HardcoreProtester::addGold(){
    
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
            setVisible(false);
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



void Squirt::move(){
    Dir dir = getDirection();
    if (getSteps() == 4 || !getWorld()->squirtCanMove(getX(), getY(), getDirection())) {
        setDead();
        setVisible(false);
    } else{
        switch (dir) {
            case GraphObject::down:
                if(getWorld()->inSquirtField(getX(), getY() - 1)){
                    moveTo(getX(), getY() - 1);
                    incrementSteps();
                } else{
                    setDead();
                    setVisible(false);
                }
                break;
            case GraphObject::up:
                if(getWorld()->inSquirtField(getX(), getY() + 4)){
                    moveTo(getX(), getY() + 1);
                    incrementSteps();
                } else{
                    setDead();
                    setVisible(false);
                }
                break;
            case GraphObject::left:
                if(getWorld()->inSquirtField(getX() - 1, getY())){
                    moveTo(getX() - 1, getY());
                    incrementSteps();
                } else{
                    setDead();
                    setVisible(false);
                }
                break;
            case GraphObject::right:
                if(getWorld()->inSquirtField(getX() + 4, getY())){
                    moveTo(getX() + 1, getY());
                    incrementSteps();
                } else{
                    setDead();
                    setVisible(false);
                }
                break;
            default:
                break;
        }
    }
}
int Squirt::getSteps(){
    return steps;
}
void Squirt::incrementSteps(){
    steps++;
}

bool Squirt::canActorsPassThroughMe() const{
    return true;
}

void ActivatingObject::playSound(int x){
    getWorld()->playSound(x);
}
void ActivatingObject::setTicksToLive(int ticks){
    ttl = ticks;
}
void ActivatingObject::move(){
    
}

bool OilBarrel::needsToBePickedUpToFinishLevel() const{
    return true;
}

bool OilBarrel::canActorsPassThroughMe() const{
    return true;
}

void OilBarrel::move(){
    if (!isAlive()){
        return;
    }
    if (getWorld()->isFrackManNear(getX(), getY(), 3)) {
        setVisible(true);
        setDead();
        getWorld()->oilFound();
        playSound(SOUND_FOUND_OIL);
        getWorld()->increaseScore(1000);
    } else if (getWorld()->isFrackManNear(getX(), getY(), 4)) {
        setVisible(true);
        return;
    }
}

void GoldNugget::move(){
    if (!isAlive()) {
        return;
    }
    if (wait == 0) {
        setDead();
        return;
    }
    if (forFrackMan() && getWorld()->isFrackManNear(getX(), getY(), 3)) {
        setVisible(true);
        setDead();
        getWorld()->goldFound();
        playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(10);
    } else if (forFrackMan() && getWorld()->isFrackManNear(getX(), getY(), 4)) {
        setVisible(true);
        return;
    } else if (!forFrackMan()){
        wait--;
    }
    
}

bool GoldNugget::canActorsPassThroughMe() const{
    return true;
}

bool GoldNugget::forFrackMan(){
    return m_forF;
}
void GoldNugget::setForFrackMan(){
    m_forF = true;
}
void GoldNugget::setForProtestor(){
    m_forF = false;
    wait = 100;
    
}

void SonarKit::setWait(){
    wait = 100 > 300-10*getWorld()->getLevel()? 100 : 300-10*getWorld()->getLevel();
}

void SonarKit::move(){
    if (!isAlive()) {
        return;
    }
    if (wait == 0) {
        setDead();
        return;
    }
    if (getWorld()->isFrackManNear(getX(), getY(), 3)) {
        setDead();
        getWorld()->chargeFound();
        playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(75);
    }
    wait--;
    
}

void WaterPool::setWait(){
    wait = 100 > 300-10*getWorld()->getLevel()? 100 : 300-10*getWorld()->getLevel();
}

void WaterPool::move(){
    if (!isAlive()) {
        return;
    }
    if (wait == 0) {
        setDead();
        return;
    }
    if (getWorld()->isFrackManNear(getX(), getY(), 3)) {
        setDead();
        getWorld()->waterFound();
        playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(100);
    }
    wait--;
}

void Protester::move(){
    
}

