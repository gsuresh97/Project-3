#include "StudentWorld.h"
#include <string>
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
    
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHealth());
    
    m_man->doSomething();
    int mx = m_man -> getX();
    int my = m_man -> getY();
    //        if(my <= 59 && my >= 0 && mx <= 63 && mx >= 0){
    //            if (m_dirt[59 - my][mx] != nullptr) {
    //                delete m_dirt[59 - my][mx];
    //                m_dirt[59 - my][mx] = nullptr;
    //            }
    //
    //        }
    
    for(int y = my; y < my + 4; y++){
        for(int x = mx; x < mx + 4; x++){
            if(y <= 59 && y >= 0 && x >=0 && x <=63 && m_dirt[59 - y][x] != nullptr){
                delete m_dirt[59 - y][x];
                m_dirt[59 - y][x] = nullptr;
            }
        }
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
    
    
    //frackman
    m_man = new FrackMan(IID_PLAYER, 30, 60, this);
    //m_man->setWorld(&this);
    m_man->setVisible(true);
    
    displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHealth());
    
    return GWSTATUS_CONTINUE_GAME;
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
