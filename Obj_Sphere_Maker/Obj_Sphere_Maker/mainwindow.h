#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <cmath>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

struct Dot
{
    double x;
    double y;
    double z;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Start_Button_clicked();

    void on_Dir_Button_clicked();

private:
    Ui::MainWindow *ui;

    std::ofstream out_file;
    QString file_dir;

    void vWriter(const int, const int, const double);
    void vtWriter(const int,  const int);

    double roundToN(double, int n = 4);
};

#endif // MAINWINDOW_H
