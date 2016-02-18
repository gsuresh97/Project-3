#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
	{
        
	}

	virtual int init()
	{
        //2d array of dirt
        for(int y = 0; y< 60; y++){
            for(int x = 0; x < 64; x++){
                if(x < 30 || x > 33){
                    m_dirt[59 - y][x] = new Dirt(IID_DIRT, x, y);
                    m_dirt[59 - y][x]->setVisible(true);
                } else if(y < 4){
                    m_dirt[59 - y][x] = new Dirt(IID_DIRT, x, y);
                    m_dirt[59 - y][x]->setVisible(true);
                } else{
                    m_dirt[59 - y][x] = nullptr;
                }
            }
        }
        
        
        //frackman
        m_man = new FrackMan(IID_PLAYER, 30, 65);
        m_man->setVisible(true);
        
        displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHealth());
        //std::string p = sprintf("Scr: %u Lvl: %u Lives: %u Hlth: %d", getScore(), getLevel(), getLives(), m_man->getHealth());
        //setGameStatText("Scr: " + (int)(getScore()) + "Lvl: " + getLevel() +"Lives: " + getLives() "Hlth: " + m_man->getHealth());
        
		return GWSTATUS_CONTINUE_GAME;
	}
    
    
    void displayGameStatText(int score, int level, int lives, int health){
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
    
    void d_act(){
        for(int y = 59; y >= 0; y--){
            for(int x = 0; x < 64; x++){
                if(m_dirt[y][x] != nullptr){
                    m_dirt[y][x]->act(m_man->getX(), m_man->getY());
                    //m_dirt[59 - y][x]->setVisible(true);
                }
            }
        }
    }

	virtual int move()
	{
        
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		//decLives();
        displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHealth());
        int x;
        bool k;
        k = getKey(x);

        m_man->act(k, x);
        d_act();
        
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual void cleanUp()
	{
	}

private:
    Dirt* m_dirt[60][64];
    FrackMan* m_man;
};

#endif // STUDENTWORLD_H_
