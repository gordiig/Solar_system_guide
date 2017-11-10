#ifndef SPACESYSTEMS_H
#define SPACESYSTEMS_H


#include "obj.h"
#include "errors.h"

class BaseSystem
{
public:
    virtual ~BaseSystem() {}

    virtual void remove(int) = 0;
    virtual void tickMove() = 0;
    virtual void setObj(Obj&) = 0;

    virtual int size() const = 0;
};


class PlanetSystem : public BaseSystem
{
protected:
    std::vector<Sphere*> planet_system_object;

public:
    ~PlanetSystem();

    void add(Sphere*);
    virtual void remove(int) override;

    virtual void tickMove() override;

    std::vector<Sphere*>::iterator begin();
    std::vector<Sphere*>::iterator end();

    Sphere* operator [] (int) const;
    virtual int size() const override;

    virtual void setObj(Obj&) override;
    void clear();
};

class SolarSystem : public BaseSystem
{
protected:
    std::vector<PlanetSystem*> planet_systems;
    double ORBIT_BASE_ROT_ANG;
    double SUN_BASE_ROT_ANG;

public:
    SolarSystem() : ORBIT_BASE_ROT_ANG(3), SUN_BASE_ROT_ANG(1){}
    ~SolarSystem();

    void add(PlanetSystem*);
    virtual void remove(int) override;

    virtual void tickMove() override;

    std::vector<PlanetSystem*>::iterator begin();
    std::vector<PlanetSystem*>::iterator end();

    PlanetSystem* operator [] (int) const;
    virtual int size() const override;

    virtual void setObj(Obj&) override;
    void clear();

    double getOrbitBaseAng() const { return ORBIT_BASE_ROT_ANG; }
    double getSunBaseAng() const { return SUN_BASE_ROT_ANG; }

    void setOrbitBaseAng(double in) { ORBIT_BASE_ROT_ANG = in; }
    void setSunBaseAng(double in) { SUN_BASE_ROT_ANG = in; }
};

#endif // SPACESYSTEMS_H
