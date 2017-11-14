#ifndef MYDISPLAY_H
#define MYDISPLAY_H

#include <QImage>
#include "obj.h"
#include "math_abstracts.h"

class MyDisplay : public QImage
{
protected:
    MyMat<double> z_buf;

public:
    MyDisplay();
    MyDisplay(int, int, QImage::Format);
    ~MyDisplay();

    // Геттеры
    double getIJFromZBuf(const int i, const int j) const { return z_buf[i][j]; }

    // Сеттеры
    void setIJFromZBuf(const int i, const int j, double in) { z_buf[i][j] = in; }
    void fillZBuf(const double);
    void clrZBuf();

    void screenCut(Points3D&, std::vector<double>&, Points2D&);

    bool isOnDisplay(const Dot2D<double>&, const Dot2D<double>&) const;
    bool isOnDisplay(const DotForDrawer&) const;
    bool isOnDisplay(const int, const int) const;

    bool isDotOnScreen(const Dot3D<double>&) const;
    bool isDotOnScreen(const Dot2D<double>&) const;

    void putPixel(const DotForDrawer&, const QColor&);
    void putPixel(const int, const int, const double, const QColor&);

private:
    enum ScrSide
    {
        left = 0,
        top,
        right,
        bottom
    };

    void screenCut(Points3D&, std::vector<double>&, Points2D&, int);
    bool isDotInSide(const Dot3D<double>&, int) const;
};

#endif // MYDISPLAY_H
