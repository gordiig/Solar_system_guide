#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <list>
#include <QImage>
#include "baseobjects.h"
#include "math_abstracts.h"
#include "errors.h"

enum Cam_id
{
    free_cam = 0,
    fixed_cam,
};

class Obj
{
    friend class Sphere;
    friend class Ring;
    friend class Transformer;
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

class Camera : public BaseObject
{
protected:
    MathVector view_axis;
    MathVector right_axis;
    MathVector up_axis;
    double distance_to_screen;
    int id;

public:
    Camera(int in_id = free_cam);
    Camera(const Camera&);
    Camera(Camera&&);
    Camera(double, double, double, int in_id = free_cam);
    Camera(Dot3D<double> in_dot, double in_x_ang, double in_y_ang, double in_z_ang, int in_id = free_cam);

    Camera& operator = (const Camera&);
    Camera& operator = (Camera&&);

    // Геттеры
    double getDistanceToScreen() const { return distance_to_screen; }

    double getViewAxisX() const;
    double getViewAxisY() const;
    double getViewAxisZ() const;
    MathVector getViewAxis() const;

    double getRightAxisX() const;
    double getRightAxisY() const;
    double getRightAxisZ() const;
    MathVector getRightAxis() const;

    double getUpAxisX() const;
    double getUpAxisY() const;
    double getUpAxisZ() const;
    MathVector getUpAxis() const;

    int getId() const { return id; }

    // Сеттеры
    void setDistanceToScreen(double in) { distance_to_screen = in; }

    void setViewAxisX(double in) { view_axis.setX(in); }
    void setViewAxisY(double in) { view_axis.setY(in); }
    void setViewAxisZ(double in) { view_axis.setZ(in); }
    void setViewAxis(double in_1, double in_2, double in_3) { setViewAxisX(in_1); setViewAxisY(in_2); setViewAxisZ(in_3); }
    void setViewAxis(MathVector &in) { view_axis = in; }

    void setRightAxisX(double in) { right_axis.setX(in); }
    void setRightAxisY(double in) { right_axis.setY(in); }
    void setRightAxisZ(double in) { right_axis.setZ(in); }
    void setRightAxis(double in_1, double in_2, double in_3) { setRightAxisX(in_1); setRightAxisY(in_2); setRightAxisZ(in_3); }
    void setRightAxis(MathVector &in) { right_axis = in; }

    void setUpAxisX(double in) { up_axis.setX(in); }
    void setUpAxisY(double in) { up_axis.setY(in); }
    void setUpAxisZ(double in) { up_axis.setZ(in); }
    void setUpAxis(double in_1, double in_2, double in_3) { setUpAxisX(in_1); setUpAxisY(in_2); setUpAxisZ(in_3); }
    void setUpAxis(MathVector &in) { up_axis = in; }


    void moveToWorldCenter();
    virtual void clear() override;

    bool isPolyViz(const Points3D&, Dot3D<double>&, bool) const;
    bool isPolyViz(const Points3D&) const;
    bool isOnDisplay(const DotForDrawer&) const;
    bool isOnDisplay(const double) const;
};

class Sphere : public VisibleObject
{
private:
    double ANG_PER_TICK_ROUND_SUN;
    double ANG_PER_TICK_ROUND_ORBITE;
    double ANG_PER_TICK_ROUND_TURNCENT;

    virtual void transform() override;
    virtual void move() override;
    virtual void turn() override;
    virtual void resize() override;

protected:
    static Obj obj;
    static Obj transformed_obj;
    QImage* texture;
    Camera* cam;

    virtual void initCam();

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
    Sphere(Dot3D<double>&);
    Sphere(Dot3D<int>&);

    ~Sphere();

    Sphere& operator = (const Sphere&);
    Sphere& operator = (Sphere&&);

    // Геттеры
    virtual Obj& getObj() const override { return obj; }
    virtual Obj& getTransformedObj() override { transform(); return transformed_obj; }
    virtual Points3D getPoints() const override { return obj.points; }
    virtual Points3D getScaledPoints() const override;
    virtual Points2D getTexCord() const override { return obj.texture_coord; }
    virtual PolyList getPoly() const override { return obj.poly; }
    virtual QImage* getTexture() const override { return texture; }
    virtual MathVector getPointNorm(int) const override;
    virtual std::vector<MathVector> getAllNorm() const override;
    virtual double getANG_PER_TICK_ROUND_SUN() const override { return ANG_PER_TICK_ROUND_SUN; }
    virtual double getANG_PER_TICK_ROUND_ORBITE() const override { return ANG_PER_TICK_ROUND_ORBITE; }
    virtual double getANG_PER_TICK_ROUND_TURNCENT() const override { return ANG_PER_TICK_ROUND_TURNCENT; }
    virtual Camera* getCam() override;
    double getRadius() const;

    Dot3D<double>& operator [] (int i) const;

    // Сеттеры
    virtual void setObj(const Obj& in) override { obj = in; }
    virtual void setTransformedObj(const Obj& in) override { transformed_obj = in; }
    virtual void setPoints(const Points3D& in) override { obj.points = in; }
    virtual void setPoly(const PolyList& in) override { obj.poly = in; }
    virtual void setTexture(const std::string&) override;
    virtual void setTexture(const char*) override;
    virtual void setTexture(QImage *) override;
    virtual void setANG_PER_TICK_ROUND_SUN(double in) override { ANG_PER_TICK_ROUND_SUN = in; }
    virtual void setANG_PER_TICK_ROUND_ORBITE(double in) override { ANG_PER_TICK_ROUND_ORBITE = in; }
    virtual void setANG_PER_TICK_ROUND_TURNCENT(double in) override { ANG_PER_TICK_ROUND_TURNCENT = in; }

    virtual std::vector<double> calcI(const DotLight&) const override;

    virtual void recalcCamPos();

    virtual bool isPlanet() const override { return true; }

    virtual void clear() override;
};

class Ring : public VisibleObject
{
private:
    double ANG_PER_TICK_ROUND_SUN;
    double ANG_PER_TICK_ROUND_ORBITE;
    double ANG_PER_TICK_ROUND_TURNCENT;

    virtual void transform() override;
    virtual void move() override;
    virtual void turn() override;
    virtual void resize() override;

protected:
    static Obj obj;
    static Obj transformed_obj;
    QImage* texture;

public:
    Ring();
    Ring(const Ring&);
    Ring(Ring&&);
    Ring(const Points3D&, const Points2D&, const PolyList&);
    Ring(Points3D&&, Points2D&&, PolyList&&);

    ~Ring();

    Ring& operator = (const Ring&);
    Ring& operator = (Ring&&);

    // Геттеры
    virtual Obj& getObj() const override { return obj; }
    virtual Obj& getTransformedObj() override { transform(); return transformed_obj; }
    virtual Points3D getPoints() const override { return obj.points; }
    virtual Points3D getScaledPoints() const override;
    virtual Points2D getTexCord() const override { return obj.texture_coord; }
    virtual PolyList getPoly() const override { return obj.poly; }
    virtual QImage* getTexture() const override { return texture; }
    virtual MathVector getPointNorm(int) const override;
    virtual std::vector<MathVector> getAllNorm() const override;
    virtual double getANG_PER_TICK_ROUND_SUN() const override { return ANG_PER_TICK_ROUND_SUN; }
    virtual double getANG_PER_TICK_ROUND_ORBITE() const override { return ANG_PER_TICK_ROUND_ORBITE; }
    virtual double getANG_PER_TICK_ROUND_TURNCENT() const override { return ANG_PER_TICK_ROUND_TURNCENT; }

    Dot3D<double>& operator [] (int i) const;

    // Сеттеры
    virtual void setObj(const Obj& in) override { obj = in; }
    virtual void setTransformedObj(const Obj& in) override { transformed_obj = in; }
    virtual void setPoints(const Points3D& in) override { obj.points = in; }
    virtual void setPoly(const PolyList& in) override { obj.poly = in; }
    virtual void setTexture(const std::string&) override;
    virtual void setTexture(const char*) override;
    virtual void setTexture(QImage *) override;
    virtual void setANG_PER_TICK_ROUND_SUN(double in) override { ANG_PER_TICK_ROUND_SUN = in; }
    virtual void setANG_PER_TICK_ROUND_ORBITE(double in) override { ANG_PER_TICK_ROUND_ORBITE = in; }
    virtual void setANG_PER_TICK_ROUND_TURNCENT(double in) override { ANG_PER_TICK_ROUND_TURNCENT = in; }

    virtual std::vector<double> calcI(const DotLight&) const override;

    virtual bool isPlanet() const override { return false; }

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
    DotLight(Dot3D<double>&&, double, double);

    DotLight& operator = (const DotLight&);
    DotLight& operator = (DotLight&&);

    // Геттеры
    double getId() const { return Id; }
    double getIa() const { return Ia; }

    // Сеттеры
    void setId(double in) { Id = in; }
    void setIa(double in) { Ia = in; }

    virtual void clear() override;

    std::vector<double> calcI(const Obj&, const Dot3D<double>&, double, double);

    double calcDiffuse(const Dot3D<double>&, const MathVector&) const;
};

#endif // OBJECT_H
