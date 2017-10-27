#include "comcapsule.h"

void DxCom::exec(BaseObject &in)
{
    in.setX(in.getX() + var);
}

void DyCom::exec(BaseObject &in)
{
    in.setY(in.getY() + var);
}

void DzCom::exec(BaseObject &in)
{
    in.setZ(in.getZ() + var);
}

void DxAngCom::exec(BaseObject &in)
{
    in.setXAng(var);
}

void DyAngCom::exec(BaseObject &in)
{
    in.setYAng(var);
}

void DzAngCom::exec(BaseObject &in)
{
    in.setZAng(var);
}

void PlanetDxCom::exec(BaseObject &in)
{
    in.setX(in.getX() + 2);
}

void PlanetDyCom::exec(BaseObject &in)
{
    in.setY(in.getY() + 2);
}

void PlanetDzCom::exec(BaseObject &in)
{
    in.setZ(in.getZ() + 2);
}

void PlanetDxAngCom::exec(BaseObject &in)
{
    double ang = int((in.getXAng() + 10)) % 360;
    in.setXAng(ang);
}

void PlanetDyAngCom::exec(BaseObject &in)
{
    double ang = int((in.getYAng() + 10)) % 360;
    in.setYAng(ang);
}

void PlanetDzAngCom::exec(BaseObject &in)
{
    double ang = int((in.getZAng() + 10)) % 360;
    in.setZAng(ang);
}
