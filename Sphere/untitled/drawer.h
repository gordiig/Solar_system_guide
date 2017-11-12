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
        QImage* texture;
        Dot3D<double> c_d;
        std::vector<double> I;

        BaseGraphcsToDraw(MyDisplay& in_im, Camera& in_cam, QImage* in_tex, Dot3D<double>& in_c_d,
                          std::vector<double>& in_I) :
            im(in_im), cam(in_cam), texture(in_tex), c_d(in_c_d), I(in_I){ }

        BaseGraphcsToDraw(MyDisplay& in_im, Camera& in_cam, QImage* in_tex, Dot3D<double>& in_c_d) :
            im(in_im), cam(in_cam), texture(in_tex), c_d(in_c_d){ }
    };
    struct GraphicsToDraw : public BaseGraphcsToDraw
    {
        Obj& obj;

        GraphicsToDraw(MyDisplay& in_im, Camera& in_cam, Obj& in_obj, QImage* in_tex, Dot3D<double>& in_c_d,
                       std::vector<double> in_I) :
            BaseGraphcsToDraw::BaseGraphcsToDraw(in_im, in_cam, in_tex, in_c_d, in_I), obj(in_obj) { }
    };
    struct PolyToDraw : public BaseGraphcsToDraw
    {
        Points3D poly;
        Points2D tex_coords;

        PolyToDraw(GraphicsToDraw& in_gr, int i) :
            BaseGraphcsToDraw(in_gr.im, in_gr.cam, in_gr.texture, in_gr.c_d),
            poly(in_gr.obj.makeCut(i)), tex_coords(in_gr.obj.makeTexCut(i))
        {
            PolyList poly = in_gr.obj.getPoly();
            for (auto &pt_n : poly[i])
            {
                this->I.push_back(in_gr.I[pt_n-1]);
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
    Drwr::RasteredPoly polyRasterization(Drwr::PolyToDraw &);

    void solidPolyPainting(Drwr::PolyToDraw&, const Drwr::RasteredPoly&);
    void guroPolyPainting(Drwr::PolyToDraw&, const Drwr::RasteredPoly&);

    std::list<DotForDrawer> lineRasterizationBrez(const DotForDrawer &,
                                                                const DotForDrawer &);

    void drawLineBrez(MyDisplay&, const Dot2D<double>&, const Dot2D<double>&);
    void drawLineBrez(MyDisplay&, const int, const int, const int, const int);
};

#endif // DRAWER_H
