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
    if (getHitPoints() <= 0) {
        setDead();
    }
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
                if(move && getX() > 0){
                    moveTo(getX()-1, getY());
                    getWorld()->updateFrackManMaze();
                }
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
                if(move && (getX()+3) < 63){
                    moveTo(getX()+1, getY());
                    getWorld()->updateFrackManMaze();
                }
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
                if(move && (getY()) < 60){
                    moveTo(getX(), getY()+1);
                    getWorld()->updateFrackManMaze();
                    
                }
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
                if(move && getY() > 0){
                    moveTo(getX(), getY() - 1);
                    getWorld()->updateFrackManMaze();
                }
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
                    decGold();
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


//-----------------------------redo


//-----------------------------redo


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

int Protester::getTicksLeft(){
    return tl;
}

int Protester::getTicksPerMove(){
    return tpm;
}

void Protester::setTicksPerMove(){
    tpm = 3-(int)(getWorld()->getLevel())/4 < 0? 0 : 3-getWorld()->getLevel()/4;
}

void Protester::setTicksLeft(int ticks){
    tl = ticks;
}

void Protester::decTicksLeft(){
    tl--;
}

bool Protester::annoy(unsigned int amount){
    if (amount == 3) {
        decrementHitPoints(2);
        getWorld()->increaseScore(150);
    }
    else{
        decrementHitPoints(amount);
    }
    if (getHitPoints() > 20) {
        leave();
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        getWorld()->increaseScore(100);
        setTicksLeft(0);
    } else {
        int n = 50 > 100-getWorld()->getLevel()*10 ? 50 : 100-getWorld()-> getLevel()*10;
        setTicksLeft(getTicksLeft() + n);
    }
    return true;
}

bool Protester::hasShouted(){
    return hs > 0;
}

void Protester::resetHasShouted(){
    hs = 15;
}

void Protester::decHasShouted(){
    hs--;
}


bool Protester::hasMadePerpendicularTurn(){
    return hasmadepturn > 0;
}

void Protester::decPerpendicularTurn(){
    hasmadepturn--;
}

void Protester::resetPerpendicularTurn(){
    hasmadepturn = 200;
}

void RegularProtester::move(){
    //dead
    if (!isAlive()) {
        return;
    }
    
    if (shouldLeaveOilField()) {
        cout << "leave";
        setDead();
    }
    
    getWorld()->askForGold(this);
    
    //waiting
    if (getTicksLeft() > 0) {
        decTicksLeft();
        return;
    } else{
        setTicksPerMove();
        setTicksLeft(getTicksPerMove());
    }
    decPerpendicularTurn();
    //shouting gap
    if (hasShouted()) {
        decHasShouted();
    }
    
    //maze solving leave
    if (shouldLeaveOilField()) {
        //leave
        
        setDead();
        return;
    }
    
    if (!hasShouted() && getWorld()->canAnnoy(getX(), getY(), getDirection())) {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        getWorld()->annoyFrackMan(2);
        resetHasShouted();
        return;
    }
    Dir dir = none;
    if (getWorld()->lineOfSight(this, dir)) {
        if (dir != none) {
            setDirection(dir);
            if (getWorld()->moveOne(this, dir)) {
                ;
            }
        }
        return;
    }
    dir = getDirection();
    //if (stepsLeft > 0 && getWorld()->canMove(this, dir)) {
    if (stepsLeft <= 0) {
        dir = getWorld()->getRandDirection(this);
        setDirection(dir);
        stepsLeft = rand() % 53 + 8;
    } else if (!hasMadePerpendicularTurn() && getWorld()->atIntersection(this, dir)) {
        setDirection(dir);
        stepsLeft = rand() % 53 + 8;
        resetPerpendicularTurn();
    }
    if (getWorld()->canMove(this, getDirection())) {
        getWorld()->moveOne(this, dir);
    } else{
        stepsLeft = 0;
    }
}


void HardcoreProtester::move(){
    //dead
    if (!isAlive()) {
        return;
    }
    
    if (shouldLeaveOilField()) {
        cout << "leave";
        setDead();
    }
    
    getWorld()->askForGold(this);
    
    //waiting
    if (getTicksLeft() > 0) {
        decTicksLeft();
        return;
    } else{
        setTicksPerMove();
        setTicksLeft(getTicksPerMove());
    }
    decPerpendicularTurn();
    //shouting gap
    if (hasShouted()) {
        decHasShouted();
    }
    
    //maze solving leave
    if (shouldLeaveOilField()) {
        //leave
        
        setDead();
        return;
    }
    
    if (!hasShouted() && getWorld()->canAnnoy(getX(), getY(), getDirection())) {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        getWorld()->annoyFrackMan(2);
        resetHasShouted();
        return;
    }
    int m = 16 + getWorld()->getLevel()*2;
    if (getWorld()->isTrackable(getX(), getY(), m)) {
        //trackFrackman
        return;
    }
    Dir dir = none;
    if (getWorld()->lineOfSight(this, dir)) {
        if (dir != none) {
            setDirection(dir);
            if (getWorld()->moveOne(this, dir)) {
                ;
            }
        }
        return;
    }
    dir = getDirection();
    //if (stepsLeft > 0 && getWorld()->canMove(this, dir)) {
    if (stepsLeft <= 0) {
        dir = getWorld()->getRandDirection(this);
        setDirection(dir);
        stepsLeft = rand() % 53 + 8;
    } else if (!hasMadePerpendicularTurn() && getWorld()->atIntersection(this, dir)) {
        setDirection(dir);
        stepsLeft = rand() % 53 + 8;
        resetPerpendicularTurn();
    }
    if (getWorld()->canMove(this, getDirection())) {
        getWorld()->moveOne(this, dir);
    } else{
        stepsLeft = 0;
    }
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
    vector<Actor*> items = getWorld()->getItems();
    for (int i = 0; i < items.size(); i++){
        if (getWorld()->isNear(getX(), getY(), items[i]->getX(), items[i]->getY(), 3)){
            if((items[i]->getID() == IID_PROTESTER)) {
                items[i]->annoy(2);
                setDead();
            }
            if (items[i]->getID() == IID_HARD_CORE_PROTESTER) {
                items[i]->annoy(3);
                setDead();
            }
        }
    }
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


void ActivatingObject::playSound(int x){
    getWorld()->playSound(x);
}
void ActivatingObject::setTicksToLive(int ticks){
    ttl = ticks;
}
void ActivatingObject::move(){
    
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


