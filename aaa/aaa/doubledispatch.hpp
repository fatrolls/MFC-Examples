#pragma  once
#include<map>
#include<string>
using namespace std;
class GameObject                      // this is unchanged
{
public:
    virtual void collide(GameObject& otherObject) = 0;
    ////...
};
class SpaceShip: public GameObject
{
public:
    typedef void (SpaceShip::*HitFunctionPtr)(GameObject&);
    typedef map<string, HitFunctionPtr> HitMap;
    static HitMap * initializeCollisionMap();
    static HitFunctionPtr lookup(const GameObject& whatWeHit);
    virtual void collide(GameObject& otherObject);
    // these functions now all take a GameObject parameter
    virtual void hitSpaceShip(GameObject& spaceShip);
    virtual void hitSpaceStation(GameObject& spaceStation);
    virtual void hitAsteroid(GameObject& asteroid);
    ////...
};

class SpaceStation: public GameObject {};

class Asteroid: public GameObject{};

class CollisionWithUnknownObject 
{
public:
    CollisionWithUnknownObject(GameObject& whatWeHit){}
  /////...
};

