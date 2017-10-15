#ifndef BASEOBJECTS_H
#define BASEOBJECTS_H

#include "errors.h"

template <typename T>
struct Dot2D
{
    T x;
    T y;

    Dot2D() : x(0), y(0) {}
    Dot2D(const Dot2D<T>& in) : x(in.x), y(in.y) {}
    Dot2D(Dot2D<T>&& in)
    {
        x = in.x;
        y = in.y;

        in.x = 0;
        in.y = 0;
    }
    Dot2D(const T& in_x, const T& in_y) : x(in_x), y(in_y) {}

    Dot2D& operator = (const Dot2D& in)
    {
        x = in.x;
        y = in.y;

        return *this;
    }
    Dot2D& operator = (Dot2D&& in)
    {
        x = in.x;
        y = in.y;

        in.x = 0;
        in.y = 0;

        return *this;
    }

    virtual ~Dot2D() { }
};

struct DotForDrawer : public Dot2D<int>
{
    double z;
    double I;
    Dot2D texture_coord;

    DotForDrawer(const int _x, const int _y, const double _z)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        I = 0;
    }
    DotForDrawer(const int _x, const int _y, const double _z, const double _I)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->I = _I;
    }
    DotForDrawer(const int _x, const int _y, const double _z, const double _I, const Dot2D& _tex)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->I = _I;
        texture_coord = _tex;
    }

    bool operator > (const DotForDrawer& in) const
    {
        return this->x > in.x;
    }
    bool operator < (const DotForDrawer& in) const
    {
        return this->x < in.x;
    }
};

template <typename T>
struct Dot3D : public Dot2D<T>
{
    T z;

    Dot3D() : Dot2D<T>::Dot2D(), z(0) {}
    Dot3D(const Dot3D<T>& in) : Dot2D<T>::Dot2D(in.x, in.y), z(in.z) {}
    Dot3D( Dot3D<T>&& in) : Dot2D<T>::Dot2D(in.x, in.y), z(in.z)
    {
        in.x = in.y = in.z = 0;
    }
    Dot3D(const T& in_x, const T& in_y, const T& in_z) : Dot2D<T>::Dot2D(in_x, in_y), z(in_z) {}

    Dot3D& operator = (const Dot3D& in)
    {
        this->x = in.x;
        this->y = in.y;
        z = in.z;

        return *this;
    }
    Dot3D& operator = (Dot3D&& in)
    {
        this->x = in.x;
        this->y = in.y;
        z = in.z;

        in.x = 0;
        in.y = 0;
        in.z = 0;

        return *this;
    }

    operator DotForDrawer() const
    {
        DotForDrawer ans((int) (this->x+0.5), (int) (this->y+0.5), z);
        return ans;
    }
};

class BaseObject
{
protected:
    double x;
    double y;
    double z;

    double x_ang;
    double y_ang;
    double z_ang;

public:
    BaseObject();
    BaseObject(const BaseObject&);
    BaseObject(BaseObject&&);
    BaseObject(const double in_x, const double in_y, const double in_z);
    BaseObject(const double in_x, const double in_y, const double in_z,
               const double in_x_ang, const double in_y_ang, const double in_z_ang);
    BaseObject(const Dot3D<double>&);
    BaseObject(const Dot3D<int>&);
    virtual ~BaseObject() { }

    BaseObject& operator = (const BaseObject&);
    BaseObject& operator = (BaseObject&&);

    // Геттеры
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    Dot3D<double> getPosDot() const { return Dot3D<double>(x, y, z); }
    double getXAng() const { return x_ang; }
    double getYAng() const { return y_ang; }
    double getZAng() const { return z_ang; }

    // Сеттеры
    void setX(const double in) { x = in; }
    void setY(const double in) { y = in; }
    void setZ(const double in) { z = in; }
    void setByDot(const Dot3D<double>& in) { x = in.x; y = in.y; z = in.z; }
    void setXAng(const double in) { x_ang = in; }
    void setYAng(const double in) { y_ang = in; }
    void setZAng(const double in) { z_ang = in; }

    virtual void clear();
};

class VisibleObject : public BaseObject
{
protected:
    double ka;
    double kd;

public:
    VisibleObject();
    VisibleObject(const VisibleObject&);
    VisibleObject(VisibleObject&&);
    VisibleObject(const double in_x, const double in_y, const double in_z);
    VisibleObject(const double in_x, const double in_y, const double in_z,
                  const double in_x_ang, const double in_y_ang, const double in_z_ang);
    VisibleObject(const double in_x, const double in_y, const double in_z,
                  const double in_x_ang, const double in_y_ang, const double in_z_ang,
                  const double in_kd, const double in_ka);
    VisibleObject(Dot3D<double>&);
    VisibleObject(Dot3D<double>&, double, double);
    VisibleObject(Dot3D<int>&);
    VisibleObject(Dot3D<int>&, double, double);
    virtual ~VisibleObject() { }

    VisibleObject& operator = (const VisibleObject&);
    VisibleObject& operator = (VisibleObject&&);

    // Геттеры
    double getKd() const { return kd; }
    double getKa() const { return ka; }

    // Сеттеры
    void setKd(double in) { kd = in; }
    void setKa(double in) { ka = in; }

    virtual void clear() override;
};

#endif // BASEOBJECTS_H
