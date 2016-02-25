#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0):GraphObject(imageID, startX, startY, dir, size, depth), m_world(world){
        setVisible(true);
        dead = false;
    }
    
    // Action to perform each tick. ----------------------------------------make pure virtual
    virtual void move();
    
    // Is this actor alive?
    bool isAlive() const;
    
    // Mark this actor as dead.
    void setDead();
    
    // Annoy this actor. ------------------------------------------redo
    virtual bool annoy(unsigned int amt);
    
    // Get this actor's world
    StudentWorld* getWorld() const{
        return m_world;
    }

    
    // Can other actors pass through this actor? ----------------------------redo
    virtual bool canActorsPassThroughMe() const;
    
    // Can this actor dig through dirt? ----------------------------redo
    virtual bool canDigThroughDirt() const;
    
    // Can this actor pick items up? ----------------------------redo
    virtual bool canPickThingsUp() const;

    // Does this actor hunt the FrackMan? ----------------------------redo
    virtual bool huntsFrackMan() const;
    
    // Can this actor need to be picked up to finish the level? ----------------------------redo
    virtual bool needsToBePickedUpToFinishLevel() const;
    
    // Move this actor to x,y if possible, and return true; otherwise,
    // return false without moving.
    bool moveToIfPossible(int x, int y);
    
private:
    StudentWorld* m_world;
    bool dead;
};

class Agent : public Actor
{
public:
    Agent(int imageID, int startX, int startY, StudentWorld* world, unsigned int hitPoints, unsigned int score, Direction dir = right, double size = 1.0, unsigned int depth = 0): Actor(imageID, startX, startY, world, dir, size, depth){
        m_hitPoints = hitPoints;
        m_score = score;
    }
    
    // Pick up a gold nugget. ----------------------------redo
    virtual void addGold();
    
    // How many hit points does this actor have left?
    unsigned int getHitPoints() const;
    unsigned int getScore() const;
    void setHitPoints();
    void setScore();
    
    virtual bool hasMoved() = 0;
    
    //-----------------------------------------------------------redo
    virtual bool annoy(unsigned int amount);
    
    //------------------------------------------------------------redo
    virtual bool canPickThingsUp() const;
    
private:
    unsigned int m_hitPoints;
    unsigned int m_score;
};

class FrackMan : public Agent
{
public:
    FrackMan(int imageID, int startX, int startY, StudentWorld* world, unsigned int hitPoints, unsigned int score, Direction dir = right, double size = 1.0, unsigned int depth = 0):Agent(imageID, startX, startY, world, hitPoints, score, dir, size, depth){
        
    }
    virtual void move();
    virtual bool annoy(unsigned int amount);
    virtual void addGold();
    virtual bool canDigThroughDirt() const;

    
    virtual bool hasMoved();
    // Pick up a sonar kit.
    void addSonar();
    
    // Pick up water.
    void addWater();
    
    // Get amount of gold
    unsigned int getGold() const;
    
    // Get amount of sonar charges
    unsigned int getSonar() const;
    
    // Get amount of water
    unsigned int getWater() const;
    
    virtual ~FrackMan(){}
private:
    bool m_moved;
};



class Protester : public Agent
{
public:
    Protester(int imageID, int startX, int startY, StudentWorld* world, unsigned int hitPoints, unsigned int score, Direction dir = right, double size = 1.0, unsigned int depth = 0):Agent(imageID, startX, startY, world, hitPoints, score, dir, size, depth){
        
    }
    virtual void move();
    virtual bool annoy(unsigned int amount);
    virtual void addGold();
    virtual bool huntsFrackMan() const;
    
    // Set state to having gien up protest
    void setMustLeaveOilField();
    
    // Set number of ticks until next move
    void setTicksToNextMove();
};

class RegularProtester : public Protester
{
public:
    RegularProtester(int imageID, int startX, int startY, StudentWorld* world, unsigned int hitPoints, unsigned int score):Protester(imageID, startX, startY, world, hitPoints, score){
        
    }
    virtual void move();
    virtual void addGold();
};

class HardcoreProtester : public Protester
{
public:
    HardcoreProtester(int imageID, int startX, int startY, StudentWorld* world, unsigned int hitPoints, unsigned int score):Protester(imageID, startX, startY, world, hitPoints, score){
        
    }
    virtual void move();
    virtual void addGold();
};

class Dirt : public Actor{
public:
    Dirt(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, double size = 0.25, unsigned int depth = 3):Actor(imageID, startX, startY, world, dir, size, depth){
        
    }
    
    virtual void move();
    
    virtual ~Dirt(){}
private:
};


class Boulder : public Actor
{
public:
    Boulder(int imageID, int startX, int startY, StudentWorld* world, Direction dir = down, double size = 1, unsigned int depth = 1):Actor(imageID, startX, startY, world, dir, size, depth){
        state = 's';
        wait = 0;
    }
    virtual void move();
    virtual bool canActorsPassThroughMe() const;
    void setState(char c);
    char getState();
    int getW();
    void incrementW();
    
    
private:
    char state;
    int wait;
};

class Squirt : public Actor
{
public:
    Squirt(int imageID, int startX, int startY, StudentWorld* world):Actor(imageID, startX, startY, world){
        
    }
    virtual void move();
};

class ActivatingObject : public Actor
{
public:
    ActivatingObject(int imageID, int startX, int startY, StudentWorld* world,
                     int soundToPlay, bool activateOnPlayer,
                     bool activateOnProtester, bool initallyActive);
    virtual void move();
    
    // Set number of ticks until this object dies
    void setTicksToLive();
};

class OilBarrel : public ActivatingObject
{
public:
    OilBarrel(StudentWorld* world, int startX, int startY);
    virtual void move();
    virtual bool needsToBePickedUpToFinishLevel() const;
};

class GoldNugget : public ActivatingObject
{
public:
    GoldNugget(StudentWorld* world, int startX, int startY, bool temporary);
    virtual void move();
};

class SonarKit : public ActivatingObject
{
public:
    SonarKit(StudentWorld* world, int startX, int startY);
    virtual void move();
};

class WaterPool : public ActivatingObject
{
public:
    WaterPool(StudentWorld* world, int startX, int startY);
    virtual void move();
};

#endif // ACTOR_H_
