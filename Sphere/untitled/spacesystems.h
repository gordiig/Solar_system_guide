#ifndef SPACESYSTEMS_H
#define SPACESYSTEMS_H


#include "obj.h"

class BaseSystem
{
public:
    virtual void remove(int) = 0;
    virtual void tickMove() = 0;
};


class PlanetSystem : public BaseSystem
{
protected:
    std::vector<Sphere*> planet_system_object;

public:
    void add(Sphere*);
    virtual void remove(int) override;

    virtual void tickMove() override;
};

class SolarSystem : public BaseSystem
{
protected:
    std::vector<PlanetSystem*> planet_systems;

public:
    void add(PlanetSystem*);
    virtual void remove(int) override;

    virtual void tickMove() override;

};

#endif // SPACESYSTEMS_H
