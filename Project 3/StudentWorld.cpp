#include "StudentWorld.h"
#include <string>
#include <cmath>
using namespace std;

class Coords{
public:
    Coords(int x, int y){
        mx = x;
        my = y;
    }
    int getX(){
        return mx;
    }
    int getY(){
        return my;
    }
private:
    int mx;
    int my;
};


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
    vector<Actor*>::iterator it;
    it = items.begin();
    while(it != items.end()){
        delete (*it);
        it++;
    }
    items.erase(items.begin(), items.end());
}

int StudentWorld::move()
{
    //decLives();
    //displayGameStatText(getScore(), getLevel(), getLives(), m_man->getHitPoints());
    //string stat = "Scr: ";
    char score[200];
    sprintf(score, "Scr: %0.6u  Lvl: %2u  Lives: %.1u  Hlth: %3u%%  Wtr: %2u  Gld: %2u  Sonar: %2u  Oil Left: %2d", getScore(), getLevel(), getLives(), (m_man->getHitPoints()/10)*100, m_man->getWater(), m_man->getGold(), m_man->getSonar(), numOil);
    setGameStatText(score);
    
    if (rand()%(getLevel()*25+300)==1) {
        addSonarWater();
    }
    
    m_man->move();
    if (m_man->hasMoved()) {
        clearDirt(m_man->getX(), m_man->getY());
    }
    
    for (int i = 0; i < items.size(); i++) {
        if (items[i])
            items[i]->move();
    }
    
    //remove dead items
    vector<Actor*>::iterator it;
    it = items.begin();
    if (!m_man->isAlive()) {
        playSound(SOUND_PLAYER_GIVE_UP);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    while(it != items.end()){
        if(!(*it)->isAlive()){
            delete (*it);
            it = items.erase(it);
        } else{
            it++;
        }
    }
    
    //check if level is over.
    if (numOil==0) {
        return GWSTATUS_FINISHED_LEVEL;
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
    
    
    
    //create boulders
    numBoulders = getLevel()/2+2 > 6? 6: getLevel()/2+2;
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
    
    //create Oil Barrels
    numOil = 2+getLevel() < 20? 2+getLevel(): 20;
    for (int i = 0; i < numOil; i++) {
        int x = 0;
        int y = 0;
        do{
            x= rand() % 61;
            y= rand() % 57;
        }while (!goodSpotBGO(x, y));
        
        OilBarrel* b = new OilBarrel(IID_BARREL, x, y, this);
        b->setVisible(false);
        items.push_back(b);
    }
    
    //create Gold
    numNuggets = 5-getLevel()/ 2 > 2? 5-getLevel()/ 2 : 2;
    for (int i = 0; i < numNuggets; i++) {
        int x = 0;
        int y = 0;
        do{
            x= rand() % 61;
            y= rand() % 57;
        }while (!goodSpotBGO(x, y));
        
        GoldNugget* g = new GoldNugget(IID_GOLD, x, y, this);
        g->setForFrackMan();
        g->setVisible(false);
        items.push_back(g);
    }
    
    //frackman
    m_man = new FrackMan(IID_PLAYER, 30, 60, this, 10, 0);
    m_man->setVisible(true);
    
    
    //prtestors
    protestorAdded = 25 > 200-getLevel()?25:200-getLevel();
    targetProtestors = 15 < 2 + getLevel()*1.5? 15:2 + getLevel()*1.5;
    numProtestors = 0;
    addProtestor();
        
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
    if (isNear(x, y, m_man->getX(), m_man->getY(), 3)) {
        m_man->setDead();
    }
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

bool StudentWorld::squirtCanMove(int x, int y, GraphObject::Direction dir){
    switch (dir) {
        case GraphObject::down:
            for (int i = 0; i < items.size(); i++) {
                if(items[i]->getID() == IID_BOULDER){
                    int my = items[i]->getY();
                    int mx = items[i]->getX();
                    if(abs(mx - x) < 4 && abs(my - y) < 4){
                        return false;
                    } else if(inOilField(x, y-1)){
                        if (m_dirt[59-y+1][x] || m_dirt[59-y+1][x+1] || m_dirt[59-y+1][x+2] || m_dirt[59-y+1][x+3]) {
                            return false;
                        }
                    }
                }
            }
            return true;
        case GraphObject::up:
            for (int i = 0; i < items.size(); i++) {
                if(items[i]->getID() == IID_BOULDER){
                    int my = items[i]->getY();
                    int mx = items[i]->getX();
                    if(abs(mx - x) < 4 && abs(my - y) < 4){
                        return false;
                    } else if(inOilField(x, y+4)){
                        if (m_dirt[59-y-4][x] || m_dirt[59-y-4][x+1] || m_dirt[59-y-4][x+2] || m_dirt[59-y-4][x+3]) {
                            return false;
                        }
                    }
                }
            }
            return true;
        case GraphObject::left:
            for (int i = 0; i < items.size(); i++) {
                if(items[i]->getID() == IID_BOULDER){
                    int my = items[i]->getY();
                    int mx = items[i]->getX();
                    if(abs(mx - x) < 4 && abs(my - y) < 4){
                        return false;
                    } else if(inOilField(x - 1, y)){
                        if (m_dirt[59-y][x-1] || m_dirt[59-y-1][x-1] || m_dirt[59-y-2][x-1] || m_dirt[59-y-3][x-1]) {
                            return false;
                        }
                    }
                }
            }
            return true;
        case GraphObject::right:
            for (int i = 0; i < items.size(); i++) {
                if(items[i]->getID() == IID_BOULDER){
                    int my = items[i]->getY();
                    int mx = items[i]->getX();
                    if(abs(mx - x) < 4 && abs(my - y) < 4){
                        return false;
                    } else if(inOilField(x, y+4)){
                        if (m_dirt[59-y][x+4] || m_dirt[59-y-1][x+4] || m_dirt[59-y-2][x+4] || m_dirt[59-y-3][x-1]) {
                            return false;
                        }
                    }
                    for (int j = my; j < my+4; j++) {
                        for(int k = y; k < y+4; k++){
                            if (m_dirt[59 - k][x + 4] != nullptr || (j == k && x + 4 == mx)) {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        default:
            return true;
    }
}

void StudentWorld::addSquirt(){
    Squirt* it;
    int x = -1;
    int y = -1;
    playSound(SOUND_PLAYER_SQUIRT);
    GraphObject::Direction dir = GraphObject::none;
    m_man->getSquirtDets(x, y, dir);
    if(x != -1 && y!= -1 && squirtCanMove(x, y, dir)){
        it = new Squirt(IID_WATER_SPURT, x, y, this, dir, 1, 1);
        items.push_back(it);
        it->setVisible(true);
    }
}

void StudentWorld::addGold(){
    GoldNugget* g;
    g = new GoldNugget(IID_GOLD, m_man->getX(), m_man->getY(), this);
    items.push_back(g);
    g->setForProtestor();
    g->setVisible(true);
}

void StudentWorld::addSonarWater(){
    if (rand()%5==0) {
        SonarKit* s = new SonarKit(IID_SONAR, 0, 60, this);
        s->setVisible(true);
        items.push_back(s);
    } else {
        vector<Coords> empties;
        for(int y = 0; y< 60; y++){
            for(int x = 0; x < 60; x++){
                if (fourFree(x, y)) {
                    Coords c(x,y);
                    empties.push_back(c);
                }
            }
        }
        int i = rand()%empties.size();
        WaterPool* w = new WaterPool(IID_WATER_POOL, empties[i].getX(), empties[i].getY(), this);
        w->setVisible(true);
        items.push_back(w);
        
    }
}

void StudentWorld::addProtestor(){
    numProtestors++;
    probHardcore = getLevel() * 10 + 30 < 90? getLevel() * 10 + 30: 90;
    if (rand() % 100 < probHardcore) {
        //create Hardcore
        HardcoreProtester* p = new HardcoreProtester(IID_HARD_CORE_PROTESTER, 60, 60, this, 20, 0);
        items.push_back(p);
        p->setVisible(true);
    } else{
        //create regular
        RegularProtester* p = new RegularProtester(IID_PROTESTER, 60, 60, this, 5, 0);
        items.push_back(p);
        p->setTicksPerMove();
        p->setVisible(true);
    }
}

bool StudentWorld::fourFree(int x, int y){
    bool ans = true;
    for (int i =0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans = m_dirt[59-(y+j)][x+i]? false: ans;
        }
    }
    return ans;
}


bool StudentWorld::isFrackManNear(int x, int y, int dist){
    return isNear(x, y, m_man->getX(), m_man->getY(), dist);
}

void StudentWorld::oilFound(){
    numOil--;
    //cout <<"oil: " << numOil << endl;
}

void StudentWorld::goldFound(){
    m_man->addGold();
}

void StudentWorld::chargeFound(){
    m_man->addSonar();
}

void StudentWorld::waterFound(){
    m_man->addWater();
}