#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
//#include "mydisplay.h"
//#include "errors.h"
#include "facade.h"
//#include "singletone.h"


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
    //void paintEvent(QPaintEvent*);

private slots:
    void on_But_Up_clicked();

    void on_But_Left_clicked();

    void on_But_Down_clicked();

    void on_But_Right_clicked();

    void on_Slider_xTurn_valueChanged(int value);

    void on_Slider_yTurn_valueChanged(int value);

    void on_Slider_zTurn_valueChanged(int value);

    void on_But_To_clicked();

    void on_But_From_clicked();

    void on_ButOpen_clicked();

    void on_Slider_Id_valueChanged(int value);

    void on_Slider_kd_valueChanged(int value);

    void on_Slider_Ia_valueChanged(int value);

    void on_Slider_ka_valueChanged(int value);

    void tmrTick();

private:
    Ui::MainWindow *ui;
    Facade in_dot;
    MyDisplay im;
    QGraphicsScene *scene;
    GraphStruct gr;
    QTimer tmr;
};

#endif // MAINWINDOW_H
