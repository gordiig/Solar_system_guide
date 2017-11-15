#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "obj.h"
#include "camera.h"
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

    void clear();

private:
    Points3D points;

    void scale(const VisibleObject& obj);
    void turn(const VisibleObject& obj);
    //void turn(const Camera& cam);
    void move(const VisibleObject& obj);
};

#endif // TRANSFORMER_H
