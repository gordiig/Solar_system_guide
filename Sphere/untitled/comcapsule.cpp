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
