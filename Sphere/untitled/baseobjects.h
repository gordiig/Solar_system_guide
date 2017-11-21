#ifndef BASEOBJECTS_H
#define BASEOBJECTS_H

#include "errors.h"
#include <list>

#define BASE_KA 0.3
#define BASE_KD 0.65

class Obj;
class QImage;
class MathVector;
class DotLight;
class Camera;

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
    Dot2D<double> texture_coord;

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
    DotForDrawer(const int _x, const int _y, const double _z, const double _I, const Dot2D<double>& _tex)
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

typedef std::vector<Dot3D<double> > Points3D;
typedef std::vector<Dot2D<double> > Points2D;
typedef std::vector<std::list<int> > PolyList;

class BaseObject
{
protected:
    double x;
    double y;
    double z;

    double x_ang;
    double y_ang;
    double z_ang;

    double turning_cent_x;
    double turning_cent_y;
    double turning_cent_z;

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
    double getTurningCentX() const { return turning_cent_x; }
    double getTurningCentY() const { return turning_cent_y; }
    double getTurningCentZ() const { return turning_cent_z; }
    Dot3D<double> getTurningCent() const { return Dot3D<double>(turning_cent_x, turning_cent_y, turning_cent_z); }

    // Сеттеры
    void setX(const double in) { x = in; }
    void setY(const double in) { y = in; }
    void setZ(const double in) { z = in; }
    void setByDot(const Dot3D<double>& in) { x = in.x; y = in.y; z = in.z; }
    void setXAng(const double in) { x_ang = in; }
    void setYAng(const double in) { y_ang = in; }
    void setZAng(const double in) { z_ang = in; }
    void setTurningCentX(const double in) { turning_cent_x = in; }
    void setTurningCentY(const double in) { turning_cent_y = in; }
    void setTurningCentZ(const double in) { turning_cent_z = in; }
    void setTurningCent(const Dot3D<double>& in) { turning_cent_x = in.x; turning_cent_y = in.y; turning_cent_z = in.z; }

    virtual void clear();
};

class VisibleObject : public BaseObject
{
    friend class Transformer;

protected:
    double scale;
    double ka;
    double kd;
    std::string texture_path;

    virtual void transform() = 0;
    virtual void move() = 0;
    virtual void turn() = 0;
    virtual void resize() = 0;
    virtual void recalcCamPos() { }

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
    VisibleObject(const double in_x, const double in_y, const double in_z,
                  const double in_x_ang, const double in_y_ang, const double in_z_ang,
                  const double in_kd, const double in_ka, const char* in_path);
    VisibleObject(Dot3D<double>&);
    VisibleObject(Dot3D<double>&, double, double);
    VisibleObject(Dot3D<double>&, double, double, const char*);
    VisibleObject(Dot3D<int>&);
    VisibleObject(Dot3D<int>&, double, double);
    VisibleObject(Dot3D<int>&, double, double, const char*);
    virtual ~VisibleObject() { }

    VisibleObject& operator = (const VisibleObject&);
    VisibleObject& operator = (VisibleObject&&);

    // Геттеры
    double getKd() const { return kd; }
    double getKa() const { return ka; }
    double getScale() const { return scale; }
    std::string getTexturePath() const { return texture_path; }
    virtual Obj& getObj() const = 0;
    virtual Obj& getTransformedObj() = 0;
    virtual Points3D getPoints() const = 0;
    virtual Points3D getScaledPoints() const = 0;
    virtual Points2D getTexCord() const = 0;
    virtual PolyList getPoly() const = 0;
    virtual QImage* getTexture() const = 0;
    virtual MathVector getPointNorm(int) const = 0;
    virtual std::vector<MathVector> getAllNorm() const = 0;
    virtual double getANG_PER_TICK_ROUND_SUN() const = 0;
    virtual double getANG_PER_TICK_ROUND_ORBITE() const = 0;
    virtual double getANG_PER_TICK_ROUND_TURNCENT() const = 0;
    virtual Camera* getCam() const { return nullptr; }

    // Сеттеры
    void setKd(double in) { kd = in; }
    void setKa(double in) { ka = in; }
    void setScale(double in) { scale = in; }
    void setTexturePath(const char* in) { texture_path = std::string(in); }
    void setTexturePath(const std::string& in) { texture_path = in; }
    virtual void setObj(const Obj& in) = 0;
    virtual void setTransformedObj(const Obj& in) = 0;
    virtual void setPoints(const Points3D& in) = 0;
    virtual void setPoly(const PolyList& in) = 0;
    virtual void setTexture(const std::string&) = 0;
    virtual void setTexture(const char*) = 0;
    virtual void setTexture(QImage *) = 0;
    virtual void setANG_PER_TICK_ROUND_SUN(double in) = 0;
    virtual void setANG_PER_TICK_ROUND_ORBITE(double in) = 0;
    virtual void setANG_PER_TICK_ROUND_TURNCENT(double in) = 0;

    virtual std::vector<double> calcI(const DotLight&) const = 0;

    virtual bool isPlanet() const = 0;

    virtual void clear() override;
};

#endif // BASEOBJECTS_H
