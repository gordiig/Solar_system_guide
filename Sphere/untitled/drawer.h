#ifndef DRAWER_H
#define DRAWER_H

#include "obj.h"
#include "logger.h"
#include "mydisplay.h"
#include "camera.h"
#include "math_abstracts.h"
#include <iterator>
#include <math.h>
namespace Drwr
{
    struct BaseGraphcsToDraw
    {
        MyDisplay& im;
        Camera& cam;
        DotLight& light;
        QImage* texture;
        std::vector<double> I;

        BaseGraphcsToDraw(MyDisplay& in_im, Camera& in_cam, DotLight& in_light, QImage* in_tex,
                          std::vector<double>& in_I) :
            im(in_im), cam(in_cam), light(in_light), texture(in_tex), I(in_I){ }
    };
    struct GraphicsToDraw : public BaseGraphcsToDraw
    {
        Obj& obj;

        GraphicsToDraw(MyDisplay& in_im, Camera& in_cam, DotLight& in_light, Obj& in_obj, QImage* in_tex,
                       std::vector<double> in_I) :
            BaseGraphcsToDraw::BaseGraphcsToDraw(in_im, in_cam, in_light, in_tex, in_I), obj(in_obj) { }
    };
    struct PolyToDraw : public BaseGraphcsToDraw
    {
        Points3D poly;
        Points2D tex_coords;
        std::vector<MathVector> point_vectors;

        PolyToDraw(GraphicsToDraw& in_gr, int i) :
            BaseGraphcsToDraw(in_gr.im, in_gr.cam, in_gr.light, in_gr.texture, in_gr.I),
            poly(in_gr.obj.makeCut(i)), tex_coords(in_gr.obj.makeTexCut(i)), point_vectors(in_gr.obj.calcPointNorm(i))
        {
            this->I.clear();
            PolyList poly = in_gr.obj.getPoly();
            for (auto &i : poly[i])
            {
                this->I.push_back(in_gr.I[i-1]);
            }
        }
    };

    typedef std::vector<std::list<DotForDrawer> > RasteredPoly;
}

class Drawer
{
public:
    Drawer() { }
    void draw(Drwr::GraphicsToDraw&);

private:
    void drawDots(MyDisplay&, const Points3D&);
    void drawScelet(MyDisplay&, const Obj&);
    void drawVizScelet(MyDisplay&, const Camera& cam, const Obj&);
    void drawSphere(Drwr::GraphicsToDraw&);

    void drawPoly(Drwr::PolyToDraw& gr);
    Drwr::RasteredPoly polyRasterization(const Drwr::PolyToDraw&);

    void solidPolyPainting(Drwr::PolyToDraw&, const Drwr::RasteredPoly&);
    void guroPolyPainting(Drwr::PolyToDraw&, const Drwr::RasteredPoly&);

    std::list<DotForDrawer> lineRasterizationBrez(const DotForDrawer &,
                                                                const DotForDrawer &);

    void drawLineBrez(MyDisplay&, const Dot2D<double>&, const Dot2D<double>&);
    void drawLineBrez(MyDisplay&, const int, const int, const int, const int);
};

#endif // DRAWER_H
