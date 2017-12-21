#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "obj.h"
#include <math.h>

class Transformer
{
public:
    Transformer();
    ~Transformer();
    Points3D& transform(const VisibleObject &obj);
    void proectToCam(Obj&, const Camera&);
    void proectToCam(Dot3D<double>&, const Camera&);
    Dot3D<double> transform(const DotLight&, const Camera &cam);
    // void scale(Obj&, double);
    Points3D scale(const Points3D&, double);
    void proectToCam(Points3D &, const Camera&);

    void clear();

private:
    Points3D points;

    void scale(const VisibleObject& obj);
    void turn(const VisibleObject& obj);
    //void turn(const Camera& cam);
    void move(const VisibleObject& obj);
};

#endif // TRANSFORMER_H
