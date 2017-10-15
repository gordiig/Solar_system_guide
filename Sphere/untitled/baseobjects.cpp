#include "baseobjects.h"

BaseObject::BaseObject() : x(0), y(0), z(0), x_ang(0), y_ang(0), z_ang(0) { }
BaseObject::BaseObject(const double in_x, const double in_y, const double in_z) :
    x(in_x), y(in_y), z(in_z) { }
BaseObject::BaseObject(const double in_x, const double in_y, const double in_z,
                       const double in_x_ang, const double in_y_ang, const double in_z_ang) :
    x(in_x), y(in_y), z(in_z) , x_ang(in_x_ang), y_ang(in_y_ang), z_ang(in_z_ang) { }
BaseObject::BaseObject(const Dot3D<double> &in) : BaseObject(in.x, in.y, in.z) { }
BaseObject::BaseObject(const Dot3D<int> &in) : BaseObject(in.x, in.y, in.z) { }

BaseObject::BaseObject(const BaseObject &in)
{
    (*this) = in;
}
BaseObject::BaseObject(BaseObject &&in)
{
    (*this) = in;
    in.clear();
}
BaseObject& BaseObject::operator = (const BaseObject& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;

    return (*this);
}
BaseObject& BaseObject::operator = (BaseObject&& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;

    in.clear();
    return (*this);
}

void BaseObject::clear()
{
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
}


VisibleObject::VisibleObject() : BaseObject::BaseObject(), ka(0.3), kd(0.6), texture_path("NULL") { }
VisibleObject::VisibleObject(const double in_x, const double in_y, const double in_z) :
    BaseObject::BaseObject(in_x, in_y, in_z), ka(0.3), kd(0.6), texture_path("NULL") { }
VisibleObject::VisibleObject(const double in_x, const double in_y, const double in_z,
                             const double in_x_ang, const double in_y_ang, const double in_z_ang) :
    BaseObject::BaseObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang), ka(0.3), kd(0.6),
    texture_path("NULL"){ }
VisibleObject::VisibleObject(const double in_x, const double in_y, const double in_z,
                             const double in_x_ang, const double in_y_ang, const double in_z_ang,
                             const double in_kd, const double in_ka) :
    BaseObject::BaseObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang), ka(in_ka), kd(in_kd),
    texture_path("NULL") { }
VisibleObject::VisibleObject(const double in_x, const double in_y, const double in_z,
                             const double in_x_ang, const double in_y_ang, const double in_z_ang,
                             const double in_kd, const double in_ka, const char* in_path) :
    BaseObject::BaseObject(in_x, in_y, in_z, in_x_ang, in_y_ang, in_z_ang), ka(in_ka), kd(in_kd),
    texture_path(in_path) { }
VisibleObject::VisibleObject(Dot3D<double> &in) : BaseObject::BaseObject(in), ka(0.3), kd(0.6),
    texture_path("NULL") { }
VisibleObject::VisibleObject(Dot3D<double> &in, double in_kd, double in_ka) : BaseObject::BaseObject(in),
    kd(in_kd), ka(in_ka), texture_path("NULL") { }
VisibleObject::VisibleObject(Dot3D<double> &in, double in_kd, double in_ka, const char* in_path) :
    BaseObject::BaseObject(in), kd(in_kd), ka(in_ka), texture_path(in_path) { }
VisibleObject::VisibleObject(Dot3D<int> &in) : BaseObject::BaseObject(in), ka(0.3), kd(0.6),
    texture_path("NULL") { }
VisibleObject::VisibleObject(Dot3D<int> &in, double in_kd, double in_ka) : BaseObject::BaseObject(in),
    kd(in_kd), ka(in_ka), texture_path("NULL") { }
VisibleObject::VisibleObject(Dot3D<int> &in, double in_kd, double in_ka, const char* in_path) :
    BaseObject::BaseObject(in), kd(in_kd), ka(in_ka), texture_path(in_path) { }

VisibleObject::VisibleObject(const VisibleObject &in)
{
    (*this) = in;
}
VisibleObject::VisibleObject(VisibleObject &&in)
{
    (*this) = in;
    in.clear();
}
VisibleObject& VisibleObject::operator = (const VisibleObject& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    kd = in.kd;
    ka = in.ka;
    texture_path = in.texture_path;

    return (*this);
}
VisibleObject& VisibleObject::operator = (VisibleObject&& in)
{
    x = in.x;
    y = in.y;
    z = in.z;
    x_ang = in.x_ang;
    y_ang = in.y_ang;
    z_ang = in.z_ang;
    kd = in.kd;
    ka = in.ka;
    texture_path = in.texture_path;

    in.clear();
    return (*this);
}

void VisibleObject::clear()
{
    x = 0;
    y = 0;
    z = 0;
    x_ang = 0;
    y_ang = 0;
    z_ang = 0;
    kd = 0;
    ka = 0;
    texture_path.clear();
}
