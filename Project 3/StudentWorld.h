#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include "Actor.h"
#include <vector>
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
    
    void clearDirt(int x, int y);
    bool inOilField(int x, int y);
    void displayGameStatText(int score, int level, int lives, int health);
    bool isNear(int x1, int y1, int x2, int y2, int dist);
    std::vector<Actor*> getItems();
    bool goodSpotBGO(int x, int y);
    bool isFreeUnder(int x, int y);
    bool canMoveDown(int x, int y);
    
private:
    Dirt* m_dirt[60][64];
    FrackMan* m_man;
    int numBoulders;
    int numNuggets;
    int numOil;
    std::vector<Actor*> items;
};

#endif // STUDENTWORLD_H_
