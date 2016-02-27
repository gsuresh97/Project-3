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
    bool inSquirtField(int x, int y);
    bool isNear(int x1, int y1, int x2, int y2, int dist);
    std::vector<Actor*> getItems();
    bool goodSpotBGO(int x, int y);
    bool isFreeUnder(int x, int y);
    bool canMoveDown(int x, int y);
    void addSquirt();
    bool canMove(Actor* a, GraphObject::Direction dir);
    void addGold();
    void addSonarWater();
    void addProtestor();
    bool squirtCanMove(int x, int y, GraphObject::Direction dir);
    bool isFrackManNear(int x, int y, int dist);
    void oilFound();
    void goldFound();
    void waterFound();
    void chargeFound();
    bool fourFree(int x, int y);
    bool canAnnoy(int x, int y, GraphObject::Direction dir);
    void annoyFrackMan(int hp);
    bool lineOfSight(Protester* a, GraphObject::Direction& dir);
    bool moveOne(Actor* a, GraphObject::Direction dir);
    bool atIntersection(Protester* a, GraphObject::Direction& dir);
    bool askForGold(Protester* p);
    bool isTrackable(int x, int y, int dist);
    void solveFrackman(Protester* p, int&x, int&y);
    void updateFrackManMaze();
    GraphObject::Direction getRandDirection(Actor* a);
    
private:
    Dirt* m_dirt[60][64];
    FrackMan* m_man;
    int numBoulders;
    int numNuggets;
    int numOil;
    std::vector<Actor*> items;
    int protestorAdded;
    int targetProtestors;
    int numProtestors;
    int probHardcore;
    int tToProtestor;
    char frackManMaze[64][64];
};

#endif // STUDENTWORLD_H_
