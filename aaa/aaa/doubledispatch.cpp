//#include "SpaceShip.h"
//#include "SpaceStation.h"
//#include "Asteroid.h"
#include "doubledispatch.hpp"
#include<map>
#include<string>
using namespace std;
namespace                       // unnamed namespace .see below
{
    class UnknownCollision
    {
    public:
        UnknownCollision(GameObject& object1, GameObject& object2){}
    };
    // primary collision-processing functions
    void shipAsteroid(GameObject& spaceShip, GameObject& asteroid)
    {}
    void shipStation(GameObject& spaceShip, GameObject& spaceStation)
    {}
    void asteroidStation(GameObject& asteroid, GameObject& spaceStation)
    {}
    ////...
    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function
    void asteroidShip(GameObject& asteroid, GameObject& spaceShip)
    {
        shipAsteroid(spaceShip, asteroid);
    }
    void stationShip(GameObject& spaceStation, GameObject& spaceShip)
    {
        shipStation(spaceShip, spaceStation);
    }
    void stationAsteroid(GameObject& spaceStation, GameObject& asteroid)
    {
        asteroidStation(asteroid, spaceStation);
    }
    void satelliteShip(GameObject& satellite, GameObject& spaceShip)
    {}
    void satelliteAsteroid(GameObject& satellite, GameObject& asteroid)
    {}
    ////...
    // see below for a description of these types/functions
    typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    typedef map< pair<string,string>, HitFunctionPtr > HitMap;
    // map<const type_info *, HitFunctionPtr>;
    pair<string,string> makeStringPair(const char *s1,
        const char *s2);
    HitMap * initializeCollisionMap();
    HitFunctionPtr lookup(const string& class1,
        const string& class2);
} // end namespace
void processCollision(GameObject& object1,
    GameObject& object2)
{
    HitFunctionPtr phf = lookup(typeid(object1).name(),
        typeid(object2).name());
    if (phf) phf(object1, object2);
    else throw UnknownCollision(object1, object2);
}
// we use this function to create pair<string,string>
// objects from two char* literals. It's used in
// initializeCollisionMap below. Note how this function
// enables the return value optimization (see Item 20).

namespace            // unnamed namespace again . see below
{
    pair<string,string> makeStringPair(const char *s1,
        const char *s2)
    {
        return pair<string,string>(s1, s2);
    }
} // end namespace

namespace            // still the unnamed namespace . see below
{
    HitMap * initializeCollisionMap()
    {
        HitMap *phm = new HitMap;
        (*phm)[makeStringPair("SpaceShip","Asteroid")] =
            &shipAsteroid;
        (*phm)[makeStringPair("SpaceShip", "SpaceStation")] =
            &shipStation;
        ////...
        return phm;
    }
} // end namespace

namespace            // I explain this below . trust me
{
    HitFunctionPtr lookup(const string& class1,
        const string& class2)
    {
        static auto_ptr<HitMap>
            collisionMap(initializeCollisionMap());
        // see below for a description of make_pair
        HitMap::iterator mapEntry=
            collisionMap->find(make_pair(class1, class2));
        if (mapEntry == collisionMap->end()) return 0;
        return (*mapEntry).second;
    }
} // end namespace

class CollisionMap
{
public:
    typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    void addEntry(const string& type1,
        const string& type2,
        HitFunctionPtr collisionFunction,
        bool symmetric = true);               // see below
    void removeEntry(const string& type1,
        const string& type2);
    HitFunctionPtr lookup(const string& type1,
        const string& type2);
    // this function returns a reference to the one and only
    // map . see Item 26
    static CollisionMap& theCollisionMap();
private:
    // these functions are private to prevent the creation
    // of multiple maps . see Item 26
    CollisionMap(){}
    CollisionMap(const CollisionMap&);
};
void CollisionMap::addEntry(const string& type1, const string& type2, HitFunctionPtr collisionFunction, bool symmetric)
{}
CollisionMap& CollisionMap::theCollisionMap()
{
    static CollisionMap  acolmap;
    return acolmap;
}



class RegisterCollisionFunction
{
public:
    RegisterCollisionFunction(
        const string& type1,
        const string& type2,
        CollisionMap::HitFunctionPtr collisionFunction,
        bool symmetric = true) {
            CollisionMap::theCollisionMap().addEntry(type1, type2, collisionFunction, symmetric);
    }
};


void testDoubleDispatch( )
{
    CollisionMap::theCollisionMap().addEntry("SpaceShip",    "Asteroid",    &shipAsteroid);
    CollisionMap::theCollisionMap().addEntry("SpaceShip", "SpaceStation", &shipStation);
    CollisionMap::theCollisionMap().addEntry("Asteroid", "SpaceStation", &asteroidStation);
    ////...
    RegisterCollisionFunction cf1("SpaceShip", "Asteroid", &shipAsteroid);
    RegisterCollisionFunction cf2("SpaceShip", "SpaceStation", &shipStation);
    RegisterCollisionFunction cf3("Asteroid", "SpaceStation", &asteroidStation);
    ////...

    RegisterCollisionFunction cf4("Satellite", "SpaceShip", &satelliteShip);
    RegisterCollisionFunction cf5("Satellite", "Asteroid", &satelliteAsteroid);
    ////...
}


/////////////////doubledispatch.hpp/////////////////
SpaceShip::HitMap * SpaceShip::initializeCollisionMap()
{
    HitMap *phm = new HitMap;
    (*phm)["SpaceShip"] = &hitSpaceShip;
    (*phm)["SpaceStation"] = &hitSpaceStation;
    (*phm)["Asteroid"] = &hitAsteroid;
    return phm;
}
void SpaceShip::hitSpaceShip(GameObject& spaceShip)
{
    SpaceShip& otherShip=
        dynamic_cast<SpaceShip&>(spaceShip);
    //process a SpaceShip-SpaceShip collision;
}
void SpaceShip::hitSpaceStation(GameObject& spaceStation)
{
    SpaceStation& station=
        dynamic_cast<SpaceStation&>(spaceStation);
    //process a SpaceShip-SpaceStation collision;
}
void SpaceShip::hitAsteroid(GameObject& asteroid)
{
    Asteroid& theAsteroid =
        dynamic_cast<Asteroid&>(asteroid);
    //process a SpaceShip-Asteroid collision;
}
void SpaceShip::collide(GameObject& otherObject)
{
    HitFunctionPtr hfp =
        lookup(otherObject);                // find the function to call
    if (hfp) {                            // if a function was found
        (this->*hfp)(otherObject);          // call it
    } else {
        throw CollisionWithUnknownObject(otherObject);
    }
}


SpaceShip::HitFunctionPtr
SpaceShip::lookup(const GameObject& whatWeHit)
{
    static auto_ptr<HitMap>
    collisionMap(initializeCollisionMap());
    // look up the collision-processing function for the type
    // of whatWeHit. The value returned is a pointer-like
    // object called an "iterator" (see Item 35).
    HitMap::iterator mapEntry=
        collisionMap->find(typeid(whatWeHit).name());//.
    // mapEntry == collisionMap.end() if the lookup failed;
    // this is standard map behavior. Again, see Item 35.
    if (mapEntry == collisionMap->end()) return 0;//.
    // If we get here, the search succeeded. mapEntry
    // points to a complete map entry, which is a
    // (string, HitFunctionPtr) pair. We want only the
    // second part of the pair, so that's what we return.
    return (*mapEntry).second;
}

/////////////////doubledispatch.hpp/////////////////