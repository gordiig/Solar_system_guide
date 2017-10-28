#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <list>
#include <QImage>
#include "baseobjects.h"
#include "math_abstracts.h"
#include "errors.h"
//#include "drawer.h"

//class MathVector;

typedef std::vector<Dot3D<double> > Points3D;
typedef std::vector<Dot2D<double> > Points2D;
typedef std::vector<std::list<int> > PolyList;

class Obj
{
    friend class Sphere;
private:
    Points3D points;
    Points2D texture_coord;
    PolyList poly;

public:
    Obj() { }
    Obj(const Points3D&, const Points2D&, const PolyList&);
    Obj(Points3D&&, Points2D&&, PolyList&&);
    Obj(const Obj&);
    Obj(Obj&&);
    Obj& operator = (const Obj&);
    Obj& operator = (Obj&&);
    ~Obj();

    // Геттеры
    Points3D getPoints() const { return points; }
    Points2D getTextureCoord() const { return texture_coord; }
    PolyList getPoly() const { return poly; }

    void clear();
    Points3D makeCut(int) const;
    Points2D makeTexCut(int) const;

    MathVector calcOutNorm(const int i) const;
    static MathVector calcOutNorm(const Points3D& pts)
    {
        /*
        double a = pts[0].y * (pts[1].z-pts[2].z) +
                pts[1].y * (pts[2].z-pts[0].z) +
                pts[2].y * (pts[0].z-pts[1].z);

        double b = pts[0].z * (pts[1].x-pts[2].x) +
                pts[1].z * (pts[2].x-pts[0].x) +
                pts[2].z * (pts[0].x-pts[1].x);

        double c = pts[0].x * (pts[1].y-pts[2].y) +
                pts[1].x * (pts[2].y-pts[0].y) +
                pts[2].x * (pts[0].y-pts[1].y);
        */
        double x = 0, y = 0, z = 0;
        for (auto &pt : pts)
        {
            x += pt.x;
            y += pt.y;
            z += pt.z;
        }

        MathVector ans(x/pts.size(), y/pts.size(), z/pts.size());
        return ans;
    }
    MathVector calcInNorm(const int i) const;
    static MathVector calcInNorm(const Points3D& pts)
    {
        return calcOutNorm(pts).invert();
    }

    std::vector<MathVector> calcPointNorm(const int) const;
};

class Sphere : public VisibleObject
{
    friend class Transformer;

protected:
    static Obj obj;
    QImage* texture;

public:
    Sphere();
    Sphere(const Sphere&);
    Sphere(Sphere&&);
    Sphere(const Points3D&, const Points2D&, const PolyList&);
    Sphere(Points3D&&, Points2D&&, PolyList&&);
    Sphere(const double in_x, const double in_y, const double in_z);
    Sphere(const double in_x, const double in_y, const double in_z,
                  const double in_x_ang, const double in_y_ang, const double in_z_ang);
    Sphere(const double in_x, const double in_y, const double in_z,
                  const double in_x_ang, const double in_y_ang, const double in_z_ang,
                  const int in_kd, const int in_ka);
    Sphere(const double in_x, const double in_y, const double in_z,
                  const double in_x_ang, const double in_y_ang, const double in_z_ang,
                  const int in_kd, const int in_ka, const char* in_path);
    Sphere(Dot3D<double>&);
    Sphere(Dot3D<double>&, int, int);
    Sphere(Dot3D<double>&, int, int, const char*);
    Sphere(Dot3D<int>&);
    Sphere(Dot3D<int>&, int, int);
    Sphere(Dot3D<int>&, int, int, const char*);

    ~Sphere();

    Sphere& operator = (const Sphere&);
    Sphere& operator = (Sphere&&);

    // Геттеры
    Obj& getObj() const { return obj; }
    Points3D getPoints() const { return obj.points; }
    Points2D getTexCord() const { return obj.texture_coord; }
    PolyList getPoly() const { return obj.poly; }
    QImage* getTexture() const { return texture; }

    Dot3D<double>& operator [] (int i) const;

    // Сеттеры
    void setObj(const Obj& in) { obj = in; }
    void setPoints(const Points3D& in) { obj.points = in; }
    void setPoly(const PolyList& in) { obj.poly = in; }
    void setTexture(const std::string&);
    void setTexture(const char*);
    void setTexture(QImage *);

    virtual void clear() override;


};

class DotLight : public BaseObject
{
private:
    double Id;
    double Ia;

public:
    DotLight();
    DotLight(const DotLight&);
    DotLight(DotLight&&);
    DotLight(Dot3D<double>&, double, double);

    DotLight& operator = (const DotLight&);
    DotLight& operator = (DotLight&&);

    // Геттеры
    double getId() const { return Id; }
    double getIa() const { return Ia; }

    // Сеттеры
    void setId(double in) { Id = in; }
    void setIa(double in) { Ia = in; }

    virtual void clear() override;

    double calcDiffuse(const Dot3D<double>&, const MathVector&) const;
};

#endif // OBJECT_H
