#include "spacesystems.h"

PlanetSystem::~PlanetSystem()
{
    clear();
}

void PlanetSystem::add(VisibleObject *in)
{
    planet_system_object.push_back(in);
}
void PlanetSystem::remove(int i)
{
    planet_system_object.erase(planet_system_object.begin() + i);
}

void PlanetSystem::tickMove()
{
    for (auto &planet : planet_system_object)
    {
        planet->setYAng(planet->getYAng() + planet->getANG_PER_TICK_ROUND_ORBITE());


        Dot3D<double> cent = planet->getPosDot();
        Dot3D<double> turning_cent = planet->getTurningCent();
        double a = planet->getANG_PER_TICK_ROUND_SUN()*M_PI/180;
        double b = planet->getANG_PER_TICK_ROUND_TURNCENT()*M_PI/180;

        planet->setTurningCentX(turning_cent.x*cos(a) - turning_cent.z*sin(a));
        planet->setTurningCentZ(turning_cent.z*cos(a) + turning_cent.x*sin(a));
        if (fabs(a - b) > 1e-4)
        {
            planet->setX(cent.x*cos(a) - cent.z*sin(a));
            planet->setZ(cent.z*cos(a) + cent.x*sin(a));
            cent = planet->getPosDot();
        }
        turning_cent = planet->getTurningCent();

        planet->setX(turning_cent.x + (cent.x-turning_cent.x)*cos(b) - (cent.z-turning_cent.z)*sin(b));
        planet->setZ(turning_cent.z + (cent.z-turning_cent.z)*cos(b) + (cent.x-turning_cent.x)*sin(b));

    }
}

VisibleObject* PlanetSystem::operator [](int i) const
{
    if (i >= planet_system_object.size() || i < 0)
    {
        throw VecRangeErr("PlanetSystem::operator[] from spacesystems.cpp");
    }
    return planet_system_object[i];
}
int PlanetSystem::size() const
{
    return planet_system_object.size();
}

void PlanetSystem::setObj(Obj &in)
{
    if (planet_system_object.size() == 0)
    {
        throw VecRangeErr("PlanetSystem::setObj in spacesystems.cpp");
    }

    planet_system_object[0]->setObj(in);
}
void PlanetSystem::clear()
{
    for (int i = 0; i < planet_system_object.size(); i++)
    {
        delete planet_system_object[i];
        planet_system_object[i] = nullptr;
    }

    planet_system_object.clear();
}


SolarSystem::~SolarSystem()
{
    clear();
}

void SolarSystem::add(PlanetSystem *in)
{
    planet_systems.push_back(in);
}
void SolarSystem::remove(int i)
{
    planet_systems.erase(planet_systems.begin() + i);
}

void SolarSystem::tickMove()
{
    for (auto &system : planet_systems)
    {
        system->tickMove();
    }
}

PlanetSystem* SolarSystem::operator [](int i) const
{
    if (i >= planet_systems.size() || i < 0)
    {
        throw VecRangeErr("SolarSystem::operator[] from spacesystems.cpp");
    }
    return planet_systems[i];
}
int SolarSystem::size() const
{
    return planet_systems.size();
}

void SolarSystem::setObj(Obj &in)
{
    planet_systems[0]->setObj(in);
}
void SolarSystem::clear()
{
    for (int i = 0; i < planet_systems.size(); i++)
    {
        delete planet_systems[i];
        planet_systems[i] = nullptr;
    }

    planet_systems.clear();
}
