#include "facade.h"

Facade::Facade()
{
    std::string path("/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/textures");

    PlanetSystem* sys = new PlanetSystem;
    Sphere* pl = new Sphere;
    pl->setTexturePath(path+std::string("/earth.jpg"));

    sys->add(pl);
    solar_system.add(sys);
}

Facade::Facade(const char *name)
{
    reader.openFile(name);
}

Facade::~Facade()
{
    reader.closeFile();
}

void Facade::camMove(GraphStruct &gr, InterfaceCommand *caps)
{
    if (caps)
    {
        caps->exec(cam);
    }
    light.setX(50);
    light.setY(50);
    light.setZ(-120);

    draw(gr);
}

void Facade::planetMove(GraphStruct &gr)
{
    solar_system.tickMove();
    light.setX(50);
    light.setY(50);
    light.setZ(-120);

    draw(gr);
}

void Facade::draw(GraphStruct &gr)
{
    for (int i = 0; i < solar_system.size(); i++)
    {
        for (int j = 0; j < solar_system[i]->size(); j++)
        {
            Sphere* planet = (*solar_system[i])[j];
            Transformer trans;
            Obj draw_object(trans.transform(*planet, cam), planet->getTexCord(), planet->getPoly());
            light.setByDot(trans.transform(light, cam));

            planet->setKa(gr.ka);
            planet->setKd(gr.kd);
            light.setIa(gr.Ia);
            light.setId(gr.Id);

            if (!texture)
            {
                texture = new QImage(QString::fromStdString(planet->getTexturePath()));
            }


            Drwr::GraphicsToDraw gr_in(gr.im, cam, light, draw_object, texture,
                           planet->getKa(), planet->getKd());
            gr_in.im.clrZBuf();
            Drawer dr;
            dr.draw(gr_in);
        }
        delete texture;
        texture = nullptr;
    }
}

void Facade::read(const char *name)
{
    reader.openFile(name);
    Obj tmp = reader.read();
    solar_system.setObj(tmp);
}
