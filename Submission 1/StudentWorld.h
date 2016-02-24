#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include "Actor.h"
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
	{
        
	}

    virtual int init();
    
    
    
    
    virtual int move();
    
    virtual void cleanUp();
    
    ~StudentWorld();
    
    bool inBounds(int x, int y, int width, int height){
        return y+height;
    }
    
    
    void displayGameStatText(int score, int level, int lives, int health);

private:
    Dirt* m_dirt[60][64];
    FrackMan* m_man;
};

#endif // STUDENTWORLD_H_
