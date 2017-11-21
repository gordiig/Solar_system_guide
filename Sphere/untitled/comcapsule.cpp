#include "comcapsule.h"

void DxCom::exec(Camera &in)
{
    if (in.getId() == fixed_cam)
    {
        return;
    }

    double x = in.getRightAxisX();
    double y = in.getRightAxisY();
    double z = in.getRightAxisZ();

    in.setX(in.getX() + x*var);
    in.setY(in.getY() + y*var);
    in.setZ(in.getZ() + z*var);
}
void DyCom::exec(Camera &in)
{
    if (in.getId() == fixed_cam)
    {
        return;
    }

    double x = in.getUpAxisX();
    double y = in.getUpAxisY();
    double z = in.getUpAxisZ();

    in.setX(in.getX() + x*var);
    in.setY(in.getY() + y*var);
    in.setZ(in.getZ() + z*var);
}
void DzCom::exec(Camera &in)
{
    if (in.getId() == fixed_cam)
    {
        return;
    }

    double x = in.getViewAxisX();
    double y = in.getViewAxisY();
    double z = in.getViewAxisZ();

    in.setX(in.getX() + x*var);
    in.setY(in.getY() + y*var);
    in.setZ(in.getZ() + z*var);
}

void DxAngCom::exec(Camera &in)
{
    in.setXAng(in.getXAng() + var);
}
void DyAngCom::exec(Camera &in)
{
    in.setYAng(in.getYAng() + var);
}
void DzAngCom::exec(Camera &in)
{
    in.setZAng(in.getZAng() + var);
}
