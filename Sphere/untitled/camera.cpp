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
Camera::Camera(Dot3D<double> in_dot, double in_x_ang, double in_y_ang, double in_z_ang)
{
    x = in_dot.x;
    y = in_dot.y;
    z = in_dot.z;

    x_ang = in_x_ang;
    y_ang = in_y_ang;
    z_ang = in_z_ang;
}

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

double Camera::getRightAxisX() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector right_vector = right_axis;

    // Ох
    double y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(_x_ang) + right_vector.getZ()*sin(_x_ang));
    right_vector.setZ(-y_pr*sin(_x_ang) + right_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_y_ang) - right_vector.getZ()*sin(_y_ang));
    right_vector.setZ(x_pr*sin(_y_ang) + right_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_z_ang) - right_vector.getY()*sin(_z_ang));
    right_vector.setY(x_pr*sin(_z_ang) + right_vector.getY()*cos(_z_ang));

    return right_vector.getX();
}
double Camera::getRightAxisY() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector right_vector = right_axis;

    // Ox
    double y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(_x_ang) + right_vector.getZ()*sin(_x_ang));
    right_vector.setZ(-y_pr*sin(_x_ang) + right_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_y_ang) - right_vector.getZ()*sin(_y_ang));
    right_vector.setZ(x_pr*sin(_y_ang) + right_vector.getZ()*cos(_y_ang));


    // Oz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_z_ang) - right_vector.getY()*sin(_z_ang));
    right_vector.setY(x_pr*sin(_z_ang) + right_vector.getY()*cos(_z_ang));

    return right_vector.getY();
}
double Camera::getRightAxisZ() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector right_vector = right_axis;

    // Ox
    double y_pr = right_vector.getY();
    right_vector.setY(y_pr*cos(_x_ang) + right_vector.getZ()*sin(_x_ang));
    right_vector.setZ(-y_pr*sin(_x_ang) + right_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_y_ang) - right_vector.getZ()*sin(_y_ang));
    right_vector.setZ(x_pr*sin(_y_ang) + right_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = right_vector.getX();
    right_vector.setX(x_pr*cos(_z_ang) - right_vector.getY()*sin(_z_ang));
    right_vector.setY(x_pr*sin(_z_ang) + right_vector.getY()*cos(_z_ang));

    return right_vector.getZ();
}
MathVector Camera::getRightAxis() const
{
    return MathVector(getRightAxisX(), getRightAxisY(), getRightAxisZ());
}

double Camera::getUpAxisX() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector up_vector = up_axis;

    // Ox
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(_x_ang) + up_vector.getZ()*sin(_x_ang));
    up_vector.setZ(-y_pr*sin(_x_ang) + up_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_y_ang) - up_vector.getZ()*sin(_y_ang));
    up_vector.setZ(x_pr*sin(_y_ang) + up_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_z_ang) - up_vector.getY()*sin(_z_ang));
    up_vector.setY(x_pr*sin(_z_ang) + up_vector.getY()*cos(_z_ang));

    return up_vector.getX();
}
double Camera::getUpAxisY() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector up_vector = up_axis;

    // Ox
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(_x_ang) + up_vector.getZ()*sin(_x_ang));
    up_vector.setZ(-y_pr*sin(_x_ang) + up_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_y_ang) - up_vector.getZ()*sin(_y_ang));
    up_vector.setZ(x_pr*sin(_y_ang) + up_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_z_ang) - up_vector.getY()*sin(_z_ang));
    up_vector.setY(x_pr*sin(_z_ang) + up_vector.getY()*cos(_z_ang));

    return up_vector.getY();
}
double Camera::getUpAxisZ() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector up_vector = up_axis;

    // Ox
    double y_pr = up_vector.getY();
    up_vector.setY(y_pr*cos(_x_ang) + up_vector.getZ()*sin(_x_ang));
    up_vector.setZ(-y_pr*sin(_x_ang) + up_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_y_ang) - up_vector.getZ()*sin(_y_ang));
    up_vector.setZ(x_pr*sin(_y_ang) + up_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = up_vector.getX();
    up_vector.setX(x_pr*cos(_z_ang) - up_vector.getY()*sin(_z_ang));
    up_vector.setY(x_pr*sin(_z_ang) + up_vector.getY()*cos(_z_ang));

    return up_vector.getZ();
}
MathVector Camera::getUpAxis() const
{
    return MathVector(getUpAxisX(), getUpAxisY(), getUpAxisZ());
}

double Camera::getViewAxisX() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector view_vector = view_axis;

    // Ox
    double y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(_x_ang) + view_vector.getZ()*sin(_x_ang));
    view_vector.setZ(-y_pr*sin(_x_ang) + view_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_y_ang) - view_vector.getZ()*sin(_y_ang));
    view_vector.setZ(x_pr*sin(_y_ang) + view_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_z_ang) - view_vector.getY()*sin(_z_ang));
    view_vector.setY(x_pr*sin(_z_ang) + view_vector.getY()*cos(_z_ang));

    return view_vector.getX();
}
double Camera::getViewAxisY() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector view_vector = view_axis;

    // Ox
    double y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(_x_ang) + view_vector.getZ()*sin(_x_ang));
    view_vector.setZ(-y_pr*sin(_x_ang) + view_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_y_ang) - view_vector.getZ()*sin(_y_ang));
    view_vector.setZ(x_pr*sin(_y_ang) + view_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_z_ang) - view_vector.getY()*sin(_z_ang));
    view_vector.setY(x_pr*sin(_z_ang) + view_vector.getY()*cos(_z_ang));

    return view_vector.getY();
}
double Camera::getViewAxisZ() const
{
    double _x_ang = x_ang * M_PI/180;
    double _y_ang = y_ang * M_PI/180;
    double _z_ang = z_ang * M_PI/180;

    MathVector view_vector = view_axis;

    // Ox
    double y_pr = view_vector.getY();
    view_vector.setY(y_pr*cos(_x_ang) + view_vector.getZ()*sin(_x_ang));
    view_vector.setZ(-y_pr*sin(_x_ang) + view_vector.getZ()*cos(_x_ang));

    // Oy
    double x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_y_ang) - view_vector.getZ()*sin(_y_ang));
    view_vector.setZ(x_pr*sin(_y_ang) + view_vector.getZ()*cos(_y_ang));

    // Oz
    x_pr = view_vector.getX();
    view_vector.setX(x_pr*cos(_z_ang) - view_vector.getY()*sin(_z_ang));
    view_vector.setY(x_pr*sin(_z_ang) + view_vector.getY()*cos(_z_ang));

    return view_vector.getZ();
}
MathVector Camera::getViewAxis() const
{
    return MathVector(getViewAxisX(), getViewAxisY(), getViewAxisZ());
}

void Camera::moveToWorldCenter()
{
    clear();
    view_axis.setZ(1);
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
    return true;
}
bool Camera::isPolyViz(const Points3D &points, Dot3D<double> &cent_dot, bool is_planet) const
{
    if (!is_planet) return true;

    if (points.size() < 3)
    {
        throw NotEnoughPointsForPoly("\nIn file \"Camera.cpp\" in Camera::IsPolyVis()\n");
    }

    int num = 0;
    double min_z = points[0].z;
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i].z < min_z)
        {
            num = i;
            min_z = points[i].z;
        }
    }

    MathVector poly_norm(points[num].x-cent_dot.x, points[num].y-cent_dot.y, points[num].z-cent_dot.z);
    MathVector cam_vector(points[num].x, points[num].y, points[num].z);

    return (poly_norm.scalarMult(cam_vector) > 0) ? (false) : (true);
}
bool Camera::isOnDisplay(const DotForDrawer &point) const
{
    return isOnDisplay(point.z);
}
bool Camera::isOnDisplay(const double z) const
{
    return (z > 500 /*distance_to_screen*/) ? true : false;
}

