#include "camera.h"

Camera::Camera() : BaseObject::BaseObject()
{
    view_axis.setZ(1);
    right_axis.setX(1);
    up_axis.setY(1);
    distance_to_screen = 500;
    z = -700;
}
Camera::Camera(double in_x, double in_y, double in_z) : BaseObject::BaseObject(in_x, in_y, in_z) { }

Camera::Camera(const Camera &in)
{
    (*this) = in;
}
Camera::Camera(Camera &&in)
{
    (*this) = in;
    in.clear();
}
Camera& Camera::operator = (const Camera& in)
{
    view_axis = in.view_axis;
    right_axis = in.right_axis;
    up_axis = in.up_axis;
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;

    return (*this);
}
Camera& Camera::operator = (Camera&& in)
{
    view_axis = in.view_axis;
    right_axis = in.right_axis;
    up_axis = in.up_axis;
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;

    in.clear();
    return (*this);
}

void Camera::moveToWorldCenter()
{
    clear();
    view_axis.setZ(-1);
    up_axis.setY(1);
    right_axis.setX(1);
}
void Camera::clear()
{
    view_axis.clear();
    up_axis.clear();
    right_axis.clear();
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
}

bool Camera::isPolyViz(const Points3D &points) const
{
    if (points.size() < 3)
    {
        throw NotEnoughPointsForPoly("\nIn file \"Camera.cpp\" in Camera::IsPolyVis()\n");
    }

    /*
    double a = points[0].y * (points[1].z-points[2].z) +
            points[1].y * (points[2].z-points[0].z) +
            points[2].y * (points[0].z-points[1].z);

    double b = points[0].z * (points[1].x-points[2].x) +
            points[1].z * (points[2].x-points[0].x) +
            points[2].z * (points[0].x-points[1].x);


    double c = points[0].x * (points[1].y-points[2].y) +
            points[1].x * (points[2].y-points[0].y) +
            points[2].x * (points[0].y-points[1].y);

    double d = points[0].x * (points[1].y*points[2].z - points[2].y*points[1].z) +
            points[1].x * (points[2].y*points[0].z - points[0].y*points[2].z) +
            points[2].x * (points[0].y*points[1].z - points[1].y*points[0].z);

    d *= -1;

    return (d > 0) ? false : true;
    */

    return true;
}
bool Camera::isOnDisplay(const DotForDrawer &point) const
{
    return isOnDisplay(point.z);
}
bool Camera::isOnDisplay(const double z) const
{
    return (z > 100 /*distance_to_screen*/) ? true : false;
}

