#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gr(im)
{
    ui->setupUi(this);

    im = MyDisplay(ui->graphicsView->width()-2, ui->graphicsView->height()-2,
                QImage::Format_ARGB32);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    gr.Ia = ui->Slider_Ia->value();
    gr.Id = ui->Slider_Id->value();
    gr.kd = (double)ui->Slider_kd->value()/100.;
    gr.ka = (double)ui->Slider_ka->value()/100.;

    im.fill(Qt::black);
    on_ButOpen_clicked();

    /*
    try
    {
        in_dot.read("new.obj");
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
    */
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::on_But_Up_clicked()
{
    InterfaceCommand *caps = new DyCom(-50);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_But_Left_clicked()
{
    InterfaceCommand *caps = new DxCom(-50);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_But_Down_clicked()
{
    InterfaceCommand *caps = new DyCom(50);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_But_Right_clicked()
{
    InterfaceCommand *caps = new DxCom(50);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_Slider_xTurn_valueChanged(int value)
{
    InterfaceCommand *caps = new DxAngCom(value);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_Slider_yTurn_valueChanged(int value)
{
    InterfaceCommand *caps = new DyAngCom(value);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_Slider_zTurn_valueChanged(int value)
{
    InterfaceCommand *caps = new DzAngCom(value);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_But_To_clicked()
{
    InterfaceCommand *caps = new DzCom(-50);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_But_From_clicked()
{
    InterfaceCommand *caps = new DzCom(50);

    try
    {
        in_dot.draw(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

    delete caps;
}

void MainWindow::on_ButOpen_clicked()
{
    try
    {
        in_dot.read(ui->LineEdit->text().toStdString().c_str());
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
}

void MainWindow::on_Slider_Id_valueChanged(int value)
{
    gr.Id = value;

    try
    {
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }

}

void MainWindow::on_Slider_kd_valueChanged(int value)
{
    if ((ui->Slider_kd->value() + ui->Slider_ka->value()) >= 100)
    {
        ui->Slider_kd->setValue(100 - ui->Slider_ka->value());
        ui->label->setText("Нельзя чтобы коэффициенты световой энергии"
                           " в сумме давали > 100");

        return;
    }


    gr.kd = (double)value/100;
    try
    {
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
}

void MainWindow::on_Slider_ka_valueChanged(int value)
{
    if ((ui->Slider_kd->value() + ui->Slider_ka->value()) >= 100)
    {
        ui->Slider_ka->setValue(100 - ui->Slider_kd->value());
        ui->label->setText("Нельзя чтобы коэффициенты световой энергии"
                           " в сумме давали > 100");

        return;
    }

    gr.ka = (double)value/100;
    try
    {
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
}

void MainWindow::on_Slider_Ia_valueChanged(int value)
{
    gr.Ia = value;

    try
    {
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
}
