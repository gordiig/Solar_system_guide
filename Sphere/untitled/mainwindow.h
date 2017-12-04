#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
//#include "mydisplay.h"
//#include "errors.h"
#include "facade.h"

#define MOUSE_SENS 0.3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
    void tmrTick();

private:
    Ui::MainWindow *ui;
    Facade in_dot;
    MyDisplay im;
    QGraphicsScene *scene;
    GraphStruct gr;
    QTimer tmr;

    int last_x;
    int last_y;
};

#endif // MAINWINDOW_H
