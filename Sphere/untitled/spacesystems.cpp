#include "spacesystems.h"

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
        planet.setYAng(planet.getYAng() + 1);
    }
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
        system.tickMove();
    }
}
