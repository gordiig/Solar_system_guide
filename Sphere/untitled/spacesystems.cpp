#include "spacesystems.h"

PlanetSystem::~PlanetSystem()
{
    clear();
}

void PlanetSystem::add(Sphere *in)
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
        planet->setYAng(planet->getYAng() + 1);
    }
}

std::vector<Sphere*>::iterator PlanetSystem::begin()
{
    return planet_system_object.begin();
}
std::vector<Sphere*>::iterator PlanetSystem::end()
{
    return planet_system_object.end();
}

Sphere* PlanetSystem::operator [](int i) const
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

std::vector<PlanetSystem*>::iterator SolarSystem::begin()
{
    return planet_systems.begin();
}
std::vector<PlanetSystem*>::iterator SolarSystem::end()
{
    return planet_systems.end();
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
