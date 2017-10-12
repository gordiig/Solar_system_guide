#ifndef MYDISPLAY_H
#define MYDISPLAY_H

#include <QImage>
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

    bool isOnDisplay(const DotForDrawer&) const;
    bool isOnDisplay(const int, const int) const;

    void putPixel(const DotForDrawer&, const QColor&);
    void putPixel(const int, const int, const double, const QColor&);
};

#endif // MYDISPLAY_H
