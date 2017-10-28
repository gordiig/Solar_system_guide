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
    Points3D& transform(const Sphere& obj, const Camera &cam);
    Dot3D<double> transform(const DotLight&, const Camera &cam);

private:
    Points3D points;
    void turn(const Sphere& obj);
    //void turn(const Camera& cam);
    void move(const Sphere& obj);
    void proectToCam(const Camera& cam);
};

#endif // TRANSFORMER_H
