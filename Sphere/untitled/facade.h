#ifndef FACADE_H
#define FACADE_H

#include "errors.h"
#include "obj.h"
#include "reader.h"
#include "comcapsule.h"
#include "mydisplay.h"

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
    Sphere planet;
    QImage* texture;
    Reader reader;
    DotLight light;
    Camera cam;

    Facade(const Facade&);
    Facade(Facade&&);
    Facade& operator = (const Facade&);

public:
    Facade();
    Facade(const char *name);
    ~Facade();

    void camMove(GraphStruct& gr, InterfaceCommand *caps = nullptr);
    void planetMove(GraphStruct& gr, InterfaceCommand *caps = nullptr);

    void draw(GraphStruct &gr);
    void read(const char *name = "new.obj");
};

#endif // FACADE_H
