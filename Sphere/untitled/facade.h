#ifndef FACADE_H
#define FACADE_H

#include <map>

#include "errors.h"
#include "obj.h"
#include "reader.h"
#include "comcapsule.h"
#include "mydisplay.h"
#include "spacesystems.h"

#include "transformer.h"
#include "drawer.h"

struct GraphStruct
{
    MyDisplay &im;
    double kd;
    double ka;
    double Id;
    double Ia;

    GraphStruct(MyDisplay& in) : im(in) {}
};

class Facade
{
private:
    SolarSystem solar_system;
    QImage* texture;
    Reader reader;
    DotLight light;
    Camera cam;

    std::map<char, double> radius_koef;
    std::map<char, double> distance_koef;

    const double EARTH_DISTANCE_FROM_SUN = 450000;
    const double CAMERA_DISTANCE = 1353494.5;

    Facade(const Facade&);
    Facade(Facade&&);
    Facade& operator = (const Facade&);

public:
    Facade();
    Facade(const char *name);
    ~Facade();

    void camMove(GraphStruct& gr, InterfaceCommand *caps = nullptr);
    void planetMove(GraphStruct& gr);

    void draw(GraphStruct &gr);
    void read(const char *name = "new.obj");
};

#endif // FACADE_H
