#include "StudentWorld.h"
#include <string>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


StudentWorld::~StudentWorld(){
    if(m_man != nullptr){
        delete m_man;
        m_man = nullptr;
    }
    for(int y = 0; y< 60; y++){
        for(int x = 0; x < 64; x++){
            if(m_dirt[y][x] != nullptr){
                delete m_dirt[y][x];
                m_dirt[y][x] = nullptr;
            }
        }
    }
}

void StudentWorld::cleanUp()
{
    delete m_man;
    m_man = nullptr;
    for(int y = 0; y< 60; y++){
        for(int x = 0; x < 64; x++){
            if(m_dirt[y][x] != nullptr){
                delete m_dirt[y][x];
                m_dirt[y][x] = nullptr;
            }
        }
    }
}

int StudentWorld::move()
{
    //decLives();
    displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHitPoints());
    
    m_man->move();
    if (m_man->hasMoved()) {
        clearDirt(m_man->getX(), m_man->getY());
    }
    
    for (int i = 0; i < items.size(); i++) {
        items[i]->move();
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::init()
{
    //2d array of dirt
    for(int y = 0; y< 60; y++){
        for(int x = 0; x < 64; x++){
            if(x < 30 || x > 33){
                m_dirt[59 - y][x] = new Dirt(IID_DIRT, x, y, this);
                m_dirt[59 - y][x]->setVisible(true);
            } else if(y < 4){
                m_dirt[59 - y][x] = new Dirt(IID_DIRT, x, y, this);
                m_dirt[59 - y][x]->setVisible(true);
            } else{
                m_dirt[59 - y][x] = nullptr;
            }
        }
    }
    
    numBoulders = getLevel()/2+2 > 6? 6: getLevel()/2+2;
    numNuggets = 5-getLevel()/ 2 > 2? 5-getLevel()/ 2 : 2;
    numOil = 2+getLevel() < 20? 2+getLevel(): 20;
    
    for (int i = 0; i < numBoulders; i++) {
        int x = 0;
        int y = 0;
        do{
            x= rand() % 61;
            y= rand() % 57;
        }while (!goodSpotBGO(x, y));
        
        
        Boulder* b = new Boulder(IID_BOULDER, x, y, this);
        clearDirt(x, y);
        b->setVisible(true);
        items.push_back(b);
        b->setState('s');
    }
    
    //frackman
    m_man = new FrackMan(IID_PLAYER, 30, 60, this, 10, 0);
    //m_man->setWorld(&this);
    m_man->setVisible(true);
    
    displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHitPoints());
    
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::goodSpotBGO(int x, int y){
    if(y > 3 && (x > 26 && x < 34)){
        return false;
    }
    for(int i = 0; i < items.size(); i++){
        if(items[i]->getID() ==IID_BARREL || items[i]->getID()==IID_GOLD|| items[i]->getID()==IID_BOULDER){
            if (isNear(x, y, items[i]->getX(), items[i]->getY(), 6)){
                return false;
            }
        }
    }
    return true;
}

vector<Actor*> StudentWorld::getItems(){
    return items;
}

bool StudentWorld::inOilField(int x, int y){
    return (x < 64 && x >= 0 && y < 60 && y >= 0);
}

bool StudentWorld::inSquirtField(int x, int y){
    return (x < 64 && x >= 0 && y < 64 && y >= 0);
}

void StudentWorld::clearDirt(int x, int y){
    for(int my = y; my < y + 4; my++){
        for (int mx = x; mx < x+4; mx++) {
            if(inOilField(mx, my) && m_dirt[59-my][mx] !=nullptr){
                delete m_dirt[59-my][mx];
                m_dirt[59-my][mx] = nullptr;
            }
        }
    }
}

bool StudentWorld::isNear(int x1, int y1, int x2, int y2, int dist){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) <= dist;
}

bool StudentWorld::isFreeUnder(int x, int y){
    return m_dirt[59 - y + 1][x] == nullptr && m_dirt[59 - y + 1][x + 1] == nullptr && m_dirt[59 - y + 1][x + 2] == nullptr && m_dirt[59 - y + 1][x + 3] == nullptr;
}

bool StudentWorld::canMoveDown(int x, int y){
    if(y == 0)
        return false;
    for (int i = 0; i < items.size(); i++) {
        if(items[i]->getID() == IID_BOULDER){
            int my = items[i]->getY();
            int mx = items[i]->getX();
            for (int j = mx; j < mx+4; j++) {
                for(int k = x; k < x+4; k++){
                    if (j == k && y - 1 == my + 3) {
                        return false;
                    }
                }
            }
        }
    }
    return isFreeUnder(x, y);
}

void StudentWorld::addSquirt(){
    Squirt* it;
    int x = -1;
    int y = -1;
    GraphObject::Direction dir = GraphObject::none;
    m_man->getSquirtDets(x, y, dir);
    if(x != -1 && y!= -1){
        it = new Squirt(IID_WATER_SPURT, x, y, this, dir, 1, 1);
        items.push_back(it);
        it->setVisible(true);
    }
}

void StudentWorld:: displayGameStatText(int score, int level, int lives, int health){
    std::string s = "Scr: ";
    s += score;
    s += " Lvl: ";
    s += level;
    s += " Lives: ";
    s += lives;
    s += " Hlth: ";
    s += health;
    
    setGameStatText(s);
    
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
