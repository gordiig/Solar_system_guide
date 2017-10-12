#include "facade.h"

Facade::Facade() { }

Facade::Facade(const char *name)
{
    reader.openFile(name);
}

Facade::~Facade()
{
    reader.closeFile();
}

void Facade::draw(GraphStruct &gr, InterfaceCommand *caps)
{
    if (caps)
    {
        caps->exec(cam);
    }
    light.setX(100);
    light.setY(100);
    light.setZ(-700);

    Transformer trans;
    Obj draw_object(trans.transform(planet, cam), planet.getPoly());
    light.setByDot(trans.transform(light, cam));

    planet.setKa(gr.ka);
    planet.setKd(gr.kd);
    light.setIa(gr.Ia);
    light.setId(gr.Id);


    Drwr::GraphicsToDraw gr_in(gr.im, cam, light, draw_object,
                   planet.getKa(), planet.getKd());
    gr_in.im.clrZBuf();
    Drawer dr;
    dr.draw(gr_in);
}

void Facade::read(const char *name)
{
    reader.openFile(name);
    planet.setObj(reader.read());
}
